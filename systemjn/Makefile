BUILDLIB:=PASECAR
DIR:=$(shell pwd)

.PHONY: cleanlib

cleanlib:
	system "dltlib ${BUILDLIB}" || system "clrlib ${BUILDLIB}"

/qsys.lib/${BUILDLIB}.lib:
	system "crtlib ${BUILDLIB}" || system "clrlib ${BUILDLIB}"
	/QOpenSys/usr/bin/system -Kkpiebv "CHGOBJOWN OBJ(QSYS/${BUILDLIB}) OBJTYPE(*LIB) NEWOWN(QSYS) CUROWNAUT(*REVOKE)"

/qsys.lib/${BUILDLIB}.lib/systemjn.pgm: /qsys.lib/${BUILDLIB}.lib systemjn.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/SYSTEMJN) SRCSTMF('${DIR}/systemjn.c') TGTCCSID(37) TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/SYSTEMJN) MODULE(${BUILDLIB}/SYSTEMJN) USRPRF(*USER) TEXT('BoB system utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"

all: /qsys.lib/${BUILDLIB}.lib/systemjn.pgm