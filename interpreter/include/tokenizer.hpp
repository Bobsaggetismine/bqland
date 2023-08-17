#pragma once

class tokenizer {
	bool m_buildingFunction = false;
public:
	std::unique_ptr<std::vector<token>> tokenize(std::string& input);
	void checkIfBuilt(bool& building_id, bool& building_value, std::vector<token>* tokens, std::string& identifier, std::string& number);
};