## Requirements and installation

Please, refer to the main [README.md](../README.md) file for the requirements and general installation instructions.

## Compilation
This section describes how to compile the `bzip2` library.
For compiling `mystring` library, please head to the compilation section of main [README.md](../README.md) file.

> **Note**
>
> The following instructions are for Linux and macOS. For Windows, please use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10)

<br>

For all next steps, please, make sure that you are in the `0_bzip2_sample` directory of the project:
```bash
$ cd 0_bzip2_sample
```

### Using `compile.sh`
The `compile.sh` script is used to compile the project. It takes the following arguments:
- `-h` or `--help` - prints help message
- `-cr` or `--compile-run` - compiles the libraries and runs the examples
- `-c` or `--compile` - compiles the libraries
- `-r` or `--run` - runs the example
- `--clean` - cleans the build directory
- `--build_type=TYPE` - specifies the build type. Possible values are `Debug` and `Release`. Default value is `Debug`

To compile the libraries and run the example, use the following command:
```bash
$ ./compile.sh -cr
```
and follow the instructions.

> **Note**
>
> Libraries and executables will be written to the `build/bin` directory.

> **Warning**
>
> If you see the following error:
> ```bash
> zsh: permission denied: ./compile.sh
> ```
> You need to give the execution permissions to the script. To do that, run the following command:
> ```bash
> $ chmod +x compile.sh
> ```
> and try again.

`--clean` option can be used to clean the build directory. For example, if you want to clean the build directory and compile the libraries, use the following commands:
```bash
$ ./compile.sh --clean
$ ./compile.sh -c
```
> Note that `--clean` option will remove all the files in the build directory including the compiled libraries, so use it with caution.

`--build_type` option can be used to specify the build type. For example, if you want to compile the libraries in release mode, use the following command:
```bash
$ ./compile.sh -c --build_type=Release
```
> Note that the default build type is `Debug`.
> In this mode, the compiler will not optimize code, and you will see some debug information in the output.
>
> In release mode, the code will be optimized using -O3 flag, and you will not see any debug information.

<br>

### Using `make`
`make` build system is also supported for this library. Two makefiles are provided: `examples/Makefile` and `library/Makefile`.
Makefile located in the `library` directory is used to compile the static and shared libraries. Makefile located in the `examples` directory is used to compile the example.

To compile the libraries, use the following command:
> Make sure you are in the `0_bzip2_sample` directory of the project
```bash
$ make -f library/Makefile
```
To compile the example, use the following command:
> Make sure you are in the `0_bzip2_sample` directory of the project
```bash
$ make -f examples/Makefile
```

> **Note**
>
> Libraries and executables will be written to the `build/bin` directory.


> **Note**
>
> Running `examples/Makefile` will also compile the libraries.

To run the example, use the following command:
> Make sure you are in the `0_bzip2_sample` directory of the project
```bash
$ make -f examples/Makefile run
```

<br>

Our build system also support the release mode. To compile the libraries in release mode, use the following command:
```bash
$ make -f library/Makefile release
```
In release mode, the code will be optimized using -O3 flag.

<br>

To clean the build directory, use the following command:
```bash
$ make -f library/Makefile clean
```
or
```bash
$ make -f examples/Makefile clean
```

> **Note**
>
> Makefile located in `examples` directory will only remove example executable and object files.
> If you want to clean the build directory completely, use `make -f library/Makefile clean` instead.

<br>

### Using CMake
This library also supports CMake tool.

To build the project using CMake, use the following commands:
> Make sure you are in the `0_bzip2_sample` directory of the project
```bash
$ cmake -B build
$ cmake --build build
```

> **Note**
>
> Libraries and executables will be written to the `build/bin` directory.

If you want to build the project in release mode, use the following commands:
```bash
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

<br>

To run the example, use the following command:
```bash
$ ./build/bin/bzip2
```
or
```bash
$ ./build/bin/bzip2recover
```

<br>

To clean the build directory, use the following command:
```bash
$ cmake --build build --target clean
```

## License
The [MIT](https://choosealicense.com/licenses/mit/) License (MIT)

Copyright © 2022. Andrii Yaroshevych, Pavlo Kryven, Yurii Zinchuk and Yurii Kharabara
