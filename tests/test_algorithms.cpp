//#include <gtest/gtest.h>
//#include "../lib_algorithms/Algorithms.h"
//#include <iostream>
//
//TEST(ALGTEST, can_do_easy_ex) {
//	std::string b = "()()()";
//	ASSERT_EQ(check_breckets(b), true);
//}
//
//TEST(ALGTEST, empty_str) {
//	std::string b = "";
//	ASSERT_EQ(check_breckets(b), true);
//}
//
//TEST(ALGTEST, one_el) {
//	std::string b = "(";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, nested_brackets) {
//	std::string b = "{[()]}";
//	ASSERT_EQ(check_breckets(b), true);
//}
//
//TEST(ALGTEST, unbalanced_open_brackets) {
//	std::string b = "(((";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, unbalanced_close_brackets) {
//	std::string b = ")))";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, mixed_unbalanced_brackets) {
//	std::string b = "{[)]}";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, balanced_with_text) {
//	std::string b = "abc{def[ghi(jkl)mno]pqr}stu";
//	ASSERT_EQ(check_breckets(b), true);
//}
//
//TEST(ALGTEST, unbalanced_with_text) {
//	std::string b = "abc{def[ghi(jkl]mno)pqr}stu";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, no_brackets) {
//	std::string b = "abcdef";
//	ASSERT_EQ(check_breckets(b), true);
//}
//
//TEST(ALGTEST, only_closing_brackets) {
//	std::string b = ")}]";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, only_opening_brackets) {
//	std::string b = "{[(";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, mismatched_brackets) {
//	std::string b = "{[}";
//	ASSERT_EQ(check_breckets(b), false);
//}
//
//TEST(ALGTEST, large_balanced_input) {
//	std::string b = std::string(1000, '(') + std::string(1000, ')');
//	ASSERT_EQ(check_breckets(b), true);
//}
//
//TEST(ALGTEST, large_unbalanced_input) {
//	std::string b = std::string(1000, '(') + std::string(999, ')');
//	ASSERT_EQ(check_breckets(b), false);
//}