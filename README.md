# Carbon

Carbon is a small hobby kernel, which aims to be a microkernel

![Image of Carbon running](https://media.discordapp.net/attachments/770712465729912832/909596697141841960/Screen_Shot_2021-11-15_at_01.12.19.png)

# Building Carbon

## Linux

### Dependencies:

- build-essential

### Instructions:

Steps:

- If your GCC toolchain already compiles i686 ELF files, run `make`
- If not, build a GCC + Binutils toolchain configured for i686-elf:

Make sure to create a directory for GCC and Binutils such that your home directory doesn't get poluted.

- $ `git clone https://github.com/mobiusloopfour/mobius-carbon`
- $ `brew install wget nasm qemu gmp mpfr libmpc`
- $ `wget https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-11.2.0.tar.gz && wget https://ftp.gnu.org/gnu/binutils/binutils-2.37.tar.gz`
- $ `tar -xvf gcc-11.2.0.tar.gz`
- $ `tar -xvf binutils-2.37.tar.gz`
- $ `mkdir build-gcc build-binutils`
- $ `cd build-binutils`
- $ `export PREFIX="$HOME/opt/cross" && export TARGET=i686-elf && export PATH="$PREFIX/bin:$PATH"`

From this point onwards, you should not kill the current Terminal window as we need these variables later.

- $ `../binutils-2.37/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && make && make install`
- $ `cd ../build-gcc`
- $ `../gcc-11.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c--without-headers`
- $ `make all-gcc && all-target-libgcc && install-gcc && install-target-libgcc`

Make sure you have the current `$PATH` in your `~/.bashrc`. If you still encounter issues, refer to [this guide](https://web.archive.org/web/20211007210427/https://wiki.osdev.org/GCC_Cross-Compiler).

## macOS

### Dependencies

- homebrew
- make
- gcc
- qemu-system-i386 or qemu-system-x86_64

### Instructions

These instructions have been confirmed to work on macOS Monterey 12.0.1.

#### Building GCC and Binutils

Make sure to create a directory for GCC and Binutils such that your home directory doesn't get poluted.

- $ `git clone https://github.com/mobiusloopfour/mobius-carbon`
- $ `brew install wget nasm qemu gmp mpfr libmpc`
- $ `wget https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-11.2.0.tar.gz && wget https://ftp.gnu.org/gnu/binutils/binutils-2.37.tar.gz`
- $ `tar -xvf gcc-11.2.0.tar.gz`
- $ `tar -xvf binutils-2.37.tar.gz`
- $ `mkdir build-gcc build-binutils`
- $ `cd build-binutils`
- $ `export PREFIX="$HOME/opt/cross" && export TARGET=i686-elf && export PATH="$PREFIX/bin:$PATH"`

From this point onwards, you should not kill the current Terminal window as we need these variables later.

- $ `../binutils-2.37/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && make && make install`
- $ `cd ../build-gcc`
- $ `../gcc-11.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c--without-headers`
- $ `make all-gcc && all-target-libgcc && install-gcc && install-target-libgcc`

Make sure you have the current `$PATH` in your `~/.zshrc`. If you still encounter issues, refer to [this guide](https://web.archive.org/web/20211007210427/https://wiki.osdev.org/GCC_Cross-Compiler).

#### Building the Operating System

In the root folder of this repo, run:

- $ `make`

#### Running and debugging

QEMU is set up to debug to the standard output (that means the terminal you run `make qemu` in).

- `$ make qemu`

## Windows

Windows users should be able to build using WSL2. Running can be done on the native QEMU, although compatability has not been tested.

# Contributing

Contributions are always welcome! If you think you've spotted a bug, submit a PR. If you've thought of a new feature, add a directory called `contrib/<feature or developer id>`. This is such that any new commits from me do not interfere.

Note on developer id's: these should be Java-styled reverse domains, such as `org.MobiusCarbon.Kernel`. If you don't have a domain name (such as me), you can put anything you like, but keep the three-part structure of `TOP_LEVEL`.`ID`.`PROJECT`. 

## Style

Braces should generally be put on a new line, except for structs, if-else staments and while - and for loops. The naming convention is snake case/unix-like. 