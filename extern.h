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
 *
 *      @(#)extern.h    8.1 (Berkeley) 6/6/93
 * $FreeBSD$
 */

#include <stdio.h>
#include <stdint.h>
#include <fts.h>

extern uint32_t crc_total;

int      crc(int, uint32_t *, off_t *);
void     cwalk(void);
char    *flags_to_string(u_long);

const char      *inotype(u_int);
u_int    parsekey(char *, int *);
char    *rlink(char *);
NODE    *mtree_readspec(FILE *fi);
int     mtree_verifyspec(FILE *fi);
int     mtree_specspec(FILE *fi, FILE *fj);
int     compare(char *name, NODE *s, FTSENT *p);

int     check_includes(const char *, const char *);
int     check_excludes(const char *, const char *);
void    init_patlists(void);
void    read_includes_file(const char *);
void    read_excludes_file(const char *);
const char * ftype(u_int type);

#if !HAVE_GETMODE
mode_t getmode(const void *bbox, mode_t omode);
void *setmode(const char *p);
#endif

#if HAVE_OPENSSL_MD5_H && HAVE_EVP_MD5
char * MD5_File(const char *filename, char *result);
#endif

#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA1
char * SHA1_File(const char *filename, char *result);
#endif
#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA256
char * SHA256_File(const char *filename, char *result);
#endif
#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA384
char * SHA384_File(const char *filename, char *result);
#endif
#if HAVE_OPENSSL_SHA_H && HAVE_EVP_SHA512
char * SHA512_File(const char *filename, char *result);
#endif
#if HAVE_OPENSSL_RIPEMD_H && HAVE_EVP_RIPEMD160
char * RIPEMD160_File(const char *filename, char *result);
#endif

extern int ftsoptions;
extern u_int keys;
extern int lineno;
extern int dflag, eflag, iflag, nflag, qflag, rflag, sflag, uflag, wflag, vflag;
#ifdef MAXPATHLEN
extern char fullpath[MAXPATHLEN];
#endif
