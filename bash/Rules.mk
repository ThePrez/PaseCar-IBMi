BASH.MODULE: bash.c
BASHJL.MODULE: bashjl.c
BASH.PGM: BASH.MODULE PASECAR.SRVPGM
BASHJL.PGM: BASHJL.MODULE PASECAR.SRVPGM
BASH.CMD: bash.cmdsrc
PASECARAPI.MODULE: pasecar_api.c
PASECARAP2.MODULE: pasecar_api2.cpp
PASECARHLP.MODULE: pasecar_helpers.c
PASECAR.SRVPGM: pasecar.bnd PASECARAPI.MODULE PASECARAP2.MODULE PASECARHLP.MODULE
#PASECAR.SRVPGM: pasecar.ilesrvpgm PASECARAPI.MODULE PASECARHLP.MODULE 