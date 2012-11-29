#!/bin/sh

cat << "xxEOFxx"
#summary Wikified version of the mtree man pages
#labels Featured

Man page for mtree(8):
{{{
xxEOFxx

if [ `uname -s` = 'Darwin' ]; then
    echo This doesn\'t work on Mac OS 1>&2
    exit 1
fi
zcat /usr/share/man/man8/mtree.8.gz | groff -r LL=100n -r LT=100n -Tlatin1 -man - | sed -r -e 's/.\x08(.)/\1/g' -e 's/[[0-9]+m//g' 

cat << "xxEOFxx"
}}}
Man page for mtree(5):
{{{
xxEOFxx

if [ `uname -s` = 'Darwin' ]; then
    echo This doesn\'t work on Mac OS 1>&2
    exit 1
fi
zcat /usr/share/man/man5/mtree.5.gz | groff -r LL=100n -r LT=100n -Tlatin1 -man - | sed -r -e 's/.\x08(.)/\1/g' -e 's/[[0-9]+m//g' 

cat << "xxEOFxx"
}}}
xxEOFxx
