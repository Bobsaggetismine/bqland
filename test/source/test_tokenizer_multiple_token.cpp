#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>
#include <memory>

#include <token.hpp>
#include <tokenizer.hpp>


BOOST_AUTO_TEST_CASE(test_multiple_tokens_size) {
	std::string input = "x=6";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->size() == 3);

	input = "print(x=6)";
	auto tokens2 = tokzer.tokenize(input);

	BOOST_CHECK(tokens2->size() == 6);

}

BOOST_AUTO_TEST_CASE(test_multiple_tokens_order) {
	std::string input = "x=6";
	tokenizer tokzer;
	auto tokens = tokzer.tokenize(input);

	BOOST_CHECK(tokens->at(0).type() == token_type::identifier);
	BOOST_CHECK(tokens->at(1).type() == token_type::set);
	BOOST_CHECK(tokens->at(2).type() == token_type::numerical);
	input = "print(x=6)";
	auto tokens2 = tokzer.tokenize(input);
	BOOST_CHECK(tokens2->at(0).type() == token_type::function);
	BOOST_CHECK(tokens2->at(0).value() == "print");
	BOOST_CHECK(tokens2->at(1).type() == token_type::left);
	BOOST_CHECK(tokens2->at(2).type() == token_type::identifier);
	BOOST_CHECK(tokens2->at(2).value() == "x");
	BOOST_CHECK(tokens2->at(3).type() == token_type::set);
	BOOST_CHECK(tokens2->at(4).type() == token_type::numerical);
	BOOST_CHECK(tokens2->at(4).value() == std::to_string(6.0));
	BOOST_CHECK(tokens2->at(5).type() == token_type::right);
}