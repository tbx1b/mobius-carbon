# Carbon

Carbon is a small hobby kernel, which aims to be a microkernel

![Image of Carbon running](https://cdn.discordapp.com/attachments/770712465729912832/906606508920430662/Screen_Shot_2021-11-06_at_19.10.29.png)

# Building

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

Note that a lot of what is said here, can be found online, and Carbon documentation can be accessed with

## Mac

### Dependencies

...

### Instructions

...

# Contributing

If you have issues, or an idea - feel free to open an issue, or open a pull request.
