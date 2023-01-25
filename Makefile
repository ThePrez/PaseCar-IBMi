BUILDLIB:=PASECAR
.PHONY: bash 
bash:
	$(MAKE) -C bash cleanlib all


appinstall.jar: /QOpenSys/pkgs/bin/wget
	/QOpenSys/pkgs/bin/wget -O appinstall.jar https://github.com/ThePrez/AppInstall-IBMi/releases/download/v0.0.3/appinstall-v0.0.3.jar

pasecar-installer-v%.zip: bash appinstall.jar
	echo "Building version $*"
	system "dltlib ${BUILDLIB}" || echo "could not delete"
	system "crtlib ${BUILDLIB}"
	system "dltlib ${BUILDLIB}"
	gmake -C bash BUILDVERSION="$*" all
	/QOpenSys/QIBM/ProdData/JavaVM/jdk80/64bit/bin/java -jar appinstall.jar --qsys ${BUILDLIB} -o $@

all: bash