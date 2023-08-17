#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>
#include <memory>

#include <token.hpp>
#include <tokenizer.hpp>
#include <parser.hpp>
#include <interpreter.hpp>


BOOST_AUTO_TEST_CASE(test_basic_solve) {
	std::string input = "3+3";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(6.f));
}

BOOST_AUTO_TEST_CASE(test_complex_solve) {
	std::string input = "3+4*2/(1-5)^2^3";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(3.00012207031));
}
BOOST_AUTO_TEST_CASE(test_complex_function_solve) {
	std::string input = "max( (3+4*2/(1-5)^2^3),4)";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(4.0));
}
BOOST_AUTO_TEST_CASE(test_solve_with_variable) {
	std::string setupInput = "x=56";
	std::string input = "max(x,55)";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(setupInput);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);

	auto tokenized2 = tozr.tokenize(input);
	auto parsed2 = parsr.shunting_yard(*tokenized2);
	auto result2 = interpr.solve(*parsed2);

	BOOST_CHECK(result2.value() == "x");
}
BOOST_AUTO_TEST_CASE(test_solve_with_variable_complex) {
	std::string setupInput = "x=56";
	std::string input = "max(x,55)";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(setupInput);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);

	auto tokenized2 = tozr.tokenize(input);
	auto parsed2 = parsr.shunting_yard(*tokenized2);
	auto result2 = interpr.solve(*parsed2);

	BOOST_CHECK(result2.value() == "x");
}
BOOST_AUTO_TEST_CASE(test_solve_booleans_basic_false) {
	std::string input = "false==true";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "false");
}
BOOST_AUTO_TEST_CASE(test_solve_booleans_basic_true) {
	std::string input = "true==true";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "true");
}
BOOST_AUTO_TEST_CASE(test_solve_booleans_evaluation_basic_true) {
	std::string input = "33==33";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "true");
}
BOOST_AUTO_TEST_CASE(test_solve_booleans_evaluation_basic_false) {
	std::string input = "34==33";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "false");
}
BOOST_AUTO_TEST_CASE(test_solve_boolean_complex_false) {
	std::string input = "max(66,43)==max(67,32)";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "false");
}
BOOST_AUTO_TEST_CASE(test_solve_boolean_complex_true) {
	std::string input = "max(68,43)==max(34,32)*2";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == "true");
}