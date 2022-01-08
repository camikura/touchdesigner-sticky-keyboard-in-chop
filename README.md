# touchdesigner-sticky-keyboard-in-chop

## Overview

This is a Keyboard In CHOP that will remain active even if TouchDesigner moves to the background.

## How to use

You can use it like a normal Keyboard In CHOP.

## Configure and Build project

1. Checkout the plugin

- `git clone https://github.com/camikura/touchdesigner-sticky-keyboard-in-chop.git`
- `cd touchdesigner-sticky-keyboard-in-chop`

2. Configure and build the plugin

- `cmake -S . -B build -G <generator> [options]`
- `cmake --build build [-- [options] <target>]`

For example

```
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

## Reference

See https://docs.derivative.ca/Keyboard_In_CHOP
