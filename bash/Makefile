BUILDLIB:=PASECAR
DIR:=$(shell pwd)


.PHONY: cleanlib

cleanlib:
	system "dltlib ${BUILDLIB}" || system "clrlib ${BUILDLIB}"

/qsys.lib/${BUILDLIB}.lib:
	system "crtlib ${BUILDLIB}" || system "clrlib ${BUILDLIB}"
	/QOpenSys/usr/bin/system -Kkpiebv "CHGOBJOWN OBJ(QSYS/${BUILDLIB}) OBJTYPE(*LIB) NEWOWN(QSYS) CUROWNAUT(*REVOKE)"

/qsys.lib/${BUILDLIB}.lib/bash.pgm: /qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm bash.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/BASH) SRCSTMF('${DIR}/bash.c') SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/BASH) BNDSRVPGM(${BUILDLIB}/PASECAR) MODULE(${BUILDLIB}/BASH) USRPRF(*USER) TEXT('Bash Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"

/qsys.lib/${BUILDLIB}.lib/bashjl.pgm: /qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm /qsys.lib/${BUILDLIB}.lib bash.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/BASHJL) SRCSTMF('${DIR}/bash.c') DEFINE(JOBLOG_ONLY) SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/BASHJL) BNDSRVPGM(${BUILDLIB}/PASECAR) MODULE(${BUILDLIB}/BASHJL) USRPRF(*USER) TEXT('Bash Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"

/qsys.lib/${BUILDLIB}.lib/test.pgm: /qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm /qsys.lib/${BUILDLIB}.lib test.rpgle
	setccsid 819 ${DIR}/test.rpgle
	/QOpenSys/usr/bin/system -Kkpiebv "CRTRPGMOD MODULE(${BUILDLIB}/TEST) SRCSTMF('${DIR}/test.rpgle')  TGTRLS(${TGTRLS})"
	/QOpenSys/usr/bin/system -Kkpiebv "CRTPGM PGM(${BUILDLIB}/TEST) BNDSRVPGM(${BUILDLIB}/PASECAR) MODULE(${BUILDLIB}/test) TGTRLS(${TGTRLS})"

/qsys.lib/${BUILDLIB}.lib/pasecarapi.module: /qsys.lib/${BUILDLIB}.lib pasecar_api.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/PASECARAPI) SRCSTMF('${DIR}/pasecar_api.c')  SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"
/qsys.lib/${BUILDLIB}.lib/pasecarap2.module: /qsys.lib/${BUILDLIB}.lib pasecar_api2.cpp
	/QOpenSys/usr/bin/system -Kkpebv "CRTCppMOD MODULE(${BUILDLIB}/PASECARAP2) SRCSTMF('${DIR}/pasecar_api2.cpp')  SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"

/qsys.lib/${BUILDLIB}.lib/pasecarhlp.module: /qsys.lib/${BUILDLIB}.lib pasecar_helpers.c
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMOD MODULE(${BUILDLIB}/PASECARHLP) SRCSTMF('${DIR}/pasecar_helpers.c') SYSIFCOPT(*IFS64IO) TERASPACE(*YES *TSIFC) TGTCCSID(37) TGTRLS(${TGTRLS})"

/qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm: /qsys.lib/${BUILDLIB}.lib/pasecarapi.module /qsys.lib/${BUILDLIB}.lib/pasecarap2.module /qsys.lib/${BUILDLIB}.lib/pasecarhlp.module
	/QOpenSys/usr/bin/system -Kkpiebv "CRTSRVPGM SRVPGM(${BUILDLIB}/PASECAR) MODULE(${BUILDLIB}/PASECARAPI ${BUILDLIB}/PASECARAP2 ${BUILDLIB}/PASECARHLP) SRCSTMF('${DIR}/pasecar.bnd') USRPRF(*USER)  TEXT('sh Utility') TGTRLS(${TGTRLS}) ACTGRP(*CALLER)"


/qsys.lib/${BUILDLIB}.lib/%.cmd: /qsys.lib/${BUILDLIB}.lib/%.pgm
	/QOpenSys/usr/bin/system -Kkpiebv "CRTCMD CMD(${BUILDLIB}/$*) PGM(${BUILDLIB}/$*JL) SRCSTMF('${DIR}/$*.cmdsrc') THDSAFE(*YES) TEXT('$*')"


all: /qsys.lib/${BUILDLIB}.lib/bash.cmd /qsys.lib/${BUILDLIB}.lib/bashjl.pgm /qsys.lib/${BUILDLIB}.lib/pasecar.srvpgm /qsys.lib/${BUILDLIB}.lib/test.pgm