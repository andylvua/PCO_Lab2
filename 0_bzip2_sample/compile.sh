#! /bin/bash
# This script compiles the source code of popular library and creates the executable files
# echo settings
RED="\033[31m"
NORMAL="\033[0m"

# List of valid arguments
valid_args=(-h --help -cr --compile-run -c --compile -r --run --clean)

# Variables
lib_dir=library
examples_dir=examples
build_dir=build
bin_dir=$build_dir/bin
obj_dir=$build_dir/obj
shopt -s nullglob
dependencies=("${lib_dir}"/*.c)
dependencies=("${dependencies[@]##*/}")
examples=("${examples_dir}"/*.c)
examples=("${examples[@]##*/}")
# Compiler
cxx=gcc
cxx_flags=
# Build type
build_type="Debug"

# Flags
Help(){
    echo "Usage: compile.sh [options]"
    echo "Options:"
    echo "  -h, --help"
    echo "  -cr, --compile-run: Compile and run the example"
    echo "  -c, --compile: Compile only"
    echo "  -r, --run: Run only"
    echo "  --clean: Clean compiled files and build directory"
    echo "  --build_type=Debug/Release: Set build type. Defaults to Debug"
}

# Print error message and exit
CompileError(){
    echo -e "${RED}Error: Compilation failed.
Please carefully check the error message above or refer to the project README and make sure you are not making any mistakes:
https://github.com/ucu-cs/lab2_make_cmake-zinchukkryvenyaroshevychkharabara#readme${NORMAL}"
    exit 1
}

DebugMsg(){
    if [ "$build_type" = "Debug" ]; then
        echo "$1"
    fi
}

# Compile static and shared libraries
CompileLibraries(){
    ## Compile the dependencies
    mkdir -p $bin_dir && mkdir -p $obj_dir
    mkdir -p $obj_dir/library

    DebugMsg "Compiling dependencies..."
    for file in "${dependencies[@]}"; do
        $cxx $cxx_flags -c $lib_dir/"$file" -fPIC -o $obj_dir/$lib_dir/"${file%.*}".o || CompileError
    done

    # Compile static library
    DebugMsg "Compiling static library..."
    ar rcs $bin_dir/libbzip2.a $obj_dir/$lib_dir/*.o || CompileError
    DebugMsg "Compiled successfully. Written to $bin_dir/libmystring.a"

    # Compile dynamic library
    DebugMsg "Compiling dynamic library..."
    $cxx $cxx_flags -shared -fPIC -o $bin_dir/libbzip2.so $obj_dir/$lib_dir/*.o || CompileError
    DebugMsg "Compiled successfully. Written to $bin_dir/libmystring.so"
}

# Compile the examples
CompileExamples(){
    mkdir -p $bin_dir && mkdir -p $obj_dir
    mkdir -p $obj_dir/examples
    # Compile the examples
    for file in "${examples[@]}"; do
        $cxx $cxx_flags -c $examples_dir/"$file" -o $obj_dir/$examples_dir/"${file%.*}".o || CompileError
    done

    # Link the examples with the dynamic library
    for file in "${examples[@]}"; do
        $cxx $cxx_flags -fPIC $obj_dir/$examples_dir/"${file%.*}".o $bin_dir/libbzip2.so -o $bin_dir/"${file%.*}" \
        || CompileError
        DebugMsg "Successfully linked with dynamic library. Written to $bin_dir/${file%.*}"
    done
}

# Check state and compile libraries and examples if needed
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
            CompileExamples
        else
            exit 0
        fi
    else
        CompileLibraries
        CompileExamples
    fi
}

# Check if libraries are up to date
CheckUpToDate(){
    if ! CheckCompiled; then
        return 1
    fi

    for file in "${dependencies[@]}"; do
        if [ $lib_dir/"$file" -nt $bin_dir/libbzip2.so ]; then
            return 1
        else
            return 0
        fi
    done
}

# Check if libraries and examples are compiled
CheckCompiled(){
    if [[ -f $bin_dir/bzip2 && -f $bin_dir/bzip2recover && -f $bin_dir/libbzip2.so ]]; then
        return 0
    else
        return 1
    fi
}

# Run the examples
Run(){
    SuggestArguments(){
        echo "Since this script is only a wrapper for the original $1, please use the executable file located in $bin_dir/$1 directly
or pass the arguments now. If no arguments are passed, default --help will be used"
        echo -n "$1 [waiting for arguments]: "
    }

    if CheckCompiled; then
        echo "Which example do you want to run?"
        echo "1. bzip2"
        echo "2. bzip2recover"
        read -r answer
        if [ "$answer" == "1" ]; then
            SuggestArguments "bzip2"
            read -r args
            if [ -z "$args" ]; then
                $bin_dir/bzip2 --help
            else
                $bin_dir/bzip2 "$args"
            fi
        elif [ "$answer" == "2" ]; then
            SuggestArguments "bzip2recover"
            read -r args
            if [ -z "$args" ]; then
                $bin_dir/bzip2recover file_name --help
            else
                $bin_dir/bzip2recover "$args"
            fi
        else
            echo -e "${RED}Invalid input${NORMAL}"
            exit 1
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

# Check if there is more than one argument or second argument splitted by '=' is not --build_type
if [ $# -gt 1 ] && [ "${2%=*}" != "--build_type" ]; then
    echo -e "${RED}Error: Too many arguments${NORMAL}"
    Help
    exit 1
fi

# Check build type if it is passed
if [ "${2%=*}" == "--build_type" ]; then
    if [ "${2#*=}" == "Debug" ]; then
        cxx_flags="-g -O0"
        build_type="Debug"
    elif [ "${2#*=}" == "Release" ]; then
        echo "build_type is set to Release. To see debug messages, set build_type to Debug"
        cxx_flags="-O3"
        build_type="Release"
    else
        echo -e "${RED}Error: Invalid build type${NORMAL}"
        Help
        exit 1
    fi
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
