#ifndef _LAXER_H_
#define _LAXER_H_
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<ctype.h>
#include"Exception.h"
#include"Token.h"
using std::vector;
using std::string;
using std::cout;
using std::endl;
class Lexer
{
private:
	vector<Token*> tokenList;
	string currentCode;
	char currentChar;
	int currentPosition;
	char nextChar;
	void jumpSpace();
	void shift();
	bool isRepeatPoint(const string& tempNum);
	bool isReservedWord(const string& tempWord);
	void isWord(vector<Token*>& currentTokenList,string& tempWord);
	void isNum(vector<Token*>& currentTokenList,string& tempNum);
	void isSymbol(vector<Token*>& currentTokenList,string &tempSymbol);
	void handleSymbolToken(const TokenKind symbolKind,vector<Token*>& currentTokenList,string &tempSymbol);
public:
	Lexer(){};
	void setCurrentCode(const string& currentCode);
	void getToken(vector<Token*>& currentTokenList);
	void run();
	vector<Token*> getTokenList(){return tokenList;}
	~Lexer();
};

#endif