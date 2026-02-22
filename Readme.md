# ListTasks -- Yocto Project Task Explorer

## Overview

ListTasks is a simple utility project designed to explore and understand
BitBake tasks inside the Yocto Project build system.

This project helps embedded Linux developers:

-   View available BitBake tasks
-   Understand task execution flow
-   Inspect dependencies between tasks
-   Debug build problems
-   Learn Yocto internal workflow

------------------------------------------------------------------------

## Initialize Yocto Environment

``` bash
source oe-init-build-env
```

------------------------------------------------------------------------

## Listing All Available Tasks

``` bash
bitbake -c listtasks <recipe-name>
```

Example:

``` bash
bitbake -c listtasks core-image-minimal
```

------------------------------------------------------------------------

## Commonly Used Tasks

  Task           Description
  -------------- ---------------------------
  do_fetch       Downloads source code
  do_unpack      Extracts source archive
  do_patch       Applies patches
  do_configure   Runs configure step
  do_compile     Compiles source
  do_install     Installs to staging
  do_package     Creates packages
  do_rootfs      Generates root filesystem
  do_image       Creates final image

------------------------------------------------------------------------

## Visualizing Task Dependencies

``` bash
bitbake -g <recipe-name>
dot -Tpng task-depends.dot -o tasks.png
```

------------------------------------------------------------------------

## Running a Specific Task

``` bash
bitbake -c <task> <recipe-name>
```

------------------------------------------------------------------------

## Cleaning Tasks

``` bash
bitbake -c clean <recipe>
bitbake -c cleanall <recipe>
```

------------------------------------------------------------------------

## Debugging Task Execution

``` bash
bitbake -v <recipe>
bitbake -f -c <task> <recipe>
```

------------------------------------------------------------------------

## Example Workflow

``` bash
source oe-init-build-env
bitbake -c listtasks busybox
bitbake busybox
bitbake core-image-minimal
```


------------------------------------------------------------------------

## Author

\[Sajad Mosaybi\]\
Embedded Linux & RTOS Instructor\
Specialist in Embedded Systems, Yocto, Buildroot, and STM32 Platforms
