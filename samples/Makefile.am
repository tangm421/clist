
#AM_CFLAGS = -I$(top_srcdir)/clist

bin_PROGRAMS = sample

sample_CFLAGS = -I$(top_srcdir)/clist
sample_SOURCES = test.c
sample_LDADD = ../clist/libclist.la

sample_CPPFLAGS = -D_BINDIR='"$(bindir)"'

nodist_sample_SOURCES = mydefines.h
BUILT_SOURCES = mydefines.h
CLEANFILES = mydefines.h
mydefines.h: Makefile
	echo '#define INSTALL_BINDIR "$(bindir)"' > $@






