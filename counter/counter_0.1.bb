SUMMARY = "Counter Code Program"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://counter.c"
S = "${WORKDIR}/build"

python do_display_banner() {
    bb.plain("***********************************************");
    bb.plain("*                                             *");
    bb.plain("*  Counter Code Build Running...              *");
    bb.plain("*                                             *");
    bb.plain("***********************************************");
}
addtask display_banner before do_build

do_compile(){
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/counter.c -o ${S}/counter
}
do_install(){
    install -d ${D}${bindir}
    install -m 0755 ${S}/counter ${D}${bindir}/
}