//
// Created by Andrew Yaroshevych on 06.10.2022.
//
//
// This file contains just basic calls to the library methods. Don't take it seriously.
//

#include <iostream>
#include <fstream>
#include "../library/mystring.h"

using std::cout;
using std::endl;

int main() {
    // Empty constructor
    my_str_t empty;

    // c-string constructor
    my_str_t example("Hello world!");
    cout << "c-string constructor: " << example << endl;

    // Char constructor
    my_str_t char_n_string(10, 'a');
    cout << "Char constructor: " << char_n_string << endl;

    // Copy constructor
    my_str_t copy(example);
    cout << "Copy constructor: " << copy << endl << endl;

    // Operator =
    my_str_t assigned;
    assigned = char_n_string;
    cout << "Operator =: " << assigned << endl;

    // Operator []
    cout << "Operator []: " << copy[0] << endl;

    // At
    cout << "At: " << copy.at(copy.size() - 1) << endl << endl;

    // Reserve
    cout << "Example capacity before reserve: " << example.capacity() << endl;
    example.reserve(100);
    cout << "Example capacity after reserve: " << example.capacity() << endl << endl;

    // Shrink to fit
    cout << "Example capacity before shrink_to_fit: " << example.capacity() << endl;
    example.shrink_to_fit();
    cout << "Example capacity after shrink_to_fit: " << example.capacity() << endl << endl;

    // Resize
    cout << "Example size before resize: " << example.size() << endl;
    example.resize(5);
    cout << "Example size after resize: " << example.size() << endl << endl;

    // Clear
    cout << "Example before clear: " << example << endl;
    example.clear();
    cout << "Example after clear: " << example << endl << endl;

    // Append
    cout << "Example before append: " << example << endl;
    example.append("I am a string!");
    cout << "Example after append: " << example << endl << endl;

    // Insert
    cout << "Example before insert: " << example << endl;
    example.insert(6, " beautiful");
    cout << "Example after insert: " << example << endl << endl;

    // Erase
    cout << "Example before erase: " << example << endl;
    example.erase(17, 7);
    example.erase(4, 2);
    cout << "Example after erase: " << example << endl << endl;

    // C_str
    cout << "Example c_str: " << example.c_str() << endl << endl;

    // Find
    cout << "Example find: " << example.find("am") << endl << endl;

    // Substr
    cout << "Example substr: " << example.substr(0, 5) << endl << endl;

    // Swap
    my_str_t swappee("I am a swappee!");
    cout << "Example before swap: " << example << endl;
    cout << "Swappee before swap: " << swappee << endl;
    example.swap(swappee);
    cout << "Example after swap: " << example << endl;
    cout << "Swappee after swap: " << swappee << endl << endl;

    // Operator +
    my_str_t plus(" I am a plus!");
    cout << "Example + plus: " << example + plus << endl << endl;

    // Operator +=
    cout << "Example before += plus: " << example << endl;
    example += plus;
    cout << "Example after += plus: " << example << endl << endl;

    example = my_str_t("Oh no, I am a string again! ");
    // Operator *
    cout << "Example * 3: " << example * 3 << endl << endl;

    // Operator *=
    cout << "Example before *= 3: " << example << endl;
    example *= 3;
    cout << "Example after *= 3: " << example << endl << endl;

    // Operator ==
    cout << "Example == plus: " << (example == plus) << endl << endl;

    // Operator !=
    cout << "Example != plus: " << (example != plus) << endl << endl;

    // Operator <
    cout << "Example < plus: " << (example < plus) << endl << endl;

    // Operator >
    cout << "Example > plus: " << (example > plus) << endl << endl;

    // Operator <=
    cout << "Example <= plus: " << (example <= plus) << endl << endl;

    // Operator >=
    cout << "Example >= plus: " << (example >= plus) << endl << endl;

    // Operator <<
    cout << "Operator <<: " << example << endl << endl;

    // readline
    my_str_t text;
    std::ifstream in("../examples/example.txt");

    readline(in, text);

    cout << "Readline: " << text << endl << endl;
    return 0;
}