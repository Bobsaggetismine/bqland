#pragma once

#include <iostream>

enum token_type {
	identifier,
	subtraction, 
	addition, 
	multiplication,
	division,
	equals,
	set,
	bqboolean, 
	numerical,
	left,
	right,
	power,
	IF,
	then,
	function,
	ELSE,
	NONE
};
class token {
	
	token_type m_tokenType;
	std::string m_value;
	bool m_isOperator;
	int m_operatorPresidence;
	bool m_leftAssosiative;
public:
	token(token_type, std::string value="0");
	token();
	std::string typeToString();
	std::string value();
	token_type type();
	bool isOperator();
	int operatorPresidence();
	bool isLeftAssociated();

	static void printTokens(std::vector<token>* tokens) {
		for (auto& token : *tokens) {
			std::cout << token.typeToString() << " : " << token.value() << std::endl;
		}
	}
};