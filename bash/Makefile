BUILDLIB:=PASECAR
DIR:=$(shell pwd)


.PHONY: cleanlib

cleanlib:
	system "dltlib ${BUILDLIB}" || system "clrlib ${BUILDLIB}"

/qsys.lib/${BUILDLIB}.lib:
	system "crtlib ${BUILDLIB}" || system "clrlib ${BUILDLIB}"
	/QOpenSys/usr/bin/system -Kkpiebv "CHGOBJOWN OBJ(QSYS/${BUILDLIB}) OBJTYPE(*LIB) NEWOWN(QSYS) CUROWNAUT(*REVOKE)"

/qsys.lib/${BUILDLIB}.lib/bash.pgm: /qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm bash.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/BASH) SRCSTMF('${DIR}/bash.c') DEFINE(DO_BASH) SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/BASH) BNDSRVPGM(${BUILDLIB}/PASECAR) MODULE(${BUILDLIB}/BASH) USRPRF(*USER) TEXT('Bash Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"

/qsys.lib/${BUILDLIB}.lib/sh.pgm: /qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm /qsys.lib/${BUILDLIB}.lib bash.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/SH) SRCSTMF('${DIR}/bash.c') DEFINE(DO_BASH) SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/SH) BNDSRVPGM(${BUILDLIB}/PASECAR) MODULE(${BUILDLIB}/SH) USRPRF(*USER) TEXT('sh Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"

/qsys.lib/${BUILDLIB}.lib/pasecarapi.module: /qsys.lib/${BUILDLIB}.lib pasecar_api.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/PASECARAPI) SRCSTMF('${DIR}/pasecar_api.c') DEFINE(DO_BASH) SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"

/qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm: /qsys.lib/${BUILDLIB}.lib/pasecarapi.module
	/QOpenSys/usr/bin/system -Kkpiebv "CRTSRVPGM SRVPGM(${BUILDLIB}/PASECAR) MODULE(${BUILDLIB}/PASECARAPI) SRCSTMF('${DIR}/pasecar_api.exportsrc') USRPRF(*USER)  TEXT('sh Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"


/qsys.lib/${BUILDLIB}.lib/%.cmd: /qsys.lib/${BUILDLIB}.lib/%.pgm
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMD CMD(${BUILDLIB}/$*) PGM(${BUILDLIB}/$*) SRCSTMF('${DIR}/$*.cmdsrc') THDSAFE(*YES) TEXT('$*')"


all: /qsys.lib/${BUILDLIB}.lib/bash.cmd /qsys.lib/${BUILDLIB}.lib/sh.cmd /qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm