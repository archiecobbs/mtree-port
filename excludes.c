/*
 * Copyright 2000 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that both the above copyright notice and this
 * permission notice appear in all copies, that both the above
 * copyright notice and this permission notice appear in all
 * supporting documentation, and that the name of M.I.T. not be used
 * in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  M.I.T. makes
 * no representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THIS SOFTWARE IS PROVIDED BY M.I.T. ``AS IS''.  M.I.T. DISCLAIMS
 * ALL EXPRESS OR IMPLIED WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT
 * SHALL M.I.T. BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "config.h"

#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/time.h>           /* XXX for mtree.h */
#include <sys/queue.h>

#include <err.h>
#include <fnmatch.h>
#include <fts.h>
#include <stdio.h>
#include <stdlib.h>

#include "mtree.h"              /* XXX for extern.h */
#include "extern.h"

/*
 * We're assuming that there won't be a whole lot of excludes,
 * so it's OK to use a stupid algorithm.
 */
struct patlist {
        LIST_ENTRY(patlist) link;
        const char *glob;
        int pathname;
};
LIST_HEAD(pathead, patlist);

static struct pathead includes;
static struct pathead excludes;

static int any_includes;

static void read_patlist_file(struct pathead *pathead, const char *name);
static int check_patlist(struct pathead *pathead, const char *fname, const char *path);

void
init_patlists(void)
{
        LIST_INIT(&includes);
        LIST_INIT(&excludes);
}

void
read_includes_file(const char *name)
{
    read_patlist_file(&includes, name);
    any_includes = 1;
}

void
read_excludes_file(const char *name)
{
    read_patlist_file(&excludes, name);
}

static void
read_patlist_file(struct pathead *pathead, const char *name)
{
        FILE *fp;
        char *line, *str;
        struct patlist *e;
#if HAVE_GETLINE
        ssize_t len;
        size_t alloc;
#else
        size_t len;
#endif

        fp = fopen(name, "r");
        if (fp == 0)
                err(1, "%s", name);

#if HAVE_GETLINE
        for (line = NULL; (len = getline(&line, &alloc, fp)) != -1; ) {
#else
        while ((line = fgetln(fp, &len)) != NULL) {
#endif
                if (line[len - 1] == '\n')
                        len--;
                if (len == 0)
                        continue;

                str = malloc(len + 1);
                e = malloc(sizeof *e);
                if (str == 0 || e == 0)
                        errx(1, "memory allocation error");
                e->glob = str;
                memcpy(str, line, len);
                str[len] = '\0';
                if (strchr(str, '/'))
                        e->pathname = 1;
                else
                        e->pathname = 0;
                LIST_INSERT_HEAD(pathead, e, link);
        }
#if HAVE_GETLINE
        free(line);
#endif
        fclose(fp);
}

int
check_includes(const char *fname, const char *path)
{
        return !any_includes || check_patlist(&includes, fname, path);
}

int
check_excludes(const char *fname, const char *path)
{
        return check_patlist(&excludes, fname, path);
}

static int
check_patlist(struct pathead *pathead, const char *fname, const char *path)
{
        struct patlist *e;

        /* fnmatch(3) has a funny return value convention... */
#define MATCH(g, n) (fnmatch((g), (n), FNM_PATHNAME) == 0)

        LIST_FOREACH(e, pathead, link) {
                if ((e->pathname && MATCH(e->glob, path))
                    || MATCH(e->glob, fname))
                        return 1;
        }
        return 0;
}


