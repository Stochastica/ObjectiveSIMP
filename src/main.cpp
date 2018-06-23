#include <iostream>

#include "Options.hpp"

int main(int argc, char* argv[])
{
	OptionParser options;

	options
		.addArg("-o", 1, "Directory of output file")
		.addArg("-s", 1, "Execution stage")
		.addArg("--help", 0, "Display help");

	options.parse(argc, argv);

	if (options.count("--help"))
	{
		std::cerr << options.help();
		return 0;
	}
	std::cout << options.state();
	return 0;
}
