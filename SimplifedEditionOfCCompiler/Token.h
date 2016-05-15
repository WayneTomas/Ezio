#ifndef _TOKEN_H_
#define _TOKEN_H_
#include<iostream>
#include<string>
#include<vector>
using std::string;

enum TokenKind
{
	BAD,RESERVED_WORD,ID,NUM,ADD,SUB,MULTIPLY,DIVIDE,LEFT_ANGLE_BRACKETS,RIGHT_ANGLE_BACKETS,
	LEFT_BRACES,RIGHT_BRACES,LEFT_PARENTHESIS,RIGHT_PARENTHESIS,LEFT_SQUARE_BRACKETS,RIGHT_SQUARE_BRACKETS,
	EQUEAL,END,SHARP,NOT,AND,OR,COMMA,AMPERSAND,BAR,
	DOUBLE_QUOTATION_MARKS,SINGLE_QUATATION_MARKS,COLON,PERCERT,QUESTION_MARK,
	HEAD_FILE
};

class Token
{
protected:
	TokenKind tokenKind;
public:
	Token();
	void setTokenKind(const TokenKind& myTokenKind);
	TokenKind getTokenKind() const;
};
class Number:public Token
{
private:
	double value;
public:
	Number();
	void setValue(double value);
	double getValue() const;
};
class Word:public Token
{
private:
	string value;
public:
	Word();
	void setValue(const string& value);
	string getValue() const;
};
#endif