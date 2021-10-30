# Carbon source tree

| Directory | Contents|
| --------- | -------- |
| EXTERNAL | The UEFI SDK |
| config | Various compiler configuration files |
| include | Global include directory |
| libkern | Basic utility functions for use in the kernel |
| libsa | Bootstrap code (the boot loader is named Bateau) |
| mem | Memory allocation subsystem. This is NOT memory management |
| osck | Carbon subsystem |
| rootfs | QEMU sandbox |

# Building a kernel

To build the kernel correctly, first set up a suitable workspace. The requirements are as follows:

- clang
- lld.ld
- lld-link
- make
- cmake
- gcc (If you wish to rebuild libuefi.a)

First, set up the workspace. If you get errors, make sure uefi is symlinked correctly.

```Bash
$ git clone https://github.com/mobiusloopfour/mobius-carbon
$ cd libsa && ln -s ../EXTERNAL/uefi && cd .. # gcc is required
$ make configure
```


To build the kernel and make a chroot-like environment in `rootfs`:

```Bash
$ make
```

You may want to debug any changes you made to the kernel. Install qemu if you haven't already, and run:

```Bash
$ sudo apt install qemu # Debian-based
$ sudo yum install qemu # REHL-based
$ sudo pacman -S qemu # Arch-based
$ sudo emerge -s qemu # Gentoo

$ brew install qemu # macOS
```

```
$ make qemu
```



## Adding and removing files

Be sure to edit the Makefile and add an appropriate CMakeLists.txt. As object files are cached locally, run `make rebuild_cache` to prevent duplicate symbols when renaming/adding a file, or use cmake in the relevant directories.

### What (not) to add

Performance optimisations, scheduler improvements (not impl. as of now), bug fixes are all very welcome. However, this project seeks to be as close to a real microkernel as possible. Do not implement something like a video driver in the kernel space. Drivers that can be loaded and unloaded will be added eventually, with placeholder ones for disk access, memory managment etc. to be built-in as of now. The goal is to remove them eventually, and replace them with user space drivers.

### Suggestions

For suggestions, feel free to submit a PR, or write me at scratch.joint-0i@icloud.com. You can also add me on discord: `Zhong Xina#9009`

## clangd

This project is set up to support clangd as much as possible. `libsa` does not currently support it as it is not built using CMake.

# Kernel style guide

## Naming

In the kernel space, follow the C idiom, which means `type_t` and `snake_case`. 
Do not abbreviate needlessly. It is better to have long, understandable code than short and unclear code.
Abbreviations such as `mem`, `ptr` and other common mnemonics are allowed. Be as concise as possible and avoid `get`, `does`, `do`. When dealing with pairs, use antonyms such as `add` and `remove`. Do not use camel case.

| Good | Bad |
| ----- | --------|
| `boot_info_t` | `boot_info`, `bootInfo_t`, `BootInfo` |
| `size(...)` | `siz()`, `sz()`, `get_size()`, `getSize()` | 
| `add()` | `add_item() // It's clear an item is being added` |


## Example
```c
type_t *
identifier(const char *a, const unsigned *const b)
{
    // ...
}
```

# User/developer facing code

## Naming

Follow modern API idiom and DO use camel case. Avoid underscores or abbreviations. Do not abbreviate needlessly. It is better to have long, understandable code than short and unclear code. Be as concise as possible and avoid `get`, `does`, `do`. When dealing with pairs, use antonyms such as `add` and `remove`. Do not use camel case. Types and classes start with a capital. Functions and variables start with lowercase.

## Example
```c
Type *identifier(const char *aParameter, const unsigned int *const aConst) {
    if (a) {
        // ...
    } else {
        // ...
    }
}
```