#! /bin/bash
# This script compiles the source code and creates the executable file
# echo settings
RED="\033[31m"
NORMAL="\033[0m"

# List of valid arguments
valid_args=(-h --help -cr --compile-run -c --compile -r --run --clean)

# Variables
lib_dir=library
bin_dir=bin
obj_dir=obj
dependencies=(mystring.cpp mystring.h)
# Compiler
cxx=g++

# Flags
Help(){
    echo "Usage: compile.sh [options]"
    echo "Options:"
    echo "  -h, --help"
    echo "  -cr, --compile-run: Compile and run the example"
    echo "  -c, --compile: Compile only"
    echo "  -r, --run: Run only"
    echo "  --clean: Clean compiled files and build directory"
}

# Print error message and exit
CompileError(){
    echo -e "${RED}Error: Compilation failed.
Please carefully check the error message above or refer to the project README and make sure you are not making any mistakes:
https://github.com/ucu-cs/lab2_make_cmake-zinchukkryvenyaroshevychkharabara#readme${NORMAL}"
    exit 1
}

# Compile static and shared libraries
CompileLibraries(){
    mkdir -p $bin_dir && mkdir -p $obj_dir

    echo "Compiling static library..."
    $cxx -c $lib_dir/mystring.cpp -o $obj_dir/mystring.o || CompileError
    ar rcs $bin_dir/libmystring.a $obj_dir/mystring.o || CompileError
    echo "Compiled successfully. Written to $bin_dir/libmystring.a"

    echo "Compiling dynamic library..."
    $cxx -c $lib_dir/mystring.cpp -fPIC -o $obj_dir/mystring.o || CompileError
    $cxx -shared -fPIC -o $bin_dir/libmystring.so $obj_dir/mystring.o || CompileError
    echo "Compiled successfully. Written to $bin_dir/libmystring.so"
}

# Compile the example
CompileExample(){
    echo "Compiling example..."
    mkdir -p $bin_dir && mkdir -p $obj_dir
    $cxx -c ./examples/example.cpp -o $obj_dir/example.o -I$lib_dir || CompileError
    echo "Linking example with dynamic library..."
    $cxx -fPIC $obj_dir/example.o $bin_dir/libmystring.so -o $bin_dir/example || CompileError
    echo "Successfully linked with dynamic library. Written to $bin_dir/example"
}

# Check state and compile libraries and example if needed
Compile(){
    if CheckUpToDate; then
        echo -e "${RED}Libraries are up to date. Nothing to compile${NORMAL}"
        echo "Do you want to clean-compile? (y/n)"
        read -r answer
        if [ "$answer" == "n" ]; then
            exit 0
        fi

        if Clean; then
            CompileLibraries
            CompileExample
        else
            exit 0
        fi
    else
        CompileLibraries
        CompileExample
    fi
}

# Check if libraries are up to date
CheckUpToDate(){
    if ! CheckCompiled; then
        return 1
    fi

    for file in "${dependencies[@]}"; do
        if [ $lib_dir/"$file" -nt $bin_dir/libmystring.so ]; then
            return 1
        else
            return 0
        fi
    done
}

# Check if libraries and example are compiled
CheckCompiled(){
    if [[ -f $bin_dir/example && -f $bin_dir/libmystring.so ]]; then
        return 0
    else
        return 1
    fi
}

# Run the example
Run(){
    if CheckCompiled; then
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            echo "Linux detected. Setting LD_LIBRARY_PATH..."
            echo ""
            LD_LIBRARY_PATH="$bin_dir" $bin_dir/example
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            echo "MacOS detected. Setting DYLD_LIBRARY_PATH..."
            echo ""
            DYLD_LIBRARY_PATH="$bin_dir" $bin_dir/example
        fi
    else
        echo -e "${RED}Error: nothing to run. Necessary files are not compiled. Run with -c or --compile option to compile.${NORMAL}

Do you want to automatically compile libraries and run the example? (y/n)"
        read -r answer
        if [[ "$answer" == "y" ]]; then
            Compile
            Run
        else
            echo "Exiting..."
            exit 1
        fi
    fi
}

# Clean compiled files
Clean(){
    echo "This will remove all compiled files along with the library. Are you sure? (y/n)"
    read -r answer
    if [[ "$answer" == "y" ]]; then
        rm -rf $bin_dir
        rm -rf $obj_dir
        echo "Cleaned successfully."
        return 0
    else
        echo -e "${RED}Aborted${NORMAL}"
        return 1
    fi
}

# Check if there is no argument
if [ $# -eq 0 ]; then
    Help
    exit 1
fi

# Check if there is more than one argument
if [ $# -gt 1 ]; then
    echo -e "${RED}Error: Too many arguments${NORMAL}"
    Help
    exit 1
fi

# Check if the argument is -h or --help
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    Help
    exit 0
fi

# Check if the argument is -r or --run
if [ "$1" = "-r" ] || [ "$1" = "--run" ]; then
    Run
    exit 0
fi

# Check if the argument is -c or --compile
if [ "$1" = "-c" ] || [ "$1" = "--compile" ]; then
    Compile
    exit 0
fi

# Check if the argument is -cr or --compile-run
if [ "$1" = "-cr" ] || [ "$1" = "--compile-run" ]; then
    Compile
    Run
    exit 0
fi

# Check if the argument is clean
if [ "$1" = "--clean" ]; then
    Clean
    exit 0
fi

# Check if the argument is not valid
if [[ ! " ${valid_args[*]} " == *" $1 "* ]]; then
    echo -e "${RED}Error: Invalid argument${NORMAL}"
    Help
    exit 1
fi
