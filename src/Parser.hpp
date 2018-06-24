#pragma once

#include <fstream>

namespace syn
{
	class Node;
};

class Parser
{
public:
	Parser(std::string filename);

	syn::Node* exec();
private:
	std::ifstream file_;
};
