//
// Created by Andrew Yaroshevych on 02.10.2022.
//

#include <iostream>

#include "../library/mystring.h"
#include "gtest/gtest.h"

// Implemented by Andrew Yaroshevych
TEST(size, size) {
    my_str_t test1 = my_str_t("123456789");
    EXPECT_EQ(test1.size(), 9);
}
// Implemented by Andrew Yaroshevych
TEST(size, size_0) {
    my_str_t test1 = my_str_t();
    EXPECT_EQ(test1.size(), 0);

    my_str_t test2 = my_str_t("");
    EXPECT_EQ(test2.size(), 0);
}
// Implemented by Andrew Yaroshevych
TEST(capacity, capacity) {
    my_str_t test1 = my_str_t("123456789");
    EXPECT_EQ(test1.capacity(), 15);

    my_str_t test2 = my_str_t("123456789abcdefg");
    EXPECT_EQ(test2.capacity(), 31);

    my_str_t test3 = my_str_t();
    EXPECT_EQ(test3.capacity(), 15);
}
// Implemented by Andrew Yaroshevych
TEST(at, at) {
    my_str_t test1 = my_str_t("123456789");
    EXPECT_EQ(test1.at(5), '6');
    EXPECT_THROW(test1.at(9), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(at, const_at) {
    const my_str_t test1 = my_str_t("Hello");
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(4), 'o');
    EXPECT_THROW(test1.at(5), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(default_constructor, default_constructor) {
    my_str_t test1 = my_str_t();
    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
}
// Implemented by Andrew Yaroshevych
TEST(constructor_with_size, constructor_with_size_default_case) {
    my_str_t test1 = my_str_t(15, 'a');
    EXPECT_EQ(test1.size(), 15);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_EQ(test1.at(0), 'a');

    my_str_t test2 = my_str_t(5, '\t');
    EXPECT_EQ(test2.size(), 5);
    EXPECT_EQ(test2.capacity(), 15);
    EXPECT_EQ(test2.at(3), '\t');
}
// Implemented by Andrew Yaroshevych
TEST(constructor_with_size, handles_size_zero) {
    my_str_t test2 = my_str_t(0, 'a');
    EXPECT_EQ(test2.size(), 0);
    EXPECT_EQ(test2.capacity(), 15);
    EXPECT_THROW(test2.at(0), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(constructor_with_size, handles_big_size) {
    my_str_t test3 = my_str_t(1024, 'a');
    EXPECT_EQ(test3.size(), 1024);
    EXPECT_EQ(test3.capacity(), 2047);
    EXPECT_EQ(test3.at(0), 'a');
    EXPECT_EQ(test3.at(1023), 'a');
    ASSERT_THROW(test3.at(1024), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(cstr_constructor, cstr_constructor_default_case) {
    my_str_t test1 = my_str_t("Hello");
    EXPECT_EQ(test1.size(), 5);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(4), 'o');
}
// Implemented by Andrew Yaroshevych
TEST(cstr_constructor, cstr_constructor_handles_empty_string) {
    my_str_t test2 = my_str_t("");
    EXPECT_EQ(test2.size(), 0);
    EXPECT_EQ(test2.capacity(), 15);
    ASSERT_THROW(test2.at(0), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(string_constructor, string_constructor_default_case) {
    std::string str = "Hello, world!";
    my_str_t test1 = my_str_t(str);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(12), '!');
    EXPECT_THROW(test1.at(13), std::out_of_range);

    std::string str2 = "Hello. I am a string. I am not a char array.";
    my_str_t test2 = my_str_t(str2);

    EXPECT_EQ(test2.size(), 44);
    EXPECT_EQ(test2.capacity(), 63);
    EXPECT_EQ(test2.at(0), 'H');
    EXPECT_EQ(test2.at(43), '.');
    EXPECT_THROW(test2.at(44), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(string_constructor, string_constructor_handles_empty_string) {
    std::string str = "";  // NOLINT(readability-redundant-string-init)
    my_str_t test1 = my_str_t(str);

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_THROW(test1.at(0), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(copy_constructor, copy_constructor) {
    my_str_t test1 = my_str_t("Hello");
    my_str_t test2 = my_str_t(test1);

    EXPECT_EQ(test1.size(), test2.size());
    EXPECT_EQ(test1.capacity(), test2.capacity());
    EXPECT_EQ(test1.at(0), test2.at(0));
    EXPECT_EQ(test1.at(4), test2.at(4));
}
// Implemented by Andrew Yaroshevych
TEST(assignment_operator, assignment_operator) {
    my_str_t test1 = my_str_t("Hello");
    my_str_t test2 = my_str_t(10, 'c');
    test2 = test1;

    EXPECT_EQ(test1.size(), test2.size());
    EXPECT_EQ(test1.capacity(), test2.capacity());
    EXPECT_EQ(test1.at(0), test2.at(0));
    EXPECT_EQ(test1.at(4), test2.at(4));

    my_str_t test3 = my_str_t(512, 'a');
    test1 = test3;

    EXPECT_EQ(test1.size(), test3.size());
    EXPECT_EQ(test1.capacity(), test3.capacity());
    EXPECT_EQ(test1.at(0), test3.at(0));
    EXPECT_EQ(test1.at(511), test3.at(511));
}
// Implemented by Andrew Yaroshevych
TEST(assignment_operator, assignment_oprator_handles_self_assignment) {
    my_str_t test1 = my_str_t("Hello");
    test1 = test1;

    EXPECT_EQ(test1.size(), 5);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(4), 'o');
}
// Implemented by Andrew Yaroshevych
TEST(swap, swap) {
    my_str_t test1 = my_str_t("Hello, world!");
    my_str_t test2 = my_str_t("World, hello! Hello, world!");
    test1.swap(test2);

    EXPECT_EQ(test1.size(), 27);
    EXPECT_EQ(test1.capacity(), 31);
    EXPECT_EQ(test1.at(0), 'W');
    EXPECT_EQ(test1.at(26), '!');

    EXPECT_EQ(test2.size(), 13);
    EXPECT_EQ(test2.capacity(), 15);
    EXPECT_EQ(test2.at(0), 'H');
    EXPECT_EQ(test2.at(12), '!');
}
// Implemented by Andrew Yaroshevych
TEST(swap, swap_handles_self_swap) {
    my_str_t test1 = my_str_t("Hello, world!");
    test1.swap(test1);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(12), '!');
}
// Implemented by Andrew Yaroshevych
TEST(braces_operator, braces_operator) {
    my_str_t test1 = my_str_t("Hello, world!");
    EXPECT_EQ(test1[0], 'H');
    EXPECT_EQ(test1[12], '!');

    test1[0] = 'h';
    EXPECT_EQ(test1[0], 'h');
    EXPECT_EQ(test1[12], '!');

    test1[12] = '?';
    EXPECT_EQ(test1[0], 'h');
    EXPECT_EQ(test1[12], '?');
}
// Implemented by Andrew Yaroshevych
TEST(braces_operator, braces_operator_handles_out_of_range) {
    my_str_t test1 = my_str_t("Hello, world!");
    ASSERT_THROW(test1[13], std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(braces_operator, const_braces_operator) {
    const my_str_t test1 = my_str_t("Hello, world!");
    EXPECT_EQ(test1[0], 'H');
    EXPECT_EQ(test1[12], '!');
}
// Implemented by Andrew Yaroshevych
TEST(braces_operator, const_braces_operator_handles_out_of_range) {
    const my_str_t test1 = my_str_t("Hello, world!");
    ASSERT_THROW(test1[13], std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(reserve, reserve) {
    my_str_t test1 = my_str_t("Hello, world!");
    test1.reserve(100);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 100);
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(12), '!');

    test1.reserve(10);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 100);

    test1.reserve(1000);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 1000);
}
// Implemented by Andrew Yaroshevych
TEST(shrink_to_fit, shrink_to_fit) {
    my_str_t test1 = my_str_t(300, 'a');

    EXPECT_EQ(test1.size(), 300);
    EXPECT_EQ(test1.capacity(), 511);

    test1.shrink_to_fit();

    EXPECT_EQ(test1.size(), 300);
    EXPECT_EQ(test1.capacity(), 303);
    EXPECT_EQ(test1.at(0), 'a');
    EXPECT_EQ(test1.at(299), 'a');

    EXPECT_THROW(test1.at(300), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(shrink_to_fit, shrink_to_fit_full_capacity) {
    my_str_t test1 = my_str_t(127, 'a');

    EXPECT_EQ(test1.size(), 127);
    EXPECT_EQ(test1.capacity(), 127);

    test1.shrink_to_fit();

    EXPECT_EQ(test1.size(), 127);
    EXPECT_EQ(test1.capacity(), 127);
}
// Implemented by Andrew Yaroshevych
TEST(resize, resize) {
    my_str_t test1 = my_str_t("Hello, world!");
    test1.resize(13);
    test1.resize(10, 'a');

    EXPECT_EQ(test1.size(), 10);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_EQ(test1.at(0), 'H');

    test1.resize(15, 'b');

    EXPECT_EQ(test1.size(), 15);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(11), 'b');

    test1.resize(30, 'c');
    EXPECT_EQ(test1.size(), 30);
    EXPECT_EQ(test1.capacity(), 31);
    EXPECT_EQ(test1.at(0), 'H');
    EXPECT_EQ(test1.at(11), 'b');
    EXPECT_EQ(test1.at(20), 'c');

}
// Implemented by Andrew Yaroshevych
TEST(clear, clear) {
    my_str_t test1 = my_str_t("Hello, world!");
    test1.clear();

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "");
    EXPECT_THROW(test1.at(0), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(clear, clear_handles_empty_string) {
    my_str_t test1 = my_str_t();
    test1.clear();

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    EXPECT_THROW(test1.at(0), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(clear, clear_big_string) {
    my_str_t test1 = my_str_t(10000, 'a');
    test1.clear();

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 16383);
    EXPECT_THROW(test1.at(0), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(insert, insert_string) {
    my_str_t test1 = my_str_t("Hello,world!");
    my_str_t to_insert = my_str_t(" beautiful ");

    test1.insert(6, to_insert);

    EXPECT_EQ(test1.size(), 23);
    EXPECT_EQ(test1.capacity(), 31);
    ASSERT_TRUE(test1 == "Hello, beautiful world!");
}
// Implemented by Andrew Yaroshevych
TEST(insert, insert_char_array) {
    my_str_t test1 = my_str_t("Hello,world!");
    const char *to_insert = " beautiful ";

    test1.insert(6, to_insert);

    EXPECT_EQ(test1.size(), 23);
    EXPECT_EQ(test1.capacity(), 31);
    ASSERT_TRUE(test1 == "Hello, beautiful world!");
}
// Implemented by Andrew Yaroshevych
TEST(insert, insert_handles_out_of_range) {
    my_str_t test1 = my_str_t("Hello,world!");
    my_str_t to_insert = my_str_t(" beautiful ");

    ASSERT_THROW(test1.insert(12, to_insert), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(insert, insert_hangles_cstr_out_of_range) {
    my_str_t test1 = my_str_t("Hello,world!");
    const char *to_insert = " beautiful ";

    ASSERT_THROW(test1.insert(12, to_insert), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(insert, insert_handles_empty_string) {
    my_str_t test1 = my_str_t("Hello, world!");
    my_str_t to_insert = my_str_t("");

    test1.insert(6, to_insert);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(append, append_string) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t to_append = my_str_t("world!");
    test1.append(to_append);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, world!");

    my_str_t to_append2 = my_str_t(" What's about your capacity?");
    test1.append(to_append2);

    EXPECT_EQ(test1.size(), 41);
    EXPECT_EQ(test1.capacity(), 63);
    ASSERT_TRUE(test1 == "Hello, world! What's about your capacity?");
}
// Implemented by Andrew Yaroshevych
TEST(append, append_string_handles_empty_string) {
    my_str_t test1 = my_str_t("Hello");
    my_str_t to_append = my_str_t("");
    test1.append(to_append);

    EXPECT_EQ(test1.size(), 5);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello");
}
// Implemented by Andrew Yaroshevych
TEST(append, append_char) {
    my_str_t test1 = my_str_t("Hello");
    test1.append('!');

    EXPECT_EQ(test1.size(), 6);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello!");

    my_str_t test2 = my_str_t("Hello, world! What's about your capacity?");
    test2.append('!');

    EXPECT_EQ(test2.size(), 42);
    EXPECT_EQ(test2.capacity(), 63);
    ASSERT_TRUE(test2 == "Hello, world! What's about your capacity?!");
}
// Implemented by Andrew Yaroshevych
TEST(append, append_char_handles_overflow) {
    my_str_t test1 = my_str_t(15, 'a');
    test1.append('b');

    EXPECT_EQ(test1.size(), 16);
    EXPECT_EQ(test1.capacity(), 31);
    ASSERT_TRUE(test1 == "aaaaaaaaaaaaaaab");
}
// Implemented by Andrew Yaroshevych
TEST(append, append_char_array) {
    my_str_t test1 = my_str_t("Hello, ");
    const char *to_append = "world!";
    test1.append(to_append);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, world!");

    const char *to_append2 = " What's about your capacity?";
    test1.append(to_append2);

    EXPECT_EQ(test1.size(), 41);
    EXPECT_EQ(test1.capacity(), 63);
    ASSERT_TRUE(test1 == "Hello, world! What's about your capacity?");
}
// Implemented by Andrew Yaroshevych
TEST(append, append_char_array_handles_empty_array) {
    my_str_t test1 = my_str_t("Hello");
    const char *to_append = "";
    test1.append(to_append);

    EXPECT_EQ(test1.size(), 5);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello");
}
// Implemented by Andrew Yaroshevych
TEST(erase, erase) {
    my_str_t test1 = my_str_t("Hello, world!");
    test1.erase(6, 1);

    EXPECT_EQ(test1.size(), 12);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello,world!");

    test1.erase(0, 13);

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
}
// Implemented by Andrew Yaroshevych
TEST(erase, erase_handles_out_of_range) {
    my_str_t test1 = my_str_t("Hello, world!");
    ASSERT_THROW(test1.erase(13, 1), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(erase, erase_handles_empty_erase) {
    my_str_t test1 = my_str_t("Hello, world!");
    test1.erase(10, 0);

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
}
// Implemented by Andrew Yaroshevych
TEST(erase, erase_up_to_the_end) {
    my_str_t test1 = my_str_t("Hello, world!");
    test1.erase(10, 10);
    EXPECT_EQ(test1.size(), 10);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, wor");
}
// Implemented by Andrew Yaroshevych
TEST(cstr, cstr) {
    my_str_t test1 = my_str_t("Hello, world!");
    const char *cstr = test1.c_str();

    ASSERT_TRUE(test1 == cstr);
}
// Implemented by Andrew Yaroshevych
TEST(cstr, cstr_handles_empty_string) {
    my_str_t test1 = my_str_t("");
    const char *cstr = test1.c_str();

    ASSERT_TRUE(test1 == cstr);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char) {
    my_str_t test1 = my_str_t("Hello, world!");
    size_t pos = test1.find('o');

    EXPECT_EQ(pos, 4);

    pos = test1.find('o', 5);

    EXPECT_EQ(pos, 8);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char_handles_not_found) {
    my_str_t test1 = my_str_t("Hello, world!");
    size_t pos = test1.find('a');

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char_handles_out_of_range) {
    my_str_t test1 = my_str_t("Hello, world!");
    ASSERT_THROW(test1.find('o', 13), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_string) {
    my_str_t test1 = my_str_t("Hello, world!");
    std::string to_find = "world";
    size_t pos = test1.find(to_find, 0);

    EXPECT_EQ(pos, 7);

    std::string to_find2 = "world?";
    pos = test1.find(to_find2, 0);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_string_handles_overflow) {
    my_str_t test1 = my_str_t("Hello, world!");
    std::string to_find = "world";
    size_t pos = test1.find(to_find, 8);

    EXPECT_EQ(pos, my_str_t::not_found);

    std::string to_find2 = "world! What's about your capacity?";
    pos = test1.find(to_find2, 7);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_string_handles_not_found) {
    my_str_t test1 = my_str_t("Hello, world!");
    std::string to_find = "world!";
    size_t pos = test1.find(to_find, 11);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_string_handles_out_of_range) {
    my_str_t test1 = my_str_t("Hello, world!");
    std::string to_find = "world!";

    ASSERT_THROW(test1.find(to_find, 13), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_string_handles_empty_string) {
    my_str_t test1 = my_str_t("Hello, world!");
    std::string to_find = ""; // NOLINT(readability-redundant-string-init)
    size_t pos = test1.find(to_find, 0);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char_array) {
    my_str_t test1 = my_str_t("Hello, world!");
    const char *to_find = "world";
    size_t pos = test1.find(to_find, 0);

    EXPECT_EQ(pos, 7);

    const char *to_find2 = "world?";
    pos = test1.find(to_find2, 0);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char_array_handles_overflow) {
    my_str_t test1 = my_str_t("Hello, world!");
    const char *to_find = "world";
    size_t pos = test1.find(to_find, 8);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char_array_handles_not_found) {
    my_str_t test1 = my_str_t("Hello, world!");
    const char *to_find = "world!";
    size_t pos = test1.find(to_find, 11);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char_array_handles_out_of_range) {
    my_str_t test1 = my_str_t("Hello, world!");
    const char *to_find = "world!";

    ASSERT_THROW(test1.find(to_find, 13), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(find, find_char_array_handles_empty_string) {
    my_str_t test1 = my_str_t("Hello, world!");
    const char *to_find = "";
    size_t pos = test1.find(to_find, 0);

    EXPECT_EQ(pos, my_str_t::not_found);
}
// Implemented by Andrew Yaroshevych
TEST(substr, substr) {
    my_str_t test1 = my_str_t("Hello, world!");
    my_str_t substr = test1.substr(7, 5);

    EXPECT_EQ(substr.size(), 5);
    EXPECT_EQ(substr.capacity(), 15);
    ASSERT_TRUE(substr == "world");
}
// Implemented by Andrew Yaroshevych
TEST(substr, substr_handles_out_of_range) {
    my_str_t test1 = my_str_t("Hello, world!");
    ASSERT_THROW(test1.substr(13, 1), std::out_of_range);
}
// Implemented by Andrew Yaroshevych
TEST(substr, substr_handles_empty_string) {
    my_str_t test1 = my_str_t("Hello, world!");
    my_str_t substr = test1.substr(0, 0);

    EXPECT_EQ(substr.size(), 0);
    EXPECT_EQ(substr.capacity(), 15);
    ASSERT_TRUE(substr == "");
}
// Implemented by Andrew Yaroshevych
TEST(substr, substr_handles_full_string) {
    my_str_t test1 = my_str_t("Hello, world!");
    my_str_t substr = test1.substr(0, 13);

    EXPECT_EQ(substr.size(), 13);
    EXPECT_EQ(substr.capacity(), 15);
    ASSERT_TRUE(substr == "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(substr, substr_handles_full_string_with_overflow) {
    my_str_t test1 = my_str_t("Hello, world!");
    my_str_t substr = test1.substr(0, 30);

    EXPECT_EQ(substr.size(), 13);
    EXPECT_EQ(substr.capacity(), 15);
    ASSERT_TRUE(substr == "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(substr, substr_handles_big_string) {
    my_str_t test1 = my_str_t(1024, 'a');
    my_str_t substr = test1.substr(0, 512);

    EXPECT_EQ(substr.size(), 512);
    EXPECT_EQ(substr.capacity(), 1023);
    ASSERT_TRUE(substr == my_str_t(512, 'a'));
}
// Implemented by Andrew Yaroshevych
TEST(ostream, ostream) {
    my_str_t test1 = my_str_t("Hello, world!");
    std::stringstream ss;
    ss << test1;

    EXPECT_EQ(ss.str(), "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(istream, istream) {
    my_str_t test1;
    std::ostringstream out;
    std::istringstream in("Hello,world!");
    in >> test1;
    out << test1;
    std::cout << test1 << std::endl;
    EXPECT_EQ(test1.size(), 12);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(out.str() == "Hello,world!");
}
// Implemented by Andrew Yaroshevych
TEST(readline, readline) {
    my_str_t test1;
    std::istringstream in("Hello, world! How are you?\n I'm fine, thanks!");

    readline(in, test1);

    EXPECT_EQ(test1.size(), 26);
    EXPECT_EQ(test1.capacity(), 31);
    ASSERT_EQ(test1, "Hello, world! How are you?");
}
// Implemented by Andrew Yaroshevych
TEST(readline, readline_handles_empty_string) {
    my_str_t test1;
    std::istringstream in("");

    readline(in, test1);

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_EQ(test1, "");
}
// Implemented by Andrew Yaroshevych
TEST(readline, readline_handles_empty_stream) {
    my_str_t test1;
    std::istringstream in;

    readline(in, test1);

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_EQ(test1, "");
}
// Implemented by Andrew Yaroshevych
TEST(readline, readline_handles_empty_stream_and_string) {
    my_str_t test1;
    std::istringstream in;

    readline(in, test1);

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_EQ(test1, "");
}
// Implemented by Andrew Yaroshevych
TEST(readline, readline_handles_buffer_expanding) {
    my_str_t test1 = my_str_t(8192, 'a');
    test1.append('\n');

    my_str_t test2 = my_str_t();
    std::istringstream in(test1.c_str());

    readline(in, test2);

    EXPECT_EQ(test2.size(), 8192);
    EXPECT_EQ(test2.capacity(), 16383);

    test1.erase(test1.size() - 1, 1);
    ASSERT_EQ(test2, test1);
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = my_str_t("world!");
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 13);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation_with_empty_string) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = my_str_t();
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 7);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation_std_string) {
    my_str_t test1 = my_str_t("Hello, ");
    std::string test2 = "world!";
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 13);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "Hello, world!");
    my_str_t test4 = test2 + test1;
    EXPECT_EQ(test4.size(), 13);
    EXPECT_EQ(test4.capacity(), 15);
    ASSERT_TRUE(test4 == "world!Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation_std_string_with_empty_string) {
    my_str_t test1 = my_str_t("Hello, ");
    std::string test2 = ""; // NOLINT(readability-redundant-string-init)
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 7);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation_std_string_with_empty_my_str) {
    my_str_t test1 = my_str_t();
    std::string test2 = "world!";
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 6);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "world!");
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation_std_string_with_empty_my_str_and_string) {
    my_str_t test1 = my_str_t();
    std::string test2 = ""; // NOLINT(readability-redundant-string-init)
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 0);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "");
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation_char_array) {
    my_str_t test1 = my_str_t("Hello, ");
    char test2[] = "world!";
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 13);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "Hello, world!");

    my_str_t test4 = test2 + test1;
    EXPECT_EQ(test4.size(), 13);
    EXPECT_EQ(test4.capacity(), 15);
    ASSERT_TRUE(test4 == "world!Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(concatenation, concatenation_char) {
    my_str_t test1 = my_str_t("Hello, ");
    char test2 = '!';
    my_str_t test3 = test1 + test2;

    EXPECT_EQ(test3.size(), 8);
    EXPECT_EQ(test3.capacity(), 15);
    ASSERT_TRUE(test3 == "Hello, !");
}
// Implemented by Andrew Yaroshevych
TEST(append_operator, append_operator) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = my_str_t("world!");
    test1 += test2;

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(append_operator, append_operator_with_empty_string) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = my_str_t();
    test1 += test2;

    EXPECT_EQ(test1.size(), 7);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(append_operator, append_operator_std_string) {
    my_str_t test1 = my_str_t("Hello, ");
    std::string test2 = "world!";
    test1 += test2;

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(append_operator, append_operator_std_string_with_empty_string) {
    my_str_t test1 = my_str_t("Hello, ");
    std::string test2 = ""; // NOLINT(readability-redundant-string-init)
    test1 += test2;

    EXPECT_EQ(test1.size(), 7);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(append_operator, append_operator_char_array) {
    my_str_t test1 = my_str_t("Hello, ");
    char test2[] = "world!";
    test1 += test2;

    EXPECT_EQ(test1.size(), 13);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, world!");
}
// Implemented by Andrew Yaroshevych
TEST(append_operator, append_operator_char) {
    my_str_t test1 = my_str_t("Hello, ");
    char test2 = '!';
    test1 += test2;

    EXPECT_EQ(test1.size(), 8);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "Hello, !");
}
// Implemented by Andrew Yaroshevych
TEST(append_operator, append_operator_char_with_empty_string) {
    my_str_t test1 = my_str_t();
    char test2 = '!';
    test1 += test2;

    EXPECT_EQ(test1.size(), 1);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "!");
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = test1 * 3;

    EXPECT_EQ(test2.size(), 21);
    EXPECT_EQ(test2.capacity(), 31);
    ASSERT_TRUE(test2 == "Hello, Hello, Hello, ");

    my_str_t test3 = 3 * test1;
    EXPECT_EQ(test3.size(), 21);
    EXPECT_EQ(test3.capacity(), 31);
    ASSERT_TRUE(test3 == test2);
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_with_empty_string) {
    my_str_t test1 = my_str_t();
    my_str_t test2 = test1 * 3;

    EXPECT_EQ(test2.size(), 0);
    EXPECT_EQ(test2.capacity(), 15);
    ASSERT_TRUE(test2 == "");
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_with_zero) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = test1 * 0;

    EXPECT_EQ(test2.size(), 0);
    EXPECT_EQ(test2.capacity(), 15);
    ASSERT_TRUE(test2 == "");
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_with_negative) {
    my_str_t test1 = my_str_t("Hello, ");

    ASSERT_THROW(my_str_t test2 = test1 * -3, std::invalid_argument);
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_with_one) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = test1 * 1;

    EXPECT_EQ(test2.size(), 7);
    EXPECT_EQ(test2.capacity(), 15);
    ASSERT_TRUE(test2 == "Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_with_big_number) {
    my_str_t test1 = my_str_t("Hello, ");
    my_str_t test2 = test1 * 100;

    EXPECT_EQ(test2.size(), 700);
    EXPECT_EQ(test2.capacity(), 1023);

    for (size_t i = 0; i < 100; ++i) {
        ASSERT_TRUE(test2.substr(i * 7, 7) == "Hello, ");
    }
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_inplace) {
    my_str_t test1 = my_str_t("Hello, ");
    test1 *= 3;

    EXPECT_EQ(test1.size(), 21);
    EXPECT_EQ(test1.capacity(), 31);
    ASSERT_TRUE(test1 == "Hello, Hello, Hello, ");
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_inplace_with_empty_string) {
    my_str_t test1 = my_str_t();
    test1 *= 3;

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "");
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_inplace_with_zero) {
    my_str_t test1 = my_str_t("Hello, ");
    test1 *= 0;

    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 15);
    ASSERT_TRUE(test1 == "");
}
// Implemented by Andrew Yaroshevych
TEST(multiply_operator, multiply_operator_inplace_with_negative) {
    my_str_t test1 = my_str_t("Hello, ");

    ASSERT_THROW(test1 *= -3, std::invalid_argument);
}
// Implemented by Andrew Yaroshevych
TEST(equal, equal) {
    my_str_t test1 = my_str_t("First lab ");
    std::string helper = "First lab ";
    my_str_t test2 = my_str_t(helper);

    EXPECT_EQ(bool(test1 == test2), true);

    my_str_t test3 = my_str_t("samelength");
    EXPECT_EQ(bool(test2 == test3), false);
}
// Implemented by Andrew Yaroshevych
// Implemented by Pavlo Kryven
#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-use-after-move"
TEST(move_assignment, move_assignment){
    my_str_t test1{"Hello"};
    my_str_t test2 = std::move(test1);
    EXPECT_EQ(test1.size(), 0);
    EXPECT_EQ(test1.capacity(), 0);
    EXPECT_EQ(test1.c_str(), nullptr);

    EXPECT_EQ(test2.size(), 5);
    EXPECT_EQ(test2.capacity(),15);
    ASSERT_TRUE(test2=="Hello");
}
#pragma clang diagnostic pop
// Implemented by Pavlo Kryven
TEST(equal, equal_strings) {
    my_str_t test1 = my_str_t("First lab ");
    my_str_t test2 = my_str_t("First lab ");
    test2.reserve(60);
    EXPECT_EQ(bool(test1 == test2), true);
}
// Implemented by Andrew Yaroshevych
TEST(equal, equal_cstring) {
    const char *test1{"abcdef"};
    my_str_t test2 = my_str_t("abcdef");
    my_str_t test3 = my_str_t("abcde0");
    EXPECT_EQ(bool(test1 == test2), true);
    test2.reserve(50);
    EXPECT_EQ(bool(test1 == test2), true);
    test2.append('a');
    EXPECT_EQ(bool(test1 == test2), false);

    const char *test4{"abcdef"};
    EXPECT_EQ(bool(test4 == test3), false);
    EXPECT_EQ(bool(test3 == test4), false);
}
// Implemented by Andrew Yaroshevych
TEST(not_equal, not_equal) {
    my_str_t test1 = my_str_t("First lab ");
    my_str_t test2 = my_str_t("First lab ");
    EXPECT_EQ(bool(test1!=test2), false);

    const char *test3{"abcdef"};
    my_str_t test4 = my_str_t("abcde0");
    EXPECT_EQ(bool(test3 != test4), true);

    my_str_t test5 = my_str_t("abcdef");
    EXPECT_EQ(bool(test3 != test5), false);
}
// Implemented by Andrew Yaroshevych
TEST(not_equal, not_equal_cstr) {
    my_str_t test1 = my_str_t("First lab");
    const char *test2{"First lab"};

    EXPECT_EQ(bool(test1 != test2), false);

    const char *test3{"Hello, world!"};
    EXPECT_EQ(bool(test1 != test3), true);
}
// Implemented by Pavlo Kryven
TEST(not_equal, not_equal_true) {
    my_str_t test1 = my_str_t("First lab");
    my_str_t test2 = my_str_t("Hello, world!");
    EXPECT_EQ(bool(test1!=test2), true);
}
// Implemented by Pavlo Kryven
TEST(greater_than, greater_than_string) {
    my_str_t test1 = my_str_t("First lab ");
    my_str_t test2 = my_str_t("First lab ");
    EXPECT_EQ(bool(test1>test2), false);
    EXPECT_EQ(bool(test2>test1), false);

    test2.erase(8, 5);
    EXPECT_EQ(bool(test1>test2), true);

    my_str_t test3 = my_str_t("First lab 1");
    my_str_t test4 = my_str_t("First lab 2. You are the best!");
    EXPECT_EQ(bool(test4>test3), true);
    EXPECT_EQ(bool(test3>test4), false);

    my_str_t test5 = my_str_t("First lab 2");
    my_str_t test6 = my_str_t("First lab 1. You are the best!");

    EXPECT_EQ(bool(test5>test6), true);
    EXPECT_EQ(bool(test6>test5), false);

    test2.erase(0, 10);
    EXPECT_EQ(bool(test3>test2), true);
}
// Implemented by Pavlo Kryven
TEST(greater_than, greater_than_cstring) {
    my_str_t test1 = my_str_t("hello, world");
    const char *test2 = "hello, world";
    const char *test3 = "a new, world";
    EXPECT_EQ(bool(test1>test2), false);
    EXPECT_EQ(bool(test2>test1), false);

    test1.erase(11, 1);
    EXPECT_EQ(bool(test1>test2), false);
    EXPECT_EQ(bool(test1>test3), true);

    char test4[]{"First lab 1."};
    my_str_t test5 = my_str_t("First lab 2. You are the best!");
    EXPECT_EQ(bool(test5>test4), true);
    EXPECT_EQ(bool(test4>test5), false);

    char test6[]{"First lab 2."};
    my_str_t test7 = my_str_t("First lab 1. You are the best!");

    char test8[]{"First lab 2. You are the best!"};
    EXPECT_EQ(bool(test6>test7), true);
    EXPECT_EQ(bool(test7>test6), false);

    test7.erase(13, 17);
    EXPECT_EQ(bool(test7>test8), false);
}
// Implemented by Pavlo Kryven
TEST(less_than, less_than_cstring) {
    my_str_t test1 = my_str_t("hello, world");
    const char *test2 = "hello, world";
    const char *test3 = "a new, world";
    EXPECT_EQ(bool(test1<test2), false);
    EXPECT_EQ(bool(test2<test1), false);

    test1.erase(11, 1);
    EXPECT_EQ(bool(test1<test2), true);
    EXPECT_EQ(bool(test1<test3), false);

    const char *test4{"First lab 2."};
    my_str_t test5 = my_str_t("First lab 1.");
    EXPECT_EQ(bool(test4<test5), false);

    my_str_t test6 = my_str_t("First lab 2.");
    EXPECT_EQ(bool(test4<test6), false);

    const char test7[]{"First lab 1."};
    EXPECT_EQ(bool(test7<test6), true);
}
// Implemented by Pavlo Kryven
TEST(less_than, less_than_string) {
    my_str_t test1 = my_str_t("First lab ");
    my_str_t test2 = my_str_t("First lab ");
    EXPECT_EQ(bool(test1<test2), false);

    test2.erase(8, 5);
    EXPECT_EQ(bool(test1<test2), false);
    EXPECT_EQ(bool(test2<test1), true);

    my_str_t test3 = my_str_t("abcd");
    my_str_t test4 = my_str_t("def");
    EXPECT_EQ(bool(test4<test3), false);
    EXPECT_EQ(bool(test3<test4), true);

    test2.erase(0, 10);
    EXPECT_EQ(bool(test3<test2), false);
    EXPECT_EQ(bool(test2<test3), true);

}
// Implemented by Pavlo Kryven
TEST(greater_equal, greater_equal_string) {
    my_str_t test1 = my_str_t("abcd");
    my_str_t test2 = my_str_t("abcd");
    my_str_t test3("");
    EXPECT_EQ(bool(test1>=test2), true);
    test1.append(' ');
    EXPECT_EQ(bool(test1>=test2), true);
    test1.erase(3, 2);
    EXPECT_EQ(bool(test1>=test2), false);
    EXPECT_EQ(bool(test1>=test3), true);
}
// Implemented by Pavlo Kryven
TEST(greater_equal, greater_equal_cstring) {
    my_str_t test1 = my_str_t("abcd");
    const char *test2 = "abcd";
    const char *test3 = "";
    EXPECT_EQ(bool(test1>=test2), true);
    EXPECT_EQ(bool(test2>=test1), true);
    test1.append(' ');
    EXPECT_EQ(bool(test1>=test2), true);
    EXPECT_EQ(bool(test2>=test1), false);
    test1.erase(3, 2);
    EXPECT_EQ(bool(test1>=test2), false);
    EXPECT_EQ(bool(test1>=test3), true);
}
// Implemented by Pavlo Kryven
TEST(less_equal, less_equal_string) {
    my_str_t test1 = my_str_t("First lab ");
    my_str_t test2 = my_str_t("First lab ");
    EXPECT_EQ(bool(test1<=test2), true);
    test1.erase(5, 10);
    EXPECT_EQ(bool(test1<=test2), true);
    test1.insert(0, "zzz");
    EXPECT_EQ(bool(test1<=test2), false);
}
// Implemented by Pavlo Kryven
TEST(less_equal, less_equal_ctring) {
    my_str_t test1 = my_str_t("First lab ");
    const char *test2 = "First lab ";
    EXPECT_EQ(bool(test1<=test2), true);
    EXPECT_EQ(bool(test2<=test1), true);
    test1.erase(5, 10);
    EXPECT_EQ(bool(test1<=test2), true);
    EXPECT_EQ(bool(test2<=test1), false);
    test1.insert(0, "zzz");
    EXPECT_EQ(bool(test1<=test2), false);
    EXPECT_EQ(bool(test2<=test1), true);
}
