SUMMARY = "Simple Makefile Application"
LICENSE = "CLOSED"

SRC_URI = "file://main.c \
           file://Makefile"

S = "${WORKDIR}"


do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 myapp ${D}${bindir}
}