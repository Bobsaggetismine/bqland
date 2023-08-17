#pragma once

#include <stack>

class interpreter {
public:
	token solve(std::vector<token>& tokens);


	template <class Type>
	static void reverseStack(std::stack<Type>& stack)
	{
		Type item;
		std::stack<Type> tmpStack;

		while (stack.empty() == false)
		{
			item = stack.top();
			stack.pop();
			tmpStack.push(item);
		}

		//while (tmpStack.isEmptyStack() == false)
		//{
		//   item = tmpStack.top();
		//   tmpStack.pop();
		//   stack.push(item);
		//   cout << item;
		//}

		stack = tmpStack;
		return;
	}







	//tokens should be passed PRE-PARSED
	static void s_addFunction(const std::string& name, std::vector<token>* funcTokens, std::vector<std::string>& variables) {
		parser parsr;
		auto parsed = parsr.shunting_yard(*funcTokens);
		s_functions[name]          = std::move(parsed);
		s_functionParameters[name] = std::make_unique<std::vector<std::string>>(variables);
	}
	static std::vector<token>* s_getFunction(const std::string& name) {
		return s_functions[name].get();
	}
	static bool s_funcExists(const std::string& func) {
		return (s_functions.find(func) != s_functions.end());
	}
	static std::vector<std::string>* s_getFunctionParameters(const std::string& func) {
		return s_functionParameters[func].get();
	}
private:

	static std::map<std::string, double> s_numberVariables;
	static std::map<std::string, bool>   s_booleanVariables;
	static std::map<const std::string, std::unique_ptr<std::vector <token>>> s_functions;
	static std::map<const std::string, std::unique_ptr<std::vector <std::string>>> s_functionParameters;
	token performArtithmaticOperation(token& operand1, token& operand2, std::function<double(double, double)> fn);
	std::string valueFromToken(token& token);
};