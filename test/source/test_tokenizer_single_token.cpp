#define BOOST_TEST_MODULE TEST_GAMELIB


#include <boost/test/included/unit_test.hpp>

#include <string>
#include <vector>
#include <memory>

#include <token.hpp>
#include <tokenizer.hpp>
BOOST_AUTO_TEST_CASE(test_addition) {
	std::string input = "+";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::addition);
}
BOOST_AUTO_TEST_CASE(test_subtraction) {
	std::string input = "-";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::subtraction);
}
BOOST_AUTO_TEST_CASE(test_multiplication) {
	std::string input = "*";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::multiplication);
}
BOOST_AUTO_TEST_CASE(test_division) {
	std::string input = "/";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::division);
}
BOOST_AUTO_TEST_CASE(test_power) {
	std::string input = "^";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::power);
}
BOOST_AUTO_TEST_CASE(test_numerical) {
	std::string input = "6";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::numerical);
	BOOST_CHECK(tokens->at(0).value() == std::to_string(6.0));
}
BOOST_AUTO_TEST_CASE(test_identifier) {
	std::string input = "x";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::identifier);
	BOOST_CHECK(tokens->at(0).value() == "x");
}

BOOST_AUTO_TEST_CASE(test_leftParenthasis) {
	std::string input = "(";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::left);
}
BOOST_AUTO_TEST_CASE(test_rightParenthasis) {
	std::string input = ")";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::right);
}
BOOST_AUTO_TEST_CASE(test_equals) {
	std::string input = "==";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::equals);
}
BOOST_AUTO_TEST_CASE(test_set) {
	std::string input = "=";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::set);
}
BOOST_AUTO_TEST_CASE(test_booleantrue) {
	std::string input = "true";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::bqboolean);
	BOOST_CHECK(tokens->at(0).value() == "true");
}
BOOST_AUTO_TEST_CASE(test_booleanfalse) {
	std::string input = "false";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::bqboolean);
	BOOST_CHECK(tokens->at(0).value() == "false");
}
BOOST_AUTO_TEST_CASE(test_function) {
	std::string input = "print";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 1);
	BOOST_CHECK(tokens->at(0).type() == token_type::function);
	BOOST_CHECK(tokens->at(0).value() == "print");
}
