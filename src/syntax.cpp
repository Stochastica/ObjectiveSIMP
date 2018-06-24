#include "syntax.hpp"

namespace syn
{

Program::~Program()
{
	for (auto& e : elem_)
		delete e;
}

} // namespace syn
