# CLAY Assignment
application has the single purpose of persistently storing and retrieving key-value pairs, most commonly used to store settings. K-V pairs
cannot be nested

# Prerequisites
This program use [ALlib](https://github.com/javad123javad/ALlib) (My personal library for BSD network stack) and [Unity](http://www.throwtheswitch.org/unity) as testing framework. 
It's highly recommended to install `ALlib` as shared library, eventhough it's also possible to be compiled as static library as well.
## Installing ALLib
```shell
$ git clone git@github.com:javad123javad/ALlib.git
$ cd Allib
$ mkdir build
$ cd build
$ cmake -DBUILD_SHARED_LIBS=ON ..
$ make
$ sudo make install
```
## Installing Unity
```shell
$ git clone https://github.com/ThrowTheSwitch/Unity.git
$ cd Unity
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

## Build
imp_netman uses autohell to build the binary output. So, the instruction is straight forward:
```shell
./autogen.sh && configure && make
```
Or
```shell
autoreconf -i && configure && make
```
After successful compilation, the executable will be available in `src/Clay_Assignment`

## Execute

The binary is in `<clay directory>/src`:
```shell
$ ./src/Clay_Assignment 
> SET LED ON
OK
> SET GPS ON
OK
> GET LED
ON
> DELETE LED
OK
> GET LED

> QUIT
BYE
```

# Configure Buildroot build
To make the embedded version of this assignment, please clone `Clay` branch from my cloned repository of `buildroot`
```shell
$ git clone -b Clay https://github.com/javad123javad/buildroot.git
```
Then load one of the configuration from `configs` directory
```shell
$ make qemu_arm_versatile_defconfig
```
Enable following option in buildroot menu:
* Toolchain -->  Enable WCHAR support 
* Toolchain -->  Enable C++ support
* Target packages --> Debugging, profiling and benchmark --> Unity Test Framework
* Target packages --> Filesystem and flash utilities --> CLAY2 Assignment
* Target packages --> Libraries --> Networking --> ALlib


