# CARBON SOURCE TREE

Carbon is a modular hybrid kernel (tending to micro-kernel design). Developments can be read in man/NEWS.
It's source layout, build instructions and more are explained in the `man` (manuals) subdirectory. Pull 
request are currently accepted and welcomed. It's API is loosely based around POSIX, but built
in such a way that other user API designs are trivial to port.

## Building quick how-to

For more information, refer to `man/Building.txt`. To get started, install LLVM and CMake:

```bash
$ brew install cmake llvm # Install using homebrew
$ sudo port install clang-13 # Install using MacPorts
$ echo "export PATH=\"/usr/local/opt/llvm/bin/:$PATH\"\n" >> ~/.zshrc  # This assumes you use the Z shell. Use at your own risk

$ sudo apt install -y cmake llvm # APT-based distros

$ doas pkg install build-essential cmake # FreeBSD
```

To build, run:

```bash
$ sh ./conf
$ make
```

If you get any errors, double check all the dependenies are met (`man/Building.txt`). To run, type:

```bash
$ make run
```

## Misc.

### Binaries

Binaries and CD-ROM images will be available on the first point release.

### License

This project is licensed under GNU GPLv3-Or-Later. For more information refer to `man/License.txt`. Additionally, 
the `/gnu` subdirectory holds source files copyrighted by the FSF.

### Why isn't there anything on the screen??

Check your terminal. Carbon does not have a video driver implemented in the kernel as this goes straight
against it's design principles.

### Other languages and compilers

As this project is built around CMake and Clang, it would be relatively hard to add code in, say rust. 
Support for other languages may be better once user space servers will commence development. 

As for GCC, it has not been tested and is thus not an officially supported option, but you may have luck
editing the file `carbon.cmake` to use (i686-elf-)gcc. [Xrbiay](https://github.com/xrbiay) may be available to help
suport GCC as well.