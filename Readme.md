# Runtime Dependencies in the Yocto Project

## 🔹What is a Runtime Dependency in Yocto?
In the Yocto Project, a runtime dependency means:

A package that must be installed on the target system for another package to work correctly at runtime.

It is different from:
- Build dependency → needed only during compilation
- Runtime dependency → needed on the final target device

In Yocto, runtime dependencies are defined using ```RDEPENDS:${PN}```
## 🔹Practical Example
We will create:
- A simple program called logger
- It depends on ```bash```
- We will define it as a runtime dependency
- Then build an image and test it

## 🔹Step-by-Step Example
### ✅ Step 1  — Create a Simple Recipe
Inside your layer:
```bash
rdepends-example/
├── files
│   └── logger.sh
└── rdepends-example.bb
```

Create the file:
```bash
mkdir -p meta-mycustom-layer/recipes-example/rdepends-example/files
nano meta-mycustom-layer/recipes-example/rdepends-example/files/logger.sh
nano meta-mycustom-layer/recipes-example/rdepends-example/rdepends-example.bb
```

### ✅ Step 2 — Write the script
#### logger.sh
```bash
#!/bin/sh

# ==============================
# Real-Time System Monitor
# ==============================

while true
do
    clear
    echo "======================================"
    echo "        SYSTEM MONITOR (LIVE)"
    echo "======================================"
    echo "Date: $(date)"
    echo

    echo "----- CPU LOAD -----"
    uptime
    echo

    echo "----- MEMORY USAGE -----"
    free -h
    echo

    echo "----- DISK USAGE -----"
    df -h /
    echo

    echo "----- TOP PROCESSES -----"
    ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -10
    echo

    sleep 5
done
```
### ✅ Step 3 — Write the Recipe
#### rdepends-example.bb
```bash
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
```
## 🔹 Explanation
```RDEPENDS:${PN} += "bash"```

This means:

👉 When installing hello-app into the image

👉 The package bash must also be installed automatically

So if someone installs this package, Yocto will include bash in the image.

## 🔹 Build the Package
```bash
bitbake rdepends-example
```
## 🔹 Add Package to Image
Edit your conf/local.conf:
```bash
IMAGE_INSTALL:append = " rdepends-example"
```
## 🔹 Verify Runtime Dependency 
```bash
bitbake -e rdepends-example | grep ^RDEPENDS
```
If everything is correct, you should see the expected output.
```bash
embedded@embedded-HP-EliteDesk-800-G1-SFF:~/Documents/yocto/STM32MP1$ bitbake -e rdepends-example | grep ^RDEPENDS
RDEPENDS:${KERNEL_PACKAGE_NAME}-base=""
RDEPENDS:rdepends-example="bash"
RDEPENDS:rdepends-example-dev="rdepends-example (= 1.0-r0)"
RDEPENDS:rdepends-example-staticdev="rdepends-example-dev (= 1.0-r0)"
```
## Author

**Sajad Mosaybi**  
Embedded Linux Developer  
Specialization: Embedded Systems, Yocto Project, Buildroot, STM32, Linux Kernel Development  

Project: Yocto Project Runtime Dependency Example  
Year: 2026

## References

1. Yocto Project Documentation  
   https://docs.yoctoproject.org/

2. Yocto Project Mega-Manual  
   https://docs.yoctoproject.org/singleindex.html

3. BitBake User Manual  
   https://docs.yoctoproject.org/bitbake/

4. OpenEmbedded Documentation  
   https://www.openembedded.org/wiki/Main_Page

5. Embedded Linux Development with the Yocto Project  
   Authors: Rudolf J. Streif, et al.

6. Mastering Embedded Linux Programming  
   Author: Chris Simmonds  
   Publisher: Packt Publishing
