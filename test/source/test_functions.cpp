
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>
#include <memory>

#include <token.hpp>
#include <tokenizer.hpp>
#include <parser.hpp>
#include <interpreter.hpp>


BOOST_AUTO_TEST_CASE(test_function_define) {
	std::string input = "func add() 2+2";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;

	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(interpreter::s_getFunction("add")->size() == 3);
}
BOOST_AUTO_TEST_CASE(test_function_call) {
	std::string input = "func add() 2+2";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	input = "add()";
	auto tokenized2 = tozr.tokenize(input);
	auto parsed2 = parsr.shunting_yard(*tokenized2);
	auto result2 = interpr.solve(*parsed2);
	BOOST_CHECK(result2.value() == std::to_string(4.0));
}
BOOST_AUTO_TEST_CASE(test_functions_and_arithmatic) {
	std::string input = "func add() 2+2";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	input = "add()+2";
	auto tokenized2 = tozr.tokenize(input);
	auto parsed2 = parsr.shunting_yard(*tokenized2);
	auto result2 = interpr.solve(*parsed2);
	BOOST_CHECK(result2.value() == std::to_string(6.0));
}

BOOST_AUTO_TEST_CASE(test_add_function_parameters) {
	std::string input = "func add(a,b) a+b";
	tokenizer tozr;
	auto tokenized = tozr.tokenize(input);
	auto functionTokens = interpreter::s_getFunction("add");
	auto functionParameter = interpreter::s_getFunctionParameters("add");
	BOOST_CHECK(functionTokens->size() == 3);
	BOOST_CHECK(functionParameter->size() == 2);
}
BOOST_AUTO_TEST_CASE(test_execute_function_parameters_basic) {
	std::string input = "func subtract(a,b) a-b";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	input = "subtract(6,2)";
	tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK( result.value() == std::to_string(4.0));
}
BOOST_AUTO_TEST_CASE(test_execute_function_parameters_advanced) {
	std::string input = "func subtract(a,b,c,d,e) a-b-c+d^e";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	input = "subtract(6,2,2,4,5)";
	tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(1026.0));
}
BOOST_AUTO_TEST_CASE(test_execute_multiple_function_parameters_advanced) {
	std::string input = "func subtract(a,b,c,d,e) a-b-c+d^e";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	input = "subtract(6,2,2,4,5) + subtract(6,2,2,4,5)";
	tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(2052.0));
}
BOOST_AUTO_TEST_CASE(test_execute_sub_function_parameters_advanced) {
	std::string input = "func subtract(a,b) add(a,b)";
	tokenizer tozr;
	parser parsr;
	interpreter interpr;
	auto tokenized = tozr.tokenize(input);
	input = "subtract(2,3) + subtract(2,3)";
	tokenized = tozr.tokenize(input);
	auto parsed = parsr.shunting_yard(*tokenized);
	auto result = interpr.solve(*parsed);
	BOOST_CHECK(result.value() == std::to_string(10.0));
}