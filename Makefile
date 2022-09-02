# s1stine's suckless fork installer
# provides dwm and dwmblocks

# See LICENSE file in each folders for copyright and license details.

include config.mk

SRC = dwm/drw.c dwm/dwm.c dwm/util.c
OBJ = ${SRC:.c=.o}
# OBJ = drw.o dwm.o util.o

all: options dwm dwmblocks

options:
	@echo dwm and dwmblocks build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp dwm/config.def.h dwm/config.h
	cp dwmblocks/blocks.def.h dwmblocks/blocks.h

dwm: ${OBJ}
	mv *.o dwm
	${CC} -o $@/$@ ${OBJ} ${LDFLAGS}

dwmblocks: ${OBJ}
	${CC} -o $@/$@ ${OBJ} ${LDFLAGS}

clean:
	rm -f *.gch dwmblocks/dwmblocks dwm/dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm/dwm ${DESTDIR}${PREFIX}/bin
	cp -f dwmblocks/dwmblocks ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwmblocks
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm/dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	cp -f dwm/dwm.desktop /usr/share/xsessions
	chmod 755 /usr/share/xsessions/dwm.desktop

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1\
		/usr/share/xsessions/dwm.desktop\
		${DESTDIR}${PREFIX}/bin/dwmblocks

def:
	rm -f dwm/config.h
	rm -f dwmblocks/blocks.h

.PHONY: all options clean dist install uninstall def
