#pragma once

#include <string>
#include <vector>

namespace syn
{

class Node
{
public:
	virtual ~Node() = default;
};

class Program final: public Node
{
public:
	~Program() override;

	std::vector<Node*> elem_;
};

} // namespace syn
