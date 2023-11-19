# slock2 - simple screen locker
# See LICENSE file for copyright and license details.

include config.mk

SRC = slock2.c ${COMPATSRC}
OBJ = ${SRC:.c=.o}

all: slock2

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk arg.h util.h

config.h:
	cp config.def.h $@

slock2: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f slock2 ${OBJ} slock2-${VERSION}.tar.gz

dist: clean
	mkdir -p slock2-${VERSION}
	cp -R LICENSE Makefile README slock2.1 config.mk \
		${SRC} config.def.h arg.h util.h slock2-${VERSION}
	tar -cf slock2-${VERSION}.tar slock2-${VERSION}
	gzip slock2-${VERSION}.tar
	rm -rf slock2-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f slock2 ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/slock2
	chmod u+s ${DESTDIR}${PREFIX}/bin/slock2
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" <slock2.1 >${DESTDIR}${MANPREFIX}/man1/slock2.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/slock2.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/slock2
	rm -f ${DESTDIR}${MANPREFIX}/man1/slock2.1

.PHONY: all clean dist install uninstall
