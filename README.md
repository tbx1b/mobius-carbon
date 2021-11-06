# Carbon

Carbon is a small hobby kernel, which aims to be a microkernel

![Image of Carbon running](https://cdn.discordapp.com/attachments/770712465729912832/906606508920430662/Screen_Shot_2021-11-06_at_19.10.29.png)

# Building Carbon

## Linux

### Dependencies:

- xorriso
- nasm
- make
- qemu
- qemu-system-i386

### Instructions:

These instructions were written on Debian 11 - but should be flexible enough to work on other distributions.

Steps:

- First clone this repository.
- Once in the the root folder, cd into /mk, and clone [limine-bootloader](https://github.com/limine-bootloader/limine.git).
  - `git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1`
- You'll have to build gcc and binutils with the correct enviroment variables to utilize them to build Carbon.
  - Get the source from [the website](https://ftp.gnu.org/gnu/).
  - Be sure to have these enviroment variables in your shell:
    - export PREFIX="$HOME/opt/cross"
    - export TARGET=i686-elf
    - export PATH="$PREFIX/bin:$PATH"
- In the root folder, cd into /mk, and run:
  - `make -C limine`
- After that, go back into the root folder, and run:
  - `make`
  - `make iso`
- When you want to run the OS, run:
  - `make run`

Note that a lot of what is said here, can be found online, and if you need help compiling gcc or binutils - refer to online resources.

## macOS

### Dependencies

- homebrew
- nasm
- make
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

Make sure you have the current `$PATH` in your `~/.zshrc`. If you still encounter issues, refer to [this guide](https://web.archive.org/web/20211007210427/https://wiki.osdev.org/GCC_Cross-Compiler#Linux_Users_building_a_System_Compiler).

#### Building the Operating System

In the root folder of this repo, run:

- $ `cd mk && git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1`
- $ `cd ..; make && make iso`

#### Running and debugging

QEMU is set up to debug to the standard output (that means the terminal you run `make run` in). There is obviously no display driver built into the kernel, so this should be a suitable compromise.

- `$ make run`

# Contributing

Contributions are always welcome! If you think you've spotted a bug, submit a PR. If you've thought of a new feature, add a directory called `contrib/<feature or developer id>`. This is such that any new commits from me do not interfere.

Note on developer id's: these should be Java-styled reverse domains, such as `org.MobiusCarbon.Kernel`. If you don't have a domain name (such as me), you can put anything you like, but keep the three-part structure of `TOP_LEVEL`.`ID`.`PROJECT`. 

## Style

Every function must have the `MLTX_API` (`__cdecl__`) calling convention. Braces should generally be put on a new line, except for structs, if-else staments and while - and for loops. The naming convention is snake case, with a special scheme as to avoid namespace mangling: e.g. `_hal_shutdown`. In your header (.h) files, it is recommended to #define a more readable version of your functions. Examples can be found in ./libcarbon. 
