#include"Token.h"
//BaseClass
Token::Token()
{
	this->tokenKind=BAD;
}
void Token::setTokenKind(const TokenKind& myTokenKind)
{
	this->tokenKind=myTokenKind;
}
TokenKind Token::getTokenKind() const
{
	return this->tokenKind;
}

//SonClass:Number
Number::Number():Token()
{
}
void Number::setValue(double value)
{
	this->value=value;
}
double Number::getValue() const
{
	return this->value;
}

//SonClass:Word
Word::Word():Token()
{
}
void Word::setValue(const string& value)
{
	this->value=value;
}
string Word::getValue() const
{
	return this->value;
}