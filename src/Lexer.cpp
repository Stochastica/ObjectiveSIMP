#include "Lexer.hpp"

#include <cctype>
#include <exception>
#include <iostream>

Lexer::Lexer(std::string filename): in_(filename)
{
}

std::string Lexer::print() const
{
	std::string result;

#define CASE_CONENT(type, str) \
	case Token::type: result += "<" str ">"; break;
#define CASE_CONENT2(type, str) \
	case Token::type: result += "<" str " " + t.content_ + ">"; break;

	for (auto& t: tokens_)
	{
		switch (t.type_)
		{
		CASE_CONENT(Eof, "EOF")
		CASE_CONENT(BracketL, "(")
		CASE_CONENT(BracketR, ")")
		CASE_CONENT2(IdenS, "Iden 1")
		CASE_CONENT2(IdenL, "Iden 2")
		CASE_CONENT2(LitS, "string ")
		CASE_CONENT2(LitI, "int ")
		CASE_CONENT2(LitF, "float ")
		CASE_CONENT(KClass, "class")
		CASE_CONENT(KExtends, "extends")
		CASE_CONENT(KReturn, "return")
		CASE_CONENT(KAssign, ":=")
		CASE_CONENT(KNew, "new")
		CASE_CONENT(KPublic, "public")
		CASE_CONENT(KProtected, "protected")
		CASE_CONENT(KPrivate, "private")
		CASE_CONENT(KVirtual, "virtual")
		CASE_CONENT(KFinal, "final")
		CASE_CONENT(Invalid, "INVALID")
		}

		result += '\n';
	}

	return result;
}

void Lexer::readAll()
{
	in_.seekg(0, in_.beg);

	last_ = ' ';

	Token t = readToken();
	while (t.type_ != Token::Eof)
	{
		tokens_.push_back(t);
		t = readToken();

	}
	tokens_.push_back(t);
}

Token Lexer::readToken()
{
	// Skip all whitespaces
	if (last_ == EOF)
		return Token(Token::Eof);

	while (last_ != EOF && std::isspace(last_))
	{
		last_ = in_.get();
	}


	if (last_ == EOF)
		return Token(Token::Eof);



	// Detect keyword or identifier
	if (std::isalpha(last_))
	{ // Identifier-Keyword loop
		std::string content;
		
		content += (char) last_;
		
		last_ = in_.get();
		while (last_ != EOF && std::isalnum(last_))
		{
			content += last_;
			last_ = in_.get();
		}

		if (content == "class")
			return Token(Token::KClass);
		else if (content == "extends")
			return Token(Token::KExtends);
		else if (content == "return")
			return Token(Token::KReturn);
		else if (content == "new")
			return Token(Token::KNew);
		else if (content == "public")
			return Token(Token::KPublic);
		else if (content == "protected")
			return Token(Token::KProtected);
		else if (content == "private")
			return Token(Token::KPrivate);
		else if (content == "virtual")
			return Token(Token::KVirtual);
		else if (content == "final")
			return Token(Token::KFinal);

		return Token(Token::IdenL, content);
	}

	// Number
	if (std::isdigit(last_) || last_ == '.')
	{
		bool isFloat = last_ == '.';
		std::string content;
		do
		{
			isFloat = isFloat |= last_ == '.';
			content += (char) last_;
			last_ = in_.get();
		}
		while (EOF != last_ && (std::isdigit(last_) || last_ == '.'));

		return Token(isFloat ? Token::LitF : Token::LitI, content);
	}

	// String
	if (last_ == '"')
	{
		std::string content;
		last_ = in_.get();
		if (last_ == EOF)
			throw std::runtime_error("Malformed string");

		while (EOF != last_ && last_ != '"')
		{
			content += (char) last_;
			last_ = in_.get();
		}

		if (last_ == '"')
			last_ = in_.get();
		return Token(Token::LitS, content);
	}

	// Brackets
	if (last_ == '(')
	{
		last_ = in_.get();
		return Token(Token::BracketL);
	}
	if (last_ == ')')
	{
		last_ = in_.get();
		return Token(Token::BracketR);
	}

	// Symbol identifiers
	if (std::ispunct(last_))
	{
		std::string content;
		
		content += (char) last_;
		
		last_ = in_.get();
		while (last_ != EOF && std::ispunct(last_))
			content += last_;

		if (content == ":=")
			return Token(Token::KAssign);

		return Token(Token::IdenS, content);
	}
	

	// Comment
	if (last_ == '#')
	{
		do
		{
			last_ = in_.get();
		}
		while (EOF != last_ && last_ != '\n');

		if (EOF != last_)
			return readToken();
	}

	return Token(Token::Invalid);

}
