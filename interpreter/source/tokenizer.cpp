


#include <includes.h>

std::vector<std::string> RESERVED_KEYWORDS = {"max","print"};

void tokenizer::checkIfBuilt(bool& building_id, bool& building_value, std::vector<token>* tokens, std::string& identifier, std::string& number) {
	
	if (identifier == "func") {
		m_buildingFunction = true;
		identifier = "";
	}
	else {
		if (building_id) {
			if (std::find(RESERVED_KEYWORDS.begin(), RESERVED_KEYWORDS.end(), identifier) != RESERVED_KEYWORDS.end() || interpreter::s_funcExists(identifier))
			{
				building_id = false;
				tokens->push_back(token(token_type::function, identifier));
				identifier = "";
			}
			else if (identifier == "true") {
				building_id = false;
				tokens->push_back(token(token_type::bqboolean, "true"));
				identifier = "";
			}
			else if (identifier == "false") {
				building_id = false;
				tokens->push_back(token(token_type::bqboolean, "false"));
				identifier = "";
			}
			else if (identifier == "if") {
				building_id = false;
				tokens->push_back(token(token_type::IF, ""));
				identifier = "";
			}
			else if (identifier == "then") {
				building_id = false;
				tokens->push_back(token(token_type::then, ""));
				identifier = "";
			}
			else if (identifier == "else") {
				building_id = false;
				tokens->push_back(token(token_type::ELSE, ""));
				identifier = "";
			}
			else {
				building_id = false;
				tokens->push_back(token(token_type::identifier, identifier));
				identifier = "";
			}
		}
		if (building_value) {
			building_value = false;
			tokens->push_back(token(token_type::numerical, std::to_string(std::stod(number))));
			number = "";
		}
	}
	
}

std::unique_ptr<std::vector<token>> tokenizer::tokenize(std::string& input) {
	std::unique_ptr<std::vector<token>> tokens = std::make_unique<std::vector<token>>();
	
	std::string identifier = "";
	bool building_id = false;
	bool building_value = false;
	std::string number = "";

	bool flagEqualsCheck = false;
	
	for (auto& c : input) {

		if (m_buildingFunction) {

		}

		if (flagEqualsCheck) {
			flagEqualsCheck = false;
			if (c == '=') {
				tokens->push_back(token(equals));
				continue;
			}
			else {
				tokens->push_back(token(set));
			}
		}

		if (c == '+') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			tokens->push_back(token(addition));
		}
		else if (c == '-') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			tokens->push_back(token(subtraction));
		}
		else if (c == '*') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			tokens->push_back(token(multiplication));
		}
		else if (c == '/') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			tokens->push_back(token(division));
		}
		else if (c == '^') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			tokens->push_back(token(power));
		}
		else if (c == '(') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			tokens->push_back(token(left));
		}
		else if (c == ')') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			tokens->push_back(token(right));
		}
		else if (c == '=') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
			flagEqualsCheck = true;
		}
		else if (c >= 'a' && c <= 'z') {
			identifier.push_back(c);
			building_id = true;
		}
		else if (c >= 'A' && c <= 'Z') {
			identifier.push_back(c);
			building_id = true;
		}
		else if (c >= '0' && c <= '9') {
			number.push_back(c);
			building_value = true;
		}
		else if (c == ',') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
		}
		else if (c == ' ') {
			checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);
		}
	}
	if (flagEqualsCheck) {
		tokens->push_back(token(set));
	}
	checkIfBuilt(building_id, building_value, tokens.get(), identifier, number);

	//if we were building a function, we're going to store it for later instead of using the code now.
	if (m_buildingFunction) {
		std::string funcName = tokens->at(0).value();

		m_buildingFunction = false;

		tokens->erase(tokens->begin());
		std::vector<std::string> variables;
		std::string current_variable = "";
		for (auto it = (*tokens).begin(); it != (*tokens).end(); /* NOTHING */)
		{
			if ((*it).type() == left) {
				it = (tokens)->erase(it);
			}
				
			else if ((*it).type() == right) {
				it = (tokens)->erase(it);
				break;
			}
			else {
				variables.push_back((*it).value());
				it = (tokens)->erase(it);
			}
		}
		interpreter::s_addFunction(funcName, tokens.get(),variables);
		tokens->erase(tokens->begin(), tokens->end());
		
	}
	return std::move(tokens);
}