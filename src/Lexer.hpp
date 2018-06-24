#pragma once

#include <fstream>
#include <cstdint>
#include <vector>

struct Token
{
	enum Type: uint8_t
	{
		Eof,
		BracketL,
		BracketR,
		IdenS, // Identifier (symbol)
		IdenL, // Identifier (letter)
		LitS, // Literal (String)
		LitI, // Literal (Integer)
		LitF, // Literal (Float)

		// Keywords
		KClass,
		KExtends,
		KReturn,
		KAssign,
		KNew,
		KPublic,
		KProtected,
		KPrivate,
		KVirtual,
		KFinal,
		
		Invalid
	};
	Type type_;

	std::string content_;

	Token(Type type): type_(type) {}
	Token(Type type, std::string content): type_(type), content_(content) {}
};

class Lexer
{
public:
	Lexer(std::string filename);

	std::string print() const;

	void readAll();

	std::vector<Token> const& get() { return tokens_; }
private:
	Token readToken();

	std::ifstream in_;
	std::vector<Token> tokens_;

	// Lexing state
	int last_;
};
