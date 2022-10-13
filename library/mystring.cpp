//
// Created by Andrew Yaroshevych on 29.09.2022.
//

#include "mystring.h"
#include <cmath>

const size_t my_str_t::not_found;

// Implemented by Pavlo Kryven
size_t my_str_t::calculate_capacity(size_t size) {
    return (size > 7) ? static_cast<size_t>
    (std::pow(2, std::ceil(std::log2(size + 1))) - 1) : DEFAULT_CAPACITY;
}

// Implemented by Andrew Yaroshevych
size_t my_str_t::calculate_min_capacity(size_t size) {
    return static_cast<size_t> ((16 * std::ceil(static_cast<double> (size + 1) / 16)) - 1);
}

// Implemented by Andrew Yaroshevych
size_t my_str_t::strlen(const char *cstr) {
    const char *s;

    for (s = cstr; *s; ++s);
    return (s - cstr);
}

// Implemented by Andrew Yaroshevych
my_str_t::my_str_t() {
    size_m = 0;

    capacity_m = DEFAULT_CAPACITY;
    data_m = new char[DEFAULT_CAPACITY + 1];

    data_m[0] = '\0';
}

// Implemented by Pavlo Kryven
my_str_t::my_str_t(size_t size, char initial) {
    size_m = size;

    capacity_m = calculate_capacity(size_m);
    data_m = new char[capacity_m + 1];

    for (int i = 0; i < size_m; i++) {
        data_m[i] = initial;
    }

    data_m[size_m] = '\0';
}

// Implemented by Andrew Yaroshevych
my_str_t::my_str_t(const char *cstr) {
    size_m = strlen(cstr);

    capacity_m = calculate_capacity(size_m);
    data_m = new char[capacity_m + 1];

    memcpy(data_m, cstr, size_m);

    data_m[size_m] = '\0';
}

// Implemented by Andrew Yaroshevych
my_str_t::my_str_t(const std::string &str) {
    size_m = str.size();

    capacity_m = calculate_capacity(size_m);
    data_m = new char[capacity_m + 1];

    memcpy(data_m, str.c_str(), size_m);

    data_m[size_m] = '\0';
}

// Implemented by Pavlo Kryven
my_str_t::my_str_t(const my_str_t &mystr) : size_m{mystr.size_m}, capacity_m{mystr.capacity_m} {
    data_m = new char[capacity_m + 1];
    std::memcpy(data_m, mystr.data_m, size_m + 1);
}

// Implemented by Pavlo Kryven
my_str_t::my_str_t(my_str_t &&mystr) noexcept: size_m{0}, capacity_m{DEFAULT_CAPACITY}, data_m{nullptr} {
    size_m = mystr.size_m;
    capacity_m = mystr.capacity_m;
    data_m = mystr.data_m;
    mystr.size_m = 0;
    mystr.capacity_m = 0;
    mystr.data_m = nullptr;
}

// Implemented by Pavlo Kryven
my_str_t &my_str_t::operator=(my_str_t &&mystr) noexcept {
    if (this != &mystr) {
        delete[] data_m;
        data_m = mystr.data_m;

        size_m = mystr.size_m;
        capacity_m = mystr.capacity_m;

        mystr.size_m = 0;
        mystr.capacity_m = 0;
        mystr.data_m = nullptr;
    }
    return *this;
}

// Implemented by Andrew Yaroshevych
my_str_t &my_str_t::operator=(const my_str_t &mystr) {
    if (this == &mystr) {
        return *this;
    }

    if (capacity_m < mystr.size_m) {
        delete[] data_m;
        capacity_m = calculate_capacity(mystr.size_m);
        data_m = new char[capacity_m + 1];
    }

    size_m = mystr.size_m;

    memcpy(data_m, mystr.data_m, size_m + 1);

    data_m[size_m] = '\0';

    return *this;
}

// Implemented by Andrew Yaroshevych
void my_str_t::swap(my_str_t &other) noexcept {
    size_t tmp_size = size_m;
    size_m = other.size_m;
    other.size_m = tmp_size;

    size_t tmp_capacity = capacity_m;
    capacity_m = other.capacity_m;
    other.capacity_m = tmp_capacity;

    char *tmp_data = data_m;
    data_m = other.data_m;
    other.data_m = tmp_data;
}

// Implemented by Yurii Zinchuk
char &my_str_t::operator[](size_t idx) {
    if (idx >= size_m) {
        throw std::out_of_range("Index is out of range");
    }

    return data_m[idx];
}

// Implemented by Yurii Zinchuk
const char &my_str_t::operator[](size_t idx) const {
    if (idx >= size_m) {
        throw std::out_of_range("Index is out of range");
    }

    return data_m[idx];
}

// Implemented by Pavlo Kryven
char &my_str_t::at(size_t idx) {
    if (idx >= size_m) {
        throw std::out_of_range("Index is out of range");
    }

    return data_m[idx];
}

// Implemented by Andrew Yaroshevych
const char &my_str_t::at(size_t idx) const {
    if (idx >= size_m) {
        throw std::out_of_range("Index is out of range");
    }

    return data_m[idx];
}

// Implemented by Andrew Yaroshevych
void my_str_t::reserve(size_t new_capacity) {
    if (new_capacity <= capacity_m) {
        return;
    }

    capacity_m = new_capacity;

    char *new_data = new char[capacity_m + 1];
    std::memcpy(new_data, data_m, size_m + 1);

    delete[] data_m;
    data_m = new_data;
}

// Implemented by Andrew Yaroshevych
void my_str_t::shrink_to_fit() {
    if (size_m == capacity_m) {
        return;
    }

    capacity_m = calculate_min_capacity(size_m);
    char *new_data = new char[capacity_m + 1];

    std::memcpy(new_data, data_m, size_m + 1);

    delete[] data_m;
    data_m = new_data;
}

// Implemented by Pavlo Kryven
void my_str_t::resize(size_t new_size, char new_char) {
    if (new_size == size_m) {
        return;
    }

    if (new_size > capacity_m) {
        reserve(calculate_capacity(new_size));

        for (size_t i = 0; i < new_size - size_m; ++i) {
            data_m[size_m + i] = new_char;
        }

        data_m[new_size] = '\0';
        size_m = new_size;

        return;
    }

    if (new_size > size_m) {
        for (size_t i = 0; i < new_size - size_m; ++i) {
            data_m[size_m + i] = new_char;
        }

        data_m[new_size] = '\0';
        size_m = new_size;

        return;
    } else {
        size_m = new_size;
        data_m[size_m] = '\0';
    }
}

// Implemented by Pavlo Kryven
void my_str_t::clear() {
    data_m[0] = '\0';
    size_m = 0;
}

// Implemented by Andrew Yaroshevych
void my_str_t::insert(size_t idx, const my_str_t &str) {
    if (idx >= size_m) {
        throw std::out_of_range("Index is out of range");
    }

    if (this == &str) {
        my_str_t tmp(str); // NOLINT(performance-unnecessary-copy-initialization)
        insert(idx, tmp);
        return;
    }

    size_t new_size = size_m + str.size_m;

    if (new_size > capacity_m) {
        reserve(calculate_capacity(new_size));
    }

    size_m = new_size;

    std::memmove(data_m + idx + str.size_m, data_m + idx, size_m - idx - str.size_m);
    std::memcpy(data_m + idx, str.data_m, str.size_m);

    data_m[size_m] = '\0';
}

// Implemented by Andrew Yaroshevych
void my_str_t::insert(size_t idx, const char *cstr) {
    if (idx >= size_m) {
        throw std::out_of_range("Index is out of range");
    }

    if (*this == cstr) {
        my_str_t tmp(cstr);
        insert(idx, tmp);
        return;
    }

    size_t cstr_size = strlen(cstr);

    size_t new_size = size_m + cstr_size;

    if (new_size > capacity_m) {
        reserve(calculate_capacity(new_size));
    }

    size_m = new_size;

    std::memmove(data_m + idx + cstr_size, data_m + idx, size_m - idx - cstr_size);
    std::memcpy(data_m + idx, cstr, cstr_size);

    data_m[size_m] = '\0';
}

// Implemented by Andrew Yaroshevych
void my_str_t::append(const my_str_t &str) {
    size_t new_size = size_m + str.size_m;

    if (new_size > capacity_m) {
        reserve(calculate_capacity(new_size));
    }

    size_m = new_size;

    std::memcpy(data_m + size_m - str.size_m, str.data_m, str.size_m);

    data_m[size_m] = '\0';
}

// Implemented by Andrew Yaroshevych
void my_str_t::append(char c) {
    if (size_m + 1 > capacity_m) {
        reserve(calculate_capacity(size_m + 1));
    }

    data_m[size_m] = c;

    size_m++;
    data_m[size_m] = '\0';
}

// Implemented by Andrew Yaroshevych
void my_str_t::append(const char *cstr) {
    size_t cstr_size = strlen(cstr);

    size_t new_size = size_m + cstr_size;

    if (new_size > capacity_m) {
        reserve(calculate_capacity(new_size));
    }

    size_m = new_size;

    std::memcpy(data_m + size_m - cstr_size, cstr, cstr_size);

    data_m[size_m] = '\0';
}

// Implemented by Pavlo Kryven
void my_str_t::erase(size_t begin, size_t size) {
    if (begin >= size_m) {
        throw std::out_of_range("Begin index is out of range");
    }

    size_t new_size = size_m - std::min(size, size_m - begin);
    char *new_data = new char[calculate_capacity(new_size) + 1];

    std::memmove(new_data, data_m, begin);

    if (size + begin < size_m) {
        std::memmove(new_data + begin, data_m + begin + size, size_m - size - begin);
    }

    size_m = new_size;
    new_data[size_m] = '\0';

    delete[] data_m;
    data_m = new_data;

    this->shrink_to_fit();
}

// Implemented by Andrew Yaroshevych
size_t my_str_t::size() const noexcept {
    return size_m;
}

// Implemented by Andrew Yaroshevych
size_t my_str_t::capacity() const noexcept {
    return capacity_m;
}

// Implemented by Andrew Yaroshevych
const char *my_str_t::c_str() const {
    return data_m;
}

// Implemented by Yurii Zinchuk
size_t my_str_t::find(char c, size_t idx) {
    if (idx >= size_m) {
        throw std::out_of_range("Index out of range");
    }

    for (size_t i = idx; i < size_m; ++i) {
        if (c == data_m[i]) {
            return i;
        }
    }

    return not_found;
}

// Implemented by Yurii Zinchuk
size_t my_str_t::find(const std::string &str, size_t idx) {
    size_t str_size = str.size();

    if (idx >= size_m) {
        throw std::out_of_range("Index out of range");
    }

    if (size_m - idx < str_size || str_size == 0) {
        return not_found;
    }

    for (size_t i = idx; i < size_m - str_size + 1; ++i) {
        if (data_m[i] == str.at(0)) {
            for (size_t j = 0; j < str_size; ++j) {
                if (data_m[i + j] != str.at(j)) {
                    break;
                }
                if (j == str_size - 1) {
                    return i;
                }
            }
        }
    }

    return not_found;
}

// Implemented by Yurii Zinchuk
size_t my_str_t::find(const char *cstr, size_t idx) {
    size_t str_size = strlen(cstr);

    if (idx >= size_m) {
        throw std::out_of_range("Index out of range");
    }

    if (size_m - idx < str_size || str_size == 0) {
        return not_found;
    }

    for (size_t i = idx; i < size_m - str_size + 1; i++) {
        if (data_m[i] == cstr[0]) {
            for (size_t j = 0; j < str_size; ++j) {
                if (data_m[i + j] != cstr[j]) {
                    break;
                }
                if (j == str_size - 1) {
                    return i;
                }
            }
        }
    }

    return not_found;
}

// Implemented by Yurii Zinchuk
my_str_t my_str_t::substr(size_t begin, size_t size) {
    if (begin >= size_m) {
        throw std::out_of_range("Begin index is out of range");
    }

    if (size == 0) {
        return {};
    }

    size_t new_size = std::min(size, size_m - begin);
    char *new_data = new char[new_size + 1];

    std::memcpy(new_data, data_m + begin, new_size);
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);
    delete[] new_data;

    return new_str;
}

// Implemented by Pavlo Kryven
my_str_t::~my_str_t() {
    delete[] data_m;
}

// Implemented by Pavlo Kryven
std::ostream &operator<<(std::ostream &stream, const my_str_t &str) {
    stream << str.c_str();
    return stream;
}

// Implemented by Andrew Yaroshevych
std::istream &operator>>(std::istream &stream, my_str_t &str) {
    char *buffer = new char[4096];
    stream >> buffer;
    str = my_str_t(buffer);
    delete[] buffer;
    return stream;
}

// Implemented by Andrew Yaroshevych
std::istream &readline(std::istream &stream, my_str_t &str) {
    char *buffer = new char[4096];
    size_t buffer_size = 4096;
    size_t buffer_idx = 0;
    char c;

    while (stream.get(c)) {
        if (buffer_idx == buffer_size - 1) {
            buffer_size *= 2;
            char *new_buffer = new char[buffer_size];
            std::memcpy(new_buffer, buffer, buffer_idx);
            delete[] buffer;
            buffer = new_buffer;
        }
        if (c == '\n') {
            break;
        }
        buffer[buffer_idx] = c;
        buffer_idx++;
    }

    buffer[buffer_idx] = '\0';

    str = my_str_t(buffer);
    delete[] buffer;

    return stream;
}

// Implemented by Andrew Yaroshevych
my_str_t operator+(const my_str_t &str1, const my_str_t &str2) {
    size_t new_size = str1.size_m + str2.size_m;
    char *new_data = new char[new_size + 1];

    std::memcpy(new_data, str1.data_m, str1.size_m);
    std::memcpy(new_data + str1.size_m, str2.data_m, str2.size_m);
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);
    delete[] new_data;

    return new_str;
}

// Implemented by Andrew Yaroshevych
my_str_t operator+(const my_str_t &str1, const std::string &str2) {
    size_t new_size = str1.size() + str2.size();
    char *new_data = new char[new_size + 1];

    std::memcpy(new_data, str1.c_str(), str1.size());
    std::memcpy(new_data + str1.size(), str2.c_str(), str2.size());
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);
    delete[] new_data;

    return new_str;
}

// Implemented by Andrew Yaroshevych
my_str_t operator+(const std::string &str1, const my_str_t &str2) {
    size_t new_size = str1.size() + str2.size();
    char *new_data = new char[new_size + 1];

    std::memcpy(new_data, str1.c_str(), str1.size());
    std::memcpy(new_data + str1.size(), str2.c_str(), str2.size());
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);
    delete[] new_data;

    return new_str;
}

// Implemented by Andrew Yaroshevych
my_str_t operator+(const my_str_t &str1, const char *cstr) {
    size_t new_size = str1.size() + strlen(cstr);
    char *new_data = new char[new_size + 1];

    std::memcpy(new_data, str1.c_str(), str1.size());
    std::memcpy(new_data + str1.size(), cstr, strlen(cstr));
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);
    delete[] new_data;

    return new_str;
}

// Implemented by Andrew Yaroshevych
my_str_t operator+(const char *cstr, const my_str_t &str2) {
    size_t new_size = strlen(cstr) + str2.size();
    char *new_data = new char[new_size + 1];

    std::memcpy(new_data, cstr, strlen(cstr));
    std::memcpy(new_data + strlen(cstr), str2.c_str(), str2.size());
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);
    delete[] new_data;

    return new_str;
}

// Implemented by Andrew Yaroshevych
my_str_t operator+(const my_str_t &str1, char c) {
    size_t new_size = str1.size() + 1;
    char *new_data = new char[new_size + 1];

    std::memcpy(new_data, str1.c_str(), str1.size());
    new_data[str1.size()] = c;
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);
    delete[] new_data;

    return new_str;
}

// Implemented by Andrew Yaroshevych
void operator+=(my_str_t &str1, const my_str_t &str2) {
    str1.append(str2);
}

// Implemented by Andrew Yaroshevych
void operator+=(my_str_t &str1, const std::string &str2) {
    str1.append(str2.c_str());
}

// Implemented by Andrew Yaroshevych
void operator+=(my_str_t &str1, const char *cstr) {
    str1.append(cstr);
}

// Implemented by Andrew Yaroshevych
void operator+=(my_str_t &str1, char c) {
    str1.append(c);
}

// Implemented by Andrew Yaroshevych
my_str_t operator*(const my_str_t &str, int n) {
    if (n == 0) {
        return my_str_t{};
    }
    if (n < 0) {
        throw std::invalid_argument("n must be positive");
    }

    size_t new_size = str.size() * n;
    char *new_data = new char[new_size + 1];

    for (size_t i = 0; i < n; i++) {
        std::memcpy(new_data + i * str.size(), str.c_str(), str.size());
    }
    new_data[new_size] = '\0';

    my_str_t new_str(new_data);

    delete[] new_data;

    return new_str;
}

// Implemented by Andrew Yaroshevych
my_str_t operator*(int n, const my_str_t &str) {
    my_str_t new_str = str * n;

    return new_str;
}

// Implemented by Andrew Yaroshevych
void operator*=(my_str_t &str, int n) {
    str = str * n;
}

// Implemented by Yurii Zinchuk
bool operator==(const my_str_t &str1, const my_str_t &str2) {
    size_t str1_size = str1.size();
    size_t str2_size = str2.size();

    if (str1_size != str2_size) {
        return false;
    }

    for (size_t i = 0; i < str1_size; i++) {
        if (str1.at(i) != str2.at(i)) {
            return false;
        }
    }

    return true;
}

// Implemented by Yurii Zinchuk
bool operator!=(const my_str_t &str1, const my_str_t &str2) {
    if (str1 == str2) {
        return false;
    }

    return true;
}

// Implemented by Yurii Zinchuk
bool operator>(const my_str_t &str1, const my_str_t &str2) {
    size_t str1_size = str1.size();
    size_t str2_size = str2.size();

    if (str1 == str2) {
        return false;
    }

    if (str1_size >= str2_size) {
        for (int i = 0; i < str2_size; ++i) {
            if (str1.at(i) < str2.at(i)) {
                return false;
            }
        }

        return true;
    } else if (str1_size < str2_size) {
        for (int i = 0; i < str1_size; ++i) {
            if (str1.at(i) < str2.at(i)) {
                return false;
            } else if (str1.at(i) > str2.at(i)) {
                return true;
            }
        }
    }

    return false;
}

// Implemented by Yurii Zinchuk
bool operator>=(const my_str_t &str1, const my_str_t &str2) {
    if (str1 == str2 || str1 > str2) {
        return true;
    }

    return false;
}

// Implemented by Yurii Zinchuk
bool operator<(const my_str_t &str1, const my_str_t &str2) {
    if (str1 >= str2) {
        return false;
    }

    return true;
}

// Implemented by Yurii Zinchuk
bool operator<=(const my_str_t &str1, const my_str_t &str2) {
    if (str1 > str2) {
        return false;
    }

    return true;
}

// Implemented by Yurii Kharabara
bool operator==(const my_str_t &str1, const char *cstr) {
    size_t str1_size = str1.size();
    size_t cstr_size = strlen(cstr);

    if (str1_size != cstr_size) {
        return false;
    }

    for (int i = 0; i < str1_size; ++i) {
        if (str1.at(i) != cstr[i]) {
            return false;
        }
    }

    return true;
}

// Implemented by Yurii Kharabara
bool operator!=(const my_str_t &str1, const char *cstr) {
    if (str1 == cstr) {
        return false;
    }

    return true;
}

// Implemented by Yurii Kharabara
bool operator>(const my_str_t &str1, const char *cstr) {
    size_t str1_size = str1.size();
    size_t cstr_size = strlen(cstr);

    if (str1 == cstr) {
        return false;
    }

    if (str1_size >= cstr_size) {
        for (int i = 0; i < cstr_size; ++i) {
            if (str1.at(i) < cstr[i]) {
                return false;
            }
        }

        return true;
    } else if (str1_size < cstr_size) {
        for (int i = 0; i < str1_size; ++i) {
            if (str1.at(i) < cstr[i]) {
                return false;
            } else if (str1.at(i) > cstr[i]) {
                return true;
            }
        }
    }
    return false;
}

// Implemented by Yurii Kharabara
bool operator>=(const my_str_t &str1, const char *cstr) {
    if (str1 == cstr || str1 > cstr) {
        return true;
    }

    return false;
}

// Implemented by Yurii Kharabara
bool operator<(const my_str_t &str1, const char *cstr) {
    if (str1 >= cstr) {
        return false;
    }

    return true;
}

// Implemented by Yurii Kharabara
bool operator<=(const my_str_t &str1, const char *cstr) {
    if (str1 > cstr) {
        return false;
    }

    return true;
}

// Implemented by Yurii Zinchuk
bool operator==(const char *cstr1, const my_str_t &str2) {
    size_t str1_size = strlen(cstr1);
    size_t str2_size = str2.size();

    if (str1_size != str2_size) {
        return false;
    }

    for (int i = 0; i < str1_size; ++i) {
        if (cstr1[i] != str2.at(i)) {
            return false;
        }
    }

    return true;
}

// Implemented by Yurii Zinchuk
bool operator!=(const char *cstr1, const my_str_t &str2) {
    if (cstr1 == str2) {
        return false;
    }

    return true;
}

// Implemented by Yurii Zinchuk
bool operator>(const char *cstr1, const my_str_t &str2) {
    size_t str1_size = strlen(cstr1);
    size_t str2_size = str2.size();

    if (cstr1 == str2) {
        return false;
    }

    if (str1_size >= str2_size) {
        for (int i = 0; i < str2_size; ++i) {
            if (cstr1[i] < str2.at(i)) {
                return false;
            }
        }

        return true;
    } else if (str1_size < str2_size) {
        for (int i = 0; i < str1_size; ++i) {
            if (cstr1[i] < str2.at(i)) {
                return false;
            } else if (cstr1[i] > str2.at(i)) {
                return true;
            }
        }
    }

    return false;
}

// Implemented by Yurii Zinchuk
bool operator>=(const char *cstr1, const my_str_t &str2) {
    if (cstr1 == str2 || cstr1 > str2) {
        return true;
    }

    return false;
}

// Implemented by Yurii Zinchuk
bool operator<(const char *cstr1, const my_str_t &str2) {
    if (cstr1 >= str2) {
        return false;
    }

    return true;
}

// Implemented by Yurii Zinchuk
bool operator<=(const char *cstr1, const my_str_t &str2) {
    if (cstr1 > str2) {
        return false;
    }

    return true;
}
