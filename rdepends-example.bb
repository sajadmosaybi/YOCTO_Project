SUMMARY = "Logger Code Program"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://logger.sh"
S = "${WORKDIR}"

python do_display_banner() {
    bb.plain("***********************************************");
    bb.plain("*                                             *");
    bb.plain("*  Logger Code Build Running...              *");
    bb.plain("*                                             *");
    bb.plain("***********************************************");
}
addtask display_banner before do_build 

RDEPENDS:${PN} = "bash"
do_install(){
    install -d ${D}${bindir}
    install -m 0755 ${S}/logger.sh ${D}${bindir}/
}