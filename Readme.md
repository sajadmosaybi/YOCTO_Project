
# Variable Assignment in Yocto

This repository provides an overview of **variable assignment** in the Yocto Project. Variables in Yocto are used to configure builds, recipes, and package settings. Understanding variable assignment is essential for customizing your embedded Linux builds.

---

## Yocto Variable Assignment Operators

This document provides an overview of variable assignment operators in Yocto, their behavior, and how they are used.

---

## 1. `?=`
- Assigns a **default value** to a variable.
- Can be **overridden** later.
```bitbake
VAR ?= "foo"
VAR ?= "bar"
VAR ?= "val"
VAR ?= "var"
# The final value is TEST="foo" 
```

## 2. `??=`
- Assigns a **default value** to a variable as a **weak assignment**.
- Can be overridden.
- If multiple assignments occur, the **last one** is considered.
```bitbake
VAR ??= "foo"
VAR ??= "bar"
VAR ??= "val"
VAR ??= "var"

# The final value is TEST="var"

VAR ??= "foo"
VAR ?= "bar"
VAR ?= "val"
VAR ??= "var"

# The final value is TEST="bar" 
```

## 3. `=`
- Simple variable assignment.
- Requires quotes if spaces are present.
- Variables are **expanded at the end**.
```bitbake
# Override
A ?= "foo"
A = "bar"

# The final value is A="bar" 

# Variable Expansion
A = "foo"
B = "${A}"
A = "bar"

# The final value is B="bar" 
```

## 4. `:=`
- **Immediate variable expansion**.
- The value is expanded **immediately** at the point of assignment.
```bitbake
MY_VAR := "ImmediateValue"
```

## 5. `+=`
- Appends a value to a variable.
- Inserts a **space** between the existing value and the appended value.
- Takes effect immediately.
```bitbake
MY_VAR += " Appended"
```

## 6. `=+`
- Prepends a value to a variable.
- Inserts a **space** between the prepended value and the existing value.
- Takes effect immediately.
```bitbake
MY_VAR =+ "Prepended "
```

## 7. `.= `
- Appends a value to a variable.
- **No space** is inserted.
- Takes effect immediately.
```bitbake
MY_VAR .= "AppendedNoSpace"
```

## 8. `=.`
- Prepends a value to a variable.
- **No space** is inserted.
- Takes effect immediately.
```bitbake
MY_VAR =. "PrependedNoSpace"
```

## 9. `:append`
- Appends a value to a variable.
- **No space** is inserted.
- Effects are applied **at variable expansion time**, not immediately.
```bitbake
MY_VAR:append = "AppendedLater"
```

## 10. `:prepend`
- Prepends a value to a variable.
- **No space** is inserted.
- Effects are applied **at variable expansion time**.
```bitbake
MY_VAR:prepend = "PrependedLater"
```

## 11. `:remove`
- Removes values from a list variable.
- All occurrences of the specified value are removed.
```bitbake
MY_VAR:remove = "ValueToRemove"
```

---

## Examples

### Modifying `IMAGE_INSTALL`
```bitbake
IMAGE_INSTALL += "vim git"
IMAGE_INSTALL_append = " htop"
IMAGE_INSTALL_prepend = "nano "
```
---

## References
- [Yocto Project Mega-Manual: Variable Assignment](https://www.yoctoproject.org/docs/3.1/mega-manual/mega-manual.html#varassign)

---

## License
This repository is open-source and can be freely used and modified.
