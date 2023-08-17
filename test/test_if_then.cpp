
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>
#include <memory>

#include <token.hpp>
#include <tokenizer.hpp>
#include <parser.hpp>
#include <interpreter.hpp>

BOOST_AUTO_TEST_CASE(test_basic_if_true) {
	std::string input = "(if (8 == 8)) (then 7) (else 8)"; // 7 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	//token::printTokens(parsed.get());
	auto result = interpr.solve(*parsed);
	//std::cout << result.value() << std::endl;
	BOOST_CHECK(result.value() == std::to_string(7.0));
	
}

BOOST_AUTO_TEST_CASE(test_basic_if_false) {
	std::string input = "(if (8 == 9)) (then 7) (else 8)"; // 8 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	//token::printTokens(parsed.get());
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(8.0));

}

BOOST_AUTO_TEST_CASE(test_advanced_if_true) {
	std::string input = "(if (8*2 == 8+8)) (then 17+3) (else 17+10)"; // 8 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	//token::printTokens(parsed.get());
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(20.0));

}
BOOST_AUTO_TEST_CASE(test_advanced_if_false) {
	std::string input = "(if (8*2 == 4^8+8)) (then 17+3) (else 17+10)"; // 8 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	//token::printTokens(parsed.get());
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(27.0));

}
BOOST_AUTO_TEST_CASE(test_advanced_if_false_and_other_tokens) {
	std::string input = "2+ (if (8*2 == 4^8+8)) (then 17+3) (else 17+10) * 2"; // 8 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	//token::printTokens(parsed.get());
	auto result = interpr.solve(*parsed);

	BOOST_CHECK(result.value() == std::to_string(56.0));

}
BOOST_AUTO_TEST_CASE(test_advanced_if_false_and_other_tokens_and_variables) {
	std::string input = "result=(2+ (if (8*2 == 4^8+8)) (then 17+3) (else 17+10) * 2)"; // 8 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);

	input = "result-2";
	tokenized = tozr.tokenize(input);
	parsed = parsr.shunting_yard(*tokenized);
	result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(54.0));

}
BOOST_AUTO_TEST_CASE(test_variable_set_when_true) {
	std::string input = "v = (if (8 == 8)) (then 6) (else 5)"; // 8 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);

	input = "v==6";
	tokenized = tozr.tokenize(input);
	parsed = parsr.shunting_yard(*tokenized);
	result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "true");
}
BOOST_AUTO_TEST_CASE(test_variable_set_when_false) {
	std::string input = "v = (if (8 == 7)) (then 6) (else 5)"; // 8 will go back on stack
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	input = "v==5";
	tokenized = tozr.tokenize(input);
	parsed = parsr.shunting_yard(*tokenized);
	result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "true");
}