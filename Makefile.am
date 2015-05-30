
#
# mtree - Utility for creating and verifying file hierarchies
# 

bin_PROGRAMS=		mtree

noinst_HEADERS=		extern.h \
			mtree.h \
			vis.h

man_MANS=		mtree.5 mtree.8

docdir=			$(datadir)/doc/packages/$(PACKAGE)

doc_DATA=		CHANGES COPYING README INSTALL

EXTRA_DIST=		CHANGES mtree.5 mtree.8 mtree.spec

mtree_SOURCES=		compare.c \
			crc.c \
			create.c \
			excludes.c \
			misc.c \
			mtree.c \
			setmode.c \
			spec.c \
			specspec.c \
			unvis.c \
			verify.c \
			vis.c

