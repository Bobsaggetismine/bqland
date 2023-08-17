


#include <includes.h>


std::map<std::string, double> interpreter::s_numberVariables;
std::map<std::string, bool> interpreter::s_booleanVariables;
std::map<const std::string, std::unique_ptr<std::vector<token>>> interpreter::s_functions;
std::map<const std::string, std::unique_ptr<std::vector<std::string>>> interpreter::s_functionParameters;




token interpreter::performArtithmaticOperation(token& operand1, token& operand2, std::function<double(double, double)> fn) {
	double value1 = std::stod(valueFromToken(operand1));
	double value2 = std::stod(valueFromToken(operand2));
	return token(numerical, std::to_string(fn(value2, value1)));
}

std::string interpreter::valueFromToken(token& token)
{
	std::string value;
	if (token.type() == identifier) {
		if (s_numberVariables.find(token.value()) != s_numberVariables.end()) value = std::to_string(s_numberVariables[token.value()]);
		if (s_booleanVariables.find(token.value()) != s_booleanVariables.end()) value = std::to_string(s_booleanVariables[token.value()]);

	}
	else if (token.type() == bqboolean) value = token.value();
	else if (token.type() == numerical) value = std::to_string(std::stod(token.value()));
	return value;
}


std::ostream& operator<<(std::ostream& os, std::stack<token> my_stack) //function header
{
	while (!my_stack.empty()) //body
	{
		os <<my_stack.top().typeToString() << " : " << my_stack.top().value() << " ";
		my_stack.pop();
	}
	return os; // end of function
}

token interpreter::solve(std::vector<token>& tokens) {
	std::stack<token> workingStack;
	std::stack<token> workingStackPreserve;
	bool thenFlag = false;
	bool elseFlag = false;

	for (auto tok : tokens) {

		if (tok.type() == token_type::numerical || tok.type() == identifier || tok.type() == bqboolean || tok.type() == NONE) workingStack.push(tok);

		else if (tok.type() == subtraction || tok.type() == addition || tok.type() == division || tok.type() == multiplication || tok.type() == power) {
			token operand1 = workingStack.top();
			workingStack.pop();
			token operand2 = workingStack.top();
			workingStack.pop();
			std::function<double(double, double)> fn;
			switch (tok.type()) {
			case subtraction:	 fn = [](double x, double y) { return x - y; }; break;
			case addition:		 fn = [](double x, double y) { return x + y; }; break;
			case division:		 fn = [](double x, double y) { return x / y; }; break;
			case multiplication: fn = [](double x, double y) { return x * y; }; break;
			case power:          fn = [](double x, double y) { return std::pow(x, y); }; break;
			}
			workingStack.push(performArtithmaticOperation(operand1, operand2, fn));
		}
		else if (tok.type() == set) {

			token operand1 = workingStack.top();
			workingStack.pop();
			token operand2 = workingStack.top();
			workingStack.pop();
			workingStack.push(operand1);

			if (operand1.type() == numerical) {
				s_numberVariables[operand2.value()] = std::stod(operand1.value());
			}
			else if (operand1.type() == bqboolean) {

				if (operand1.value() == "true") {
					s_booleanVariables[operand2.value()] = true;
				}
				else if (operand1.value() == "false") {
					s_booleanVariables[operand2.value()] = false;
				}
			}
		}
		else if (tok.type() == equals) {
			token operand1 = workingStack.top();
			workingStack.pop();
			token operand2 = workingStack.top();
			workingStack.pop();
			std::string value1 = valueFromToken(operand1);
			std::string value2 = valueFromToken(operand2);

			if (value1 == value2) {
				workingStack.push(token(bqboolean, "true"));
			}
			else {
				workingStack.push(token(bqboolean, "false"));
			}

		}
		else if (tok.type() == IF) {
			std::string value = workingStack.top().value();
			workingStack.pop();
			if (value == "true") {
				thenFlag = true;

			}
			else if (value == "false") {
				elseFlag = true;
			}
			workingStackPreserve = workingStack;
			while (!workingStack.empty()) {
				workingStack.pop();
			}
		}
		else if (tok.type() == then){
				std::vector<token> thenTokens;
				for (int i = 0; i < workingStack.size();) {
					thenTokens.push_back(workingStack.top());
					workingStack.pop();
				}
				if (thenFlag) {
					auto t = solve(thenTokens);
					workingStack.push(t);
				}
				
		}
		else if (tok.type() == ELSE) {
			std::vector<token> thenTokens;
			for (int i = 0; i < workingStack.size() - thenFlag;) {
				thenTokens.push_back(workingStack.top());
				workingStack.pop();
			}
			if (elseFlag) {
				auto t = solve(thenTokens);
				workingStack.push(t);
				elseFlag = false;
			}
			thenFlag = false;

			//reverseStack<token>(workingStackPreserve);
			
			while (!workingStack.empty()) {
				workingStackPreserve.push(workingStack.top());
				workingStack.pop();
			}
			workingStack = workingStackPreserve;
			while (!workingStackPreserve.empty()) {
				workingStackPreserve.pop();
			}
			
		}
		else if (tok.type() == function) {
			if (tok.value() == "max") {
				token operand1 = workingStack.top();
				workingStack.pop();
				token operand2 = workingStack.top();
				workingStack.pop();

				double value1 = std::stod(valueFromToken(operand1));
				double value2 = std::stod(valueFromToken(operand2));

				if (value1 > value2) workingStack.push(operand1);
				else workingStack.push(operand2);

				//s_numberVariables[operand2.value()] = std::stod(operand1.value()); 
			}
			else if (tok.value() == "print") {
				token operand = workingStack.top();
				if (operand.type() == identifier) {

					if (s_numberVariables.find(operand.value()) != s_numberVariables.end()) std::cout << s_numberVariables[operand.value()] << std::endl;
					else if (s_booleanVariables.find(operand.value()) != s_booleanVariables.end()) {
						bool result = s_booleanVariables[operand.value()];
						if (result) std::cout << "true" << std::endl;
						else		std::cout << "false" << std::endl;

					}
				}
				else  std::cout << operand.value() << std::endl;
			}
			else {
				if (s_functions.find(tok.value()) != s_functions.end()) {
					auto parsed = s_functions[tok.value()].get();

					auto funcArgs = s_functionParameters[tok.value()].get();
					std::vector<token> pulled;
					for (int i = 0; i < funcArgs->size(); ++i) {
						pulled.push_back(workingStack.top());
						workingStack.pop();
					}
					std::reverse(pulled.begin(), pulled.end());
					for (int i = 0; i < funcArgs->size(); ++i) {
						for (int y = 0; y < parsed->size(); ++y) {
							if (parsed->at(y).value() == funcArgs->at(i)) {
								parsed->at(y) = token(numerical, pulled[i].value());
							}
						}
					}


					token result = solve(*parsed);
					workingStack.push(result);
				}
			}
		}
	}
	return workingStack.top();
}