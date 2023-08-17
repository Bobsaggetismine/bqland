#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>
#include <memory>

#include <token.hpp>
#include <tokenizer.hpp>
#include <parser.hpp>


BOOST_AUTO_TEST_CASE(test_basic_parse_size) {

	tokenizer tokzr;
	parser parsr;

	std::string input = "5+5";
	auto tokens = tokzr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokens.get());

	BOOST_CHECK(parsed->size() == 3);
}
BOOST_AUTO_TEST_CASE(test_basic_parse_order) {

	tokenizer tokzr;
	parser parsr;

	std::string input = "5+5";
	auto tokens = tokzr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokens.get());

	BOOST_CHECK(parsed->at(0).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(1).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(2).type() == token_type::addition);
}

BOOST_AUTO_TEST_CASE(test_complex_parse_size) {

	tokenizer tokzr;
	parser parsr;

	std::string input = "3+4*2/(1-5)^2^3";
	auto tokens = tokzr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokens.get());

	BOOST_CHECK(parsed->size() == 13);
}
BOOST_AUTO_TEST_CASE(test_complex_parse_order) {

	tokenizer tokzr;
	parser parsr;

	std::string input = "3+4*2/(1-5)^2^3";
	auto tokens = tokzr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokens.get());

	BOOST_CHECK(parsed->at(0).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(0).value() == std::to_string(3.0));
	BOOST_CHECK(parsed->at(1).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(1).value() == std::to_string(4.0));
	BOOST_CHECK(parsed->at(2).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(2).value() == std::to_string(2.0));

	BOOST_CHECK(parsed->at(3).type() == token_type::multiplication);
	BOOST_CHECK(parsed->at(4).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(4).value() == std::to_string(1.0));
	BOOST_CHECK(parsed->at(5).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(5).value() == std::to_string(5.0));

	BOOST_CHECK(parsed->at(6).type() == token_type::subtraction);
	BOOST_CHECK(parsed->at(7).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(7).value() == std::to_string(2.0));
	BOOST_CHECK(parsed->at(8).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(8).value() == std::to_string(3.0));

	BOOST_CHECK(parsed->at(9).type()  == token_type::power);
	BOOST_CHECK(parsed->at(10).type() == token_type::power);
	BOOST_CHECK(parsed->at(11).type() == token_type::division);
	BOOST_CHECK(parsed->at(12).type() == token_type::addition);
}

BOOST_AUTO_TEST_CASE(test_extremely_complex_parse_size) {

	tokenizer tokzr;
	parser parsr;

	std::string input = "print(3+4*2/(1-5)^2^3+max(5,6))";
	auto tokens = tokzr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokens.get());

	BOOST_CHECK(parsed->size() == 18);
}
BOOST_AUTO_TEST_CASE(test_extremely_complex_parse_order) {

	tokenizer tokzr;
	parser parsr;

	std::string input = "print(3+4*2/(1-5)^2^3+max(5,6))";
	auto tokens = tokzr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokens.get());
	BOOST_CHECK(parsed->at(0).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(0).value() == std::to_string(3.0));
	BOOST_CHECK(parsed->at(1).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(1).value() == std::to_string(4.0));
	BOOST_CHECK(parsed->at(2).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(2).value() == std::to_string(2.0));

	BOOST_CHECK(parsed->at(3).type() == token_type::multiplication);
	BOOST_CHECK(parsed->at(4).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(4).value() == std::to_string(1.0));
	BOOST_CHECK(parsed->at(5).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(5).value() == std::to_string(5.0));

	BOOST_CHECK(parsed->at(6).type() == token_type::subtraction);
	BOOST_CHECK(parsed->at(7).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(7).value() == std::to_string(2.0));
	BOOST_CHECK(parsed->at(8).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(8).value() == std::to_string(3.0));

	BOOST_CHECK(parsed->at(9).type() == token_type::power);
	BOOST_CHECK(parsed->at(10).type() == token_type::power);
	BOOST_CHECK(parsed->at(11).type() == token_type::division);
	BOOST_CHECK(parsed->at(12).type() == token_type::addition);

	BOOST_CHECK(parsed->at(13).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(13).value() == std::to_string(5.0));
	BOOST_CHECK(parsed->at(14).type() == token_type::numerical);
	BOOST_CHECK(parsed->at(14).value() == std::to_string(6.0));
	BOOST_CHECK(parsed->at(15).type() == token_type::function);
	BOOST_CHECK(parsed->at(15).value() == "max");
	BOOST_CHECK(parsed->at(16).type() == token_type::addition);
	BOOST_CHECK(parsed->at(17).type() == token_type::function);
	BOOST_CHECK(parsed->at(17).value() == "print");

}