#include <iostream>

#include "Options.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

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

	// Execute by stage
	if (options.count("-s"))
	{
		// Lexer stage
		if (options.optionValues("-s")[0] == "1")
		{
			std::string filename = options.optionValues("")[0];
			Lexer lex(filename);
			lex.readAll();

			std::cerr << lex.print();
		}
	}
	else
	{
		std::cout << options.state();
	}
	return 0;
}
