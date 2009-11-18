
N2N_VERSION="2.0.0"

########

CC=gcc
DEBUG?=-g3
WARN?=-Wall -Wshadow -Wpointer-arith -Wmissing-declarations -Wnested-externs

#Ultrasparc64 users experiencing SIGBUS should try the following gcc options
#(thanks to Robert Gibbon)
PLATOPTS_SPARC64=-mcpu=ultrasparc -pipe -fomit-frame-pointer -ffast-math -finline-functions -fweb -frename-registers -mapp-regs

N2N_DEFINES=
# If AES needs to be conditional
#N2N_DEFINES+="-DN2N_HAVE_AES"

CFLAGS+=$(DEBUG) $(WARN) $(OPTIONS) $(PLATOPTS) $(N2N_DEFINES)

INSTALL=install
MKDIR=mkdir -p

INSTALL_PROG=$(INSTALL) -m755
INSTALL_DOC=$(INSTALL) -m644


# DESTDIR set in debian make system
PREFIX?=$(DESTDIR)/usr
#BINDIR=$(PREFIX)/bin
SBINDIR=$(PREFIX)/sbin
MANDIR?=$(PREFIX)/share/man
MAN1DIR=$(MANDIR)/man1
MAN7DIR=$(MANDIR)/man7
MAN8DIR=$(MANDIR)/man8

N2N_LIB=n2n.a
N2N_OBJS=n2n.o n2n_keyfile.o wire.o minilzo.o twofish.o \
         transform_null.o transform_tf.o transform_aes.o \
         tuntap_freebsd.o tuntap_netbsd.o tuntap_linux.o tuntap_osx.o version.o
LIBS_EDGE=-lcrypto
LIBS_SN=

#For OpenSolaris (Solaris too?)
ifeq ($(shell uname), SunOS)
LIBS_EDGE+=-lsocket -lnsl
LIBS_SN+=-lsocket -lnsl
endif

APPS=edge
APPS+=supernode

DOCS=edge.8.gz supernode.1.gz n2n_v2.7.gz

all: $(APPS) $(DOCS)

edge: edge.c $(N2N_LIB) n2n_wire.h n2n.h Makefile
	$(CC) $(CFLAGS) edge.c $(N2N_LIB) $(LIBS_EDGE) -o edge

test: test.c $(N2N_LIB) n2n_wire.h n2n.h Makefile
	$(CC) $(CFLAGS) test.c $(N2N_LIB) $(LIBS_EDGE) -o test

supernode: sn.c $(N2N_LIB) n2n.h Makefile
	$(CC) $(CFLAGS) sn.c $(N2N_LIB) $(LIBS_SN) -o supernode

.c.o: n2n.h n2n_keyfile.h n2n_transforms.h n2n_wire.h twofish.h Makefile
	$(CC) $(CFLAGS) -c $<

%.gz : %
	gzip -c $< > $@

$(N2N_LIB): $(N2N_OBJS)
	ar rcs $(N2N_LIB) $(N2N_OBJS)
#	$(RANLIB) $@

version.c:
	@echo "---- Version $(N2N_VERSION) ----"
	@echo $(N2N_VERSION) | sed -e 's/.*/const char * n2n_sw_version   = "&";/' > version.c
	@uname -p | sed -e 's/.*/const char * n2n_sw_osName    = "&";/' >> version.c
	@date +"%D %r" | sed -e 's/.*/const char * n2n_sw_buildDate = "&";/' >> version.c

clean:
	rm -rf $(N2N_OBJS) $(N2N_LIB) $(APPS) $(DOCS) test *.dSYM *~ version.c

install: edge supernode edge.8.gz supernode.1.gz n2n_v2.7.gz
	echo "MANDIR=$(MANDIR)"
	$(MKDIR) $(SBINDIR) $(MAN1DIR) $(MAN7DIR) $(MAN8DIR)
	$(INSTALL_PROG) supernode $(SBINDIR)/
	$(INSTALL_PROG) edge $(SBINDIR)/
	$(INSTALL_DOC) edge.8.gz $(MAN8DIR)/
	$(INSTALL_DOC) supernode.1.gz $(MAN1DIR)/
	$(INSTALL_DOC) n2n_v2.7.gz $(MAN7DIR)/
