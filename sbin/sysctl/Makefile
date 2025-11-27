#	$OpenBSD: Makefile,v 1.15 2025/01/30 20:02:13 kn Exp $

PROG=	sysctl
MAN=	sysctl.8

<<<<<<< HEAD
CPPFLAGS+=     -I${.CURDIR}/../../sys # XXX
||||||| 6d253f95424
CPPFLAGS+=	-D_LIBKVM
=======
CPPFLAGS+=	-D_LIBKVM
CPPFLAGS+=	-I${.CURDIR}/../../sys # XXX
>>>>>>> d0112b2a62c03920ac11376d51d880c7e9a6b383

afterinstall:
	ln -sf ../../sbin/sysctl ${DESTDIR}/usr/sbin
	chown -h ${BINOWN}:${BINGRP} ${DESTDIR}/usr/sbin/sysctl

.include <bsd.prog.mk>
