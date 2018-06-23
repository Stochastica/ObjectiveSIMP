#pragma once

#include <string>
#include <map>
#include <vector>

struct Option
{
	Option() : nargs_(0), count_(-1) {}
	Option(int nargs, std::string help) : nargs_(nargs), help_(help), count_(0) {}

	/*
	 * Special value -1 marks infinitely many arguments. Only the "" option can
	 * have this.
	 */
	int nargs_;
	std::string help_;


	/*
	 * Populated by the parser
	 */
	int count_;
	std::vector<std::string> vals_;
};

/*
 * This parser is suitable for compilers.
 */
class OptionParser
{
public:
	typedef std::string Key;

	OptionParser();

	OptionParser& addArg(Key name, int nargs = 0, std::string help = "");

	void parse(int argc, char* argv[]);

	/**
	 * Querying information
	 */
	int count(Key const&);
	std::vector<std::string> const& optionValues(Key const&);

	std::string help() const;
	std::string state() const;
private:
	void readArgs(Key key, int* i, int argc, char* argv[]); 

	std::map<Key, Option> optmap_;
};
