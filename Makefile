PROG=		patmat
SRCS+=		patmat.c patterns.c utils.c
MAN=		patmat-patterns.7

#DEBUG=		-g -DDEBUG=3 -O0
CFLAGS+=	-std=c99
CFLAGS+=	-Wall -I${.CURDIR}
CFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=	-Wmissing-declarations
CFLAGS+=	-Wshadow -Wpointer-arith
CFLAGS+=	-Wsign-compare

README.md: patmat.1
	mandoc -Thtml -Ofragment patmat.1 > ${@}

.include <bsd.prog.mk>
