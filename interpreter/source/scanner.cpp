
#include <includes.h>

std::unique_ptr<std::vector<std::string>> scanner::readFile(std::string file) {
	std::unique_ptr<std::vector<std::string>> lines = std::make_unique<std::vector<std::string>>();

	std::string line;

	std::ifstream ifs(file);

	while (ifs >> line) {
		lines->push_back(line);
	}
	return lines;
}

std::unique_ptr<std::string> scanner::getNext() {
	std::cout << ">";
	std::string input;
	std::getline(std::cin, input);
	return std::make_unique<std::string>(input);
}