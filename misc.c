/*-
 * Copyright (c) 1991, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if 0
#ifndef lint
static char sccsid[] = "@(#)misc.c      8.1 (Berkeley) 6/6/93";
#endif /*not lint */
#endif

#include "config.h"

#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fts.h>
#include <stdio.h>
#include <unistd.h>

#if HAVE_OPENSSL_MD5_H || HAVE_OPENSSL_SHA_H || HAVE_OPENSSL_RIPEMD_H
#include <openssl/evp.h>
#endif
#ifdef HAVE_OPENSSL_MD5_H
#include <openssl/md5.h>
#endif
#ifdef HAVE_OPENSSL_SHA_H
#include <openssl/sha.h>
#endif
#ifdef HAVE_OPENSSL_RIPEMD_H
#include <openssl/ripemd.h>
#endif

#include "mtree.h"
#include "extern.h"

typedef struct _key {
        const char *name;                       /* key name */
        u_int val;                      /* value */

#define NEEDVALUE       0x01
        u_int flags;
} KEY;

/* NB: the following table must be sorted lexically. */
static KEY keylist[] = {
        {"cksum",       F_CKSUM,        NEEDVALUE},
        {"flags",       F_FLAGS,        NEEDVALUE},
        {"gid",         F_GID,          NEEDVALUE},
        {"gname",       F_GNAME,        NEEDVALUE},
        {"ignore",      F_IGN,          0},
        {"link",        F_SLINK,        NEEDVALUE},
#ifdef HAVE_OPENSSL_MD5_H
        {"md5digest",   F_MD5,          NEEDVALUE},
#endif
        {"mode",        F_MODE,         NEEDVALUE},
        {"nlink",       F_NLINK,        NEEDVALUE},
        {"nochange",    F_NOCHANGE,     0},
        {"optional",    F_OPT,          0},
#ifdef HAVE_OPENSSL_RIPEMD_H
        {"ripemd160digest", F_RMD160,   NEEDVALUE},
#endif
#ifdef HAVE_OPENSSL_SHA_H
        {"sha1",	F_SHA1,		NEEDVALUE},
        {"sha1digest",	F_SHA1,		NEEDVALUE},
        {"sha256",	F_SHA256,	NEEDVALUE},
        {"sha256digest",F_SHA256,	NEEDVALUE},
        {"sha384",	F_SHA384,	NEEDVALUE},
        {"sha384digest",F_SHA384,	NEEDVALUE},
        {"sha512",	F_SHA512,	NEEDVALUE},
        {"sha512digest",F_SHA512,	NEEDVALUE},
#endif
        {"size",        F_SIZE,         NEEDVALUE},
        {"time",        F_TIME,         NEEDVALUE},
        {"type",        F_TYPE,         NEEDVALUE},
        {"uid",         F_UID,          NEEDVALUE},
        {"uname",       F_UNAME,        NEEDVALUE},
};

int keycompare(const void *, const void *);

u_int
parsekey(char *name, int *needvaluep)
{
        KEY *k, tmp;

        tmp.name = name;
        k = (KEY *)bsearch(&tmp, keylist, sizeof(keylist) / sizeof(KEY),
            sizeof(KEY), keycompare);
        if (k == NULL)
                errx(1, "line %d: unknown keyword %s", lineno, name);

        if (needvaluep)
                *needvaluep = k->flags & NEEDVALUE ? 1 : 0;
        return (k->val);
}

int
keycompare(const void *a, const void *b)
{
        return (strcmp(((const KEY *)a)->name, ((const KEY *)b)->name));
}

char *
flags_to_string(u_long fflags)
{
        char *string;

        string = strdup("");
        if (string != NULL && *string == '\0') {
                free(string);
                string = strdup("none");
        }
        if (string == NULL)
                err(1, NULL);

        return string;
}

#define DIGEST_FILE(PREFIX, TYPE)                               \
char *                                                          \
PREFIX ## _File(const char *filename, char *result)             \
{                                                               \
    u_char md[EVP_MAX_MD_SIZE];                                 \
    u_char buf[1024];                                           \
    EVP_MD_CTX *ctx;                                            \
    unsigned int i, mdlen;                                      \
    FILE *fp;                                                   \
    size_t r;                                                   \
                                                                \
    if ((ctx = EVP_MD_CTX_create()) == NULL)                    \
        return NULL;                                            \
    EVP_DigestInit_ex(ctx, EVP_ ## TYPE(), NULL);               \
    if ((fp = fopen(filename, "r")) == NULL) {                  \
        EVP_MD_CTX_destroy(ctx);                                \
        return NULL;                                            \
    }                                                           \
    while ((r = fread(buf, 1, sizeof(buf), fp)) != 0)           \
        EVP_DigestUpdate(ctx, buf, r);                          \
    if (ferror(fp)) {                                           \
        fclose(fp);                                             \
        EVP_MD_CTX_destroy(ctx);                                \
        return NULL;                                            \
    }                                                           \
    fclose(fp);                                                 \
    EVP_DigestFinal_ex(ctx, md, &mdlen);                        \
    for (i = 0; i < mdlen; i++)                                 \
        sprintf(result + 2 * i, "%02x", md[i]);                 \
    EVP_MD_CTX_destroy(ctx);                                    \
    return result;                                              \
}

#if HAVE_OPENSSL_MD5_H && HAVE_EVP_MD5
DIGEST_FILE(MD5, md5);
#endif

#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA1
DIGEST_FILE(SHA1, sha1);
#endif
#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA256
DIGEST_FILE(SHA256, sha256);
#endif
#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA384
DIGEST_FILE(SHA384, sha384);
#endif
#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA512
DIGEST_FILE(SHA512, sha512);
#endif

#if HAVE_OPENSSL_RIPEMD_H && HAVE_EVP_RIPEMD160
DIGEST_FILE(RIPEMD160, ripemd160);
#endif

