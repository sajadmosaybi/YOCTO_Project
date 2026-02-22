
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
VAR1 ?= "1"
VAR1 ?= "2"
VAR1 ?= "3"
VAR1 ?= "4"
# The final value is VAR1="1" 
```

## 2. `??=`
- Assigns a **default value** to a variable as a **weak assignment**.
- Can be overridden.
- If multiple assignments occur, the **last one** is considered.
```bitbake
VAR2 ??= "1"
VAR2 ??= "2"
VAR2 ??= "3"
VAR2 ??= "4"

# The final value is VAR2="4"

VAR3 ??= "1"
VAR3 ?= "2"
VAR3 ?= "3"
VAR3 ??= "4"

# The final value is VAR3="2" 
```

## 3. `=`
- Simple variable assignment.
- Requires quotes if spaces are present.
- Variables are **expanded at the end**.
```bitbake
# Override
A ?= "1"
A = "2"

# The final value is A="2" 

# Variable Expansion
A = "1"
B = "${A}"
A = "2"

# The final value is B="2" 
```

## 4. `:=`
- **Immediate variable expansion**.
- The value is expanded **immediately** at the point of assignment.
```bitbake
# Override
A ?= "foo"
A := "bar"

# The final value is A="bar" 

# Variable Expansion
A = "foo"
B := "${A}"
A = "bar"
# The final value is B="foo" 
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
# Spaces are added here

# Append
A = "foo"
A += "bar"

# The final value is A="foo bar" 

# Prepend
B = "foo"
B =+ "bar"

# The final value is B="bar foo"

# Append
A ?= "val"
A += "var"

# The final value is A="val var"

# Prepend
B ??= "val"
B =+ "var"

# The final value is B="var"
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
# Append
A = "foo"
A .= "bar"

# The final value is A="foobar" 

# Prepend
B = "foo"
B =. "bar"

# The final value is B="barfoo"
```

## 9. `:append`
- Appends a value to a variable.
- **No space** is inserted.
- Effects are applied **at variable expansion time**, not immediately.
```bitbake
# Append
A = "foo"
A:append = "bar"
# The final value is A="foobar" 

# Append
A = "foo"
A:append = "bar"
A += "val"
# The final value is A="foo valbar" 

# Append
A = "foo"
A:append = " bar"
# The final value is A="foo bar" 
```

## 10. `:prepend`
- Prepends a value to a variable.
- **No space** is inserted.
- Effects are applied **at variable expansion time**.
```bitbake
# Prepend
A = "foo"
A:prepend = "bar"
# The final value is A="barfoo" 

# Prepend
A = "foo"
A:prepend = "bar"
A =+ "val"
# The final value is A="barval foo" 

# Prepend
A = "foo"
A:prepend = "bar "
# The final value is A="bar foo" 
```

## 11. `:remove`
- Removes values from a list variable.
- All occurrences of the specified value are removed.
```bitbake
#remove

A = "foo bar"
A:remove = "foo"
# The final value is A=" bar" 

A = "foo bar"
A:remove = "var"
A += "var"
# The final value is A=" foo bar val" 
```
---

## References
- [Yocto Project Mega-Manual: Variable Assignment](https://www.yoctoproject.org/docs/3.1/mega-manual/mega-manual.html#varassign)

---

## License
This repository is open-source and can be freely used and modified.
