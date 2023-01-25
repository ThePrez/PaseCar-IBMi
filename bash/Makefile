BUILDLIB:=PASECAR
DIR:=$(shell pwd)


.PHONY: cleanlib

cleanlib:
	system "dltlib ${BUILDLIB}" || echo "library ${BUILDLIB} not deleted"

/qsys.lib/${BUILDLIB}.lib:
	system "crtlib ${BUILDLIB}" || system "clrlib ${BUILDLIB}"
	/QOpenSys/usr/bin/system -Kkpiebv "CHGOBJOWN OBJ(QSYS/${BUILDLIB}) OBJTYPE(*LIB) NEWOWN(QSYS) CUROWNAUT(*REVOKE)"

/qsys.lib/${BUILDLIB}.lib/bash.pgm: /qsys.lib/${BUILDLIB}.lib bash.C
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/BASH) SRCSTMF('${DIR}/bash.c') DEFINE(DO_BASH) SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/BASH) MODULE(${BUILDLIB}/BASH) USRPRF(*USER) TEXT('Bash Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"

/qsys.lib/${BUILDLIB}.lib/sh.pgm: /qsys.lib/${BUILDLIB}.lib bash.C
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/SH) SRCSTMF('${DIR}/bash.c') SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/SH) MODULE(${BUILDLIB}/SH) USRPRF(*USER) TEXT('sh Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"


/qsys.lib/${BUILDLIB}.lib/%.cmd: /qsys.lib/${BUILDLIB}.lib/%.pgm
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMD CMD(${BUILDLIB}/$*) PGM(${BUILDLIB}/$*) SRCSTMF('${DIR}/$*.cmdsrc') THDSAFE(*YES) TEXT('$*')"


all: /qsys.lib/${BUILDLIB}.lib/bash.cmd /qsys.lib/${BUILDLIB}.lib/sh.cmd