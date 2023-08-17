#include <includes.h>



token::token() {

}

token::token(token_type type, std::string value): m_tokenType(type),  m_value(value) {

	if (type == addition || type == subtraction || type == division || type == multiplication || type == power || type==set || type==equals || type==IF || type==then || type == ELSE || type==set) {
		m_isOperator = true;
	}
	else {
		m_isOperator = false;
	}

	if (type == power) {
		m_operatorPresidence = 4;
		m_leftAssosiative = false;
	}
	else if (type == multiplication) {
		m_operatorPresidence = 3;
		m_leftAssosiative = true;
	}
	else if (type == division) {
		m_operatorPresidence = 3;
		m_leftAssosiative = true;
	}
	else if (type == addition) {
		m_operatorPresidence = 2;
		m_leftAssosiative = true;
	}
	else if (type == subtraction) {
		m_operatorPresidence = 2;
		m_leftAssosiative = true;
	}
	else if (type == set) {
		m_operatorPresidence = -1;
		m_leftAssosiative = false;
	}
	else if (type == equals) {
		m_operatorPresidence = 0;
		m_leftAssosiative = false;
	}
	else if (type == IF) {
		m_operatorPresidence = 666666666666666666;
		m_leftAssosiative = false;
	}
	else if (type == then) {
		m_operatorPresidence = 0;
		m_leftAssosiative = false;
	}
	else if (type == ELSE) {
		m_operatorPresidence = 0;
		m_leftAssosiative = false;
	}
	else {
		m_operatorPresidence = 1;
		m_leftAssosiative = false;
	}
}

std::string token::typeToString() {
	switch (m_tokenType) {
		case token_type::addition:		return "addition"; break;
		case token_type::subtraction:	return "subtraction"; break;
		case token_type::division:		return "division"; break;
		case token_type::equals:		return "equals"; break;
		case token_type::identifier:	return "identifier"; break;
		case token_type::multiplication:return "multiplication"; break;
		case token_type::set:			return "set"; break;
		case token_type::numerical:		return "numerical"; break;
		case token_type::left:			return "left"; break;
		case token_type::right:			return "right"; break;
		case token_type::power:			return "power"; break;
		case token_type::function:		return "function"; break;
		case token_type::bqboolean:		return "boolean"; break;
		case token_type::NONE:		return "none"; break;
		case token_type::then:		return "then"; break;
		case token_type::IF:		return "if"; break;
		case token_type::ELSE :		return "else"; break;
		default:						return "unknown"; break;
	}
}
token_type token::type() {
	return m_tokenType;
}
std::string token::value() {
	return m_value;
}
bool token::isOperator() {
	return m_isOperator;
}
int token::operatorPresidence() {
	return m_operatorPresidence;
}
bool token::isLeftAssociated() {
	return m_leftAssosiative;
}