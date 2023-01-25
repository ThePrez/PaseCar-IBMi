
BASH.MODULE: bash.c
SH.MODULE: bash.c
BASH.PGM: bash.ilepgm BASH.MODULE
SH.PGM: bash.ilepgm SH.MODULE
BASH.CMD: bash.cmdsrc
BASH.CMD: private PGM := PASECAR/BASH
SH.CMD: sh.cmdsrc
SH.CMD: private PGM := PASECAR/SH