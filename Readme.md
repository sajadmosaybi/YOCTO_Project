
# meta-mylayer
This is a custom Yocto layer that contains example recipes and configurations.

## How to Create the Layer
From your Yocto build directory:
```sh
source oe-init-build-env
bitbake-layers create-layer ../sources/meta-mylayer
```

This creates the standard layout:
```
meta-mylayer/
├── conf/
│   └── layer.conf
├── COPYING.MIT
├── README.md
└── recipes-example/
    └── example/
        └── example_0.1.bb
```

## How to Add the Layer
Enable it in your build:
```sh
bitbake-layers add-layer ../sources/meta-mylayer
```
Or manually add it to `conf/bblayers.conf`.

## Layer Configuration (layer.conf)
**Location:** `meta-mylayer/conf/layer.conf`
```
# We have a conf and classes directory, add to BBPATH
BBPATH .= ":${LAYERDIR}"

# We have recipes-* directories, add to BBFILES
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
            ${LAYERDIR}/recipes-*/*/*.bbappend"

BBFILE_COLLECTIONS += "meta-mylayer"
BBFILE_PATTERN_meta-mylayer = "^${LAYERDIR}/"
BBFILE_PRIORITY_meta-mylayer = "6"

LAYERDEPENDS_meta-mylayer = "core"
LAYERSERIES_COMPAT_meta-mylayer = "kirkstone"
```
- `BBFILE_PRIORITY`: Layer priority for conflicting recipes.
- `BBFILES`: Path for BitBake to find recipes.
- `LAYERDEPENDS`: Layers this layer depends on.
- `LAYERSERIES_COMPAT`: Compatible Yocto releases.

## Example Recipe (example_0.1.bb)

**Location:** `meta-mycustomlayer/recipes-example/example/example_0.1.bb`
```
SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

python do_display_banner() {
    bb.plain("***********************************************");
    bb.plain("*                                             *");
    bb.plain("*  Example recipe created by bitbake-layers   *");
    bb.plain("*                                             *");
    bb.plain("***********************************************");
}
addtask display_banner before do_build
```
## How to Compile Example Recipe
```
bitbake example
```
## How to Add Content
Put recipes under `recipes-*/*/*.bb` and edit `layer.conf` as needed.

## Notes
* Layers should start with `meta-` by convention.
* For detailed documentation, visit [Yocto Project Layers](https://docs.yoctoproject.org/dev-manual/layers.html).
