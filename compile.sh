#! /bin/bash

RED="\033[31m"
NORMAL="\033[0m"
# List of valid arguments
valid_args=(-h --help -cr --compile-run -c --compile -r --run --clean)

Help(){
    echo "Usage: compile.sh [options]"
    echo "Options:"
    echo "  -h, --help"
    echo "  -cr, --compile-run: Compile and run the example"
    echo "  -c, --compile: Compile only"
    echo "  -r, --run: Run only"
    echo "  --clean: Clean compiled files and build directory"
}

CompileLibraries(){
    mkdir -p bin && mkdir -p obj

    echo "Compiling static library..."
    g++ -c ./library/mystring.cpp -o ./obj/mystring.o
    ar rcs ./bin/libmystring.a ./obj/mystring.o
    echo "Compiled successfully. Written to ./bin/libmystring.a"

    echo "Compiling dynamic library..."
    g++ -c ./library/mystring.cpp -fPIC -o ./obj/mystring.o
    g++ -shared -fPIC -o ./bin/libmystring.so ./obj/mystring.o
    echo "Compiled successfully. Written to ./bin/libmystring.so"
}

CompileExample(){
    echo "Compiling example..."
    mkdir -p bin && mkdir -p obj
    g++ -c ./examples/example.cpp -o ./obj/example.o
    echo "Linking with dynamic library..."
    g++ -fPIC ./obj/example.o ./bin/libmystring.so -o ./bin/example
    echo "Successfully linked with dynamic library. Written to ./bin/example"
}

CheckCompiled(){
    if [[ -f ./bin/example && -f ./bin/libmystring.so ]]; then
        return 0
    else
        return 1
    fi
}

Run(){
    if CheckCompiled; then
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            echo "Linux detected. Setting LD_LIBRARY_PATH..."
            echo ""
            LD_LIBRARY_PATH="./bin" ./bin/example
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            echo "MacOS detected. Setting DYLD_LIBRARY_PATH..."
            echo ""
            DYLD_LIBRARY_PATH="./bin" ./bin/example
        fi
    else
        echo -e "${RED}Error: nothing to run. Necessary files are not compiled. Run with -c or --compile option to compile.${NORMAL}

Do you want to automatically compile libraries and run the example? (y/n)"
        read -r answer
        if [[ "$answer" == "y" ]]; then
            CompileLibraries
            CompileExample
            Run
        else
            echo "Exiting..."
            exit 1
        fi
    fi
}

Clean(){
    echo "This will remove all compiled files along with the library. Are you sure? (y/n)"
    read -r answer
    if [[ "$answer" == "y" ]]; then
        rm -rf ./bin
        rm -rf ./obj
        echo "Cleaned successfully."
    else
        echo -e "${RED}Aborted${NORMAL}"
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
    CompileLibraries
    CompileExample
    exit 0
fi

# Check if the argument is -cr or --compile-run
if [ "$1" = "-cr" ] || [ "$1" = "--compile-run" ]; then
    CompileLibraries
    CompileExample
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
