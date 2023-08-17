#pragma once


class parser {
public:
	std::unique_ptr<std::vector<token>> shunting_yard(std::vector<token> &);
};