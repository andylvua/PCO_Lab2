#! /bin/bash
# Compile dynamic library

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

Compile(){
    mkdir -p bin && mkdir -p obj
    g++ -c ./library/mystring.cpp -fPIC -o ./obj/mystring.o
    g++ -shared -fPIC -o ./bin/libmystring.so ./obj/mystring.o
    g++ -c ./examples/example.cpp -o ./obj/example.o
    g++ -fPIC ./obj/example.o ./bin/libmystring.so -o ./bin/example
    echo "Compiled successfully"
}

CheckCompiled(){
    if [[ -f ./bin/example ]]; then
        return 0
    else
        return 1
    fi
}

Run(){
    if CheckCompiled; then
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            LD_LIBRARY_PATH="../build/mystring-debug" ./bin/example
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            DYLD_LIBRARY_PATH="../build/mystring-debug" ./bin/example
        fi
    else
        echo "Error: nothing to run. Example is not compiled."
    fi
}

Clean(){
    rm -rf ./bin
    rm -rf ./obj
    echo "Cleaned successfully."
}

# Check if there is no argument
if [ $# -eq 0 ]; then
    Help
    exit 1
fi

# Check if there is more than one argument
if [ $# -gt 1 ]; then
    echo "Error: Too many arguments"
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
    echo "Error: Invalid argument"
    Help
    exit 1
fi
