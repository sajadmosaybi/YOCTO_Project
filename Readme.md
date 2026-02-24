# Step-by-Step Tutorial: Using CMake in Yocto

##  Overview
This guide explains how to integrate a CMake-based C application (example: UDP server) into the Yocto Project.

It covers:
- Creating a CMake project
- Writing a Yocto recipe
- Using the cmake class
- Building with bitbake
- Adding the application to an image

---

##  Example Project Structure

Your application should look like this:
```bash
udp-server/
    ├── CMakeLists.txt
    ├── udp_server.c.C
```
When used in Yocto, it must be placed inside:
```bash
    udp-server/
        ├── files
        │   ├── CMakeLists.txt
        │   └── udp_server.c
        └── udp-server_1.0.bb
```
---

##  Example CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(udp_server C)

set(CMAKE_C_STANDARD 11)

add_executable(udp_server src/main.c)

install(TARGETS udp_server
        RUNTIME DESTINATION bin)
```

Important:
- Always use install()
- Do NOT hardcode compilers
- Let Yocto provide toolchain

---

##  Example Yocto Recipe (udp-server_1.0.bb)

```bitbake
SUMMARY = "Advanced UDP Server using CMake"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://CMakeLists.txt \
           file://src/main.c"

S = "${WORKDIR}"

inherit cmake

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release"
```

Key Points:
- Use ```inherit cmake```
- Source files must be inside ```files/```
- ```S = "${WORKDIR}"``` is required

---

##  Build the Application
```bash
   source oe-init-build-env
   bitbake udp-server
```
---

##  Add to Image

Add to your image recipe:

```IMAGE_INSTALL:append = " udp-server"```

Then rebuild image:

```bitbake core-image-minimal```

---

##  Clean Build (If Needed)

```bash
bitbake -c clean udp-server
bitbake udp-server
```

---

##  Common Errors

- File not found → ensure files are inside ```files/```
- do_fetch error → check ```SRC_URI``` path
- Toolchain errors → ensure ```inherit cmake``` is used

---
##  Author

**Author:** Sajad Mosaybi

**Date:** 2026  

**Purpose:** Educational guide for integrating CMake-based C applications into the Yocto Project.

---

##  References

1. Yocto Project Documentation  
   https://docs.yoctoproject.org/

2. Yocto Project Development Manual  
   https://docs.yoctoproject.org/dev-manual/

3. Yocto CMake Class Documentation (`cmake.bbclass`)  
   https://docs.yoctoproject.org/ref-manual/classes.html

4. CMake Official Documentation  
   https://cmake.org/documentation/

5. BitBake User Manual  
   https://docs.yoctoproject.org/bitbake/

---
