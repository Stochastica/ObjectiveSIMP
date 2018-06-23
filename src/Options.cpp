#include "Options.hpp"

#include <cassert>
#include <iostream>

OptionParser::OptionParser()
{
	optmap_[""] = Option(-1, "");
}

OptionParser&
OptionParser::addArg(std::string name, int nargs, std::string help)
{
	optmap_[name] = Option(nargs, help);
	return *this;
}

void OptionParser::parse(int argc, char* argv[])
{
	// argv[0] is not an option.
	--argc; ++argv;

	for (int i = 0; i < argc;)
	{
		std::string arg(argv[i]);

		if (optmap_.count(arg))
		{
			optmap_[arg].count_ += 1;
			++i;
			readArgs(arg, &i, argc, argv);
		}
		else if (arg == "--")
		{
			// Read all args.
			++i;
			optmap_[""].count_ = 1;
			readArgs("", &i, argc - i, argv);
		}
		else
		{
			optmap_[""].count_ = 1;
			optmap_[""].vals_.push_back(arg);
			++i;
		}
	}
}

int OptionParser::count(Key const& key)
{
	assert(optmap_.count(key));

	return optmap_[key].count_;
}
std::vector<std::string> const&
OptionParser::optionValues(Key const& key)
{
	assert(optmap_.count(key));

	return optmap_[key].vals_;
}

void OptionParser::readArgs(Key key, int* i, int argc, char* argv[])
{
	int const nargs = optmap_[key].nargs_;
	if (nargs < 0)
	{
		for (; *i < argc; ++*i)
		{
			optmap_[key].vals_.push_back(argv[*i]);
		}
	}
	else
	{
		for (int j = 0; j < nargs; ++j)
		{
			assert(j + *i < argc);
			optmap_[key].vals_.push_back(argv[j + *i]);
		}
		*i += nargs;
	}
}

std::string OptionParser::help() const
{
	std::string result;

	result = "Command line options:\n";
	for (auto& kv : optmap_)
	{
		if (kv.first == "")
			continue;

		result += kv.first + ": " + kv.second.help_ + '\n';
	}
	return result;
}
std::string OptionParser::state() const
{
	std::string result = "Options\n";

	for (auto& kv : optmap_)
	{
		result += kv.first + " " + std::to_string(kv.second.count_) + ": [";
		bool flag = true;
		for (auto& str : kv.second.vals_)
		{
			if (!flag)
				result += ", ";
			result += str;
			flag = false;
		}
		result += "]\n";
	}

	return result;
}
