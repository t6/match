PROG=		match
SRCS+=		match.c patterns.c utils.c
MAN=		patterns.7

#DEBUG=		-g -DDEBUG=3 -O0
CFLAGS+=	-Wall -I${.CURDIR}
CFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=	-Wmissing-declarations
CFLAGS+=	-Wshadow -Wpointer-arith
CFLAGS+=	-Wsign-compare

MAN_BASE?=	http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man%S/%N.%S?query=%N&sec=%S

README.md: match.1
	mandoc -Thtml -Ofragment -Oman="${MAN_BASE}" ${PWD}/match.1 > ${@}

.include <bsd.prog.mk>
