#pragma once
class scanner {
public:
	std::unique_ptr<std::string> getNext();
	std::unique_ptr<std::vector<std::string>> readFile(std::string);
};