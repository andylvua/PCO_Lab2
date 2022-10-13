# Lab 1. Custom string
[![CMake](https://github.com/ucu-cs/lab1_cstring-zinchukkryvenyaroshevychkharabara/actions/workflows/cmake.yml/badge.svg)](https://github.com/ucu-cs/lab1_cstring-zinchukkryvenyaroshevychkharabara/actions/workflows/cmake.yml)
> Team members: Andrii Yaroshevych, Pavlo Kryven, Yurii Zinchuk and Yurii Kharabara

## Description
This is a simple implementation of the C++ string class.
It is a part of the first labs of the course "Principles of Computer Organization" at UCU.

## Installation

### Requirements
❯ CMake 3.14 or higher

❯ C++ compiler with C++14 support

❯ Git

❯ C++ IDE (optional). CLion is recommended.

> **Note**
>
> CMake and compiler is a mandatory requirements. If your CMake version is incompatible with the project,
> please, consider updating it. For more information, please, refer to the official CMake documentation.
> However, if you are using macOS or Linux, you can use the following command to install the latest version of CMake:
>
> ```bash
> macOS
> $ brew install cmake
> ```
>
> ```bash
> Ubuntu
> $ sudo apt install cmake
> ```
>
> ```bash
> Arch based distros
> $ sudo pacman -S cmake
> ```
>
> For compiler installation, please, refer to the official documentation of your compiler.

To install the library, you need to clone the repository first:
```bash
$ mkdir ~/workspace
$ cd ~/workspace
$ git clone https://github.com/ucu-cs/lab1_cstring-zinchukkryvenyaroshevychkharabara
$ cd lab1_cstring-zinchukkryvenyaroshevychkharabara
```
> Replace `~/workspace` with the path to your workspace.
>
> Remember, if you want to change the name of the folder you clone the repository to,
> you can simply add the name of the folder after the repository URL.
> ```bash
> $ git clone https://github.com/ucu-cs/lab1_cstring-zinchukkryvenyaroshevychkharabara folder_name
> ```

To compile and run the example file using g++:
```bash
$ cd examples
$ g++ -c ../src/mystring.cpp ./example.cpp
$ g++ -o example ./mystring.o ./example.o 
$ ./example
```

### Building manually
> **Note**
>
> If you are using CLion, you can skip this step. IDE will automatically build the project for you.

Then, you can build the library using CMake:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

This will build the library and the tests.

## Usage
To use the library, you need to include the header file:
> You might need to use relative path to the header file according to your working directory.


```cpp
#include "mystring.h"
```

After that, you can use the library:
```cpp
#include <iostream>
#include "mystring.h"


int main() {
    my_str_t example { "Hello, World!" };
    std::cout << example << std::endl;
    return 0;
}
```

### Methods
The library provides all the necessary methods to work with strings in C++ just like the standard library does:

#### Constructors

```cpp
my_str_t str1; //Default constructor
my_str_t str2(10, 'a'); //Constructor with size and char
my_str_t str3("Hello"); //Constructor with char array
my_str_t str4(std::string ("Hello")); //Constructor with std::string
my_str_t str5(str4); //Copy constructor
```

#### All main methods

```cpp
my_str_t example { "Hello, World!" };
my_str_t str { "How are you?" };

example.size(); //Returns the size of the string
sxample.capacity(); //Returns the capacity of the string
example.c_str(); //Returns the pointer to the string

example.swap(str); //Swap two strings
example.at(0); //Returns the character at the specified position
example.reserve(100); //Reserves memory for the string
example.shrink_to_fit(); //Shrinks the capacity of the string to fit its size
example.resize(10); //Resizes the string to a specified length
example.clear(); //Clears the string
example.insert(0, "Hello"); //Inserts a string at a specified position
example.append(str); //Appends a string to the end
example.erase(0, 5); //Erases a substring from the string
example.find("Hello"); //Finds the index of first occurrence of a substring
example.substr(0, 5); //Returns a substring of the string
```

#### Operators

```cpp
my_str_t example { "Hello, World!" };
my_str_t str { "How are you?" };

// Comparison operators
example == str;
example != str;
example < str;
example > str;
example <= str;
example >= str;

// Assignment operators
example = str;
example = str + example;
example += str;

example = example * 2;
example *= 2;

// Stream operators and readline function
std::cout << example << std::endl;
std::cin >> example;

readline(std::cin, example);
```

## Testing
To run the tests, you need to build the library first.
Then, you can run the tests:
```bash
$ cd build
$ ctest -C
```

For your convenience, you can also run the tests using CLion. For even more convenience,
we've generated a test report for you. Please head to [https://andylvua.github.io/POK_Lab1/](https://andylvua.github.io/POK_Lab1/)

## Additional tasks implemented
- [x] Move constructor `my_str_t(my_str_t &&mystr);`
- [x] Assignment operator `my_str_t &operator=(my_str_t&& mystr);`
- [x] Concatenation operators
- [x] Multiplication operators

## Performance check
We've also done a performance tests to compare the performance of our implementation 
with the standard library using [Google Benchmark](https://github.com/google/benchmark). 
You can find the results in the [benchmark_results](https://github.com/ucu-cs/lab1_cstring-zinchukkryvenyaroshevychkharabara/blob/efba977e7f413b91b4a3530e06acb6c1da4d7b7d/benchmark_results/benchmark_results.txt) file.

Most of the methods are working pretty much the same as the standard library does.
However, there are some differences. For example, the `substr()`, `erase()`, `shrink_to_fit()`, and `swap()` methods
are working significantly slower than `std::string`. It happens because we can't operate with memory directly in
some cases. For example, we can't use `realloc()` to resize the string. 

Also, standard library uses some complex algorithms to optimize the performance of the methods we can't archive 
with our implementation.

Despite this, some methods are working faster than the standard library. For example, the `find()` method is working
almost 4 times faster than the standard library. `resize()`, `reserve()`, and `at()` methods are working 2 times faster.

> **Note**
> 
> You can check the actual performance of the methods by running the benchmark yourself. The library provides
> a `benchmark.cpp` file with the benchmark tests and a `CMakeLists.txt` file to build the benchmark automatically using CMake. 
> 
> Also, you can find the benchmark results on the [GitHub Actions](https://github.com/ucu-cs/lab1_cstring-zinchukkryvenyaroshevychkharabara/actions/workflows/cmake.yml) page.

## License
The [MIT](https://choosealicense.com/licenses/mit/) License (MIT)

Copyright © 2022. Andrii Yaroshevych, Pavlo Kryven, Yurii Zinchuk and Yurii Kharabara
