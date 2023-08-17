
#include <includes.h>




std::unique_ptr<std::vector<token>> parser::shunting_yard(std::vector<token> & tokens){
	std::stack<token> op_stack;
	std::vector<token> output;

	for (int i = 0; i < tokens.size(); ++i) {

		if (tokens[i].type() == numerical || tokens[i].type() == identifier || tokens[i].type() == bqboolean) {
			output.push_back(tokens[i]);
			continue;
		}
		if (tokens[i].type() == function) {
			op_stack.push(tokens[i]);
		}
		if (tokens[i].isOperator() ) {
			while (!op_stack.empty() ) {
				if ( op_stack.top().type() != token_type::left && (op_stack.top().operatorPresidence() > tokens[i].operatorPresidence() || (op_stack.top().operatorPresidence() == tokens[i].operatorPresidence() && tokens[i].isLeftAssociated()))) {
					output.push_back(op_stack.top());
					op_stack.pop();
				}
				else {
					break;
				}
			}
			op_stack.push(tokens[i]);
		}
		if (tokens[i].type() == token_type::left) {
			op_stack.push(tokens[i]);
		}
		if (tokens[i].type() == token_type::right) {
			while (op_stack.top().type() != token_type::left) {
				output.push_back(op_stack.top());
				op_stack.pop();
			}
			op_stack.pop();

			if (!op_stack.empty()) {
				if (op_stack.top().type() == function) {
					output.push_back(op_stack.top());
					op_stack.pop();
				}
			} 
		}
	}
	while (!op_stack.empty()) {
		output.push_back(op_stack.top());
		op_stack.pop();
	}

	if (output.size() == 0) {
		output.push_back(token(NONE));
	}

	return std::make_unique<std::vector<token>>(output);
}

