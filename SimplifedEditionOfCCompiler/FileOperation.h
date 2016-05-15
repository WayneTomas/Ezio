#ifndef _FILEOPERATION_H_
#define _FILEOPERATION_H_
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include"Exception.h"
#include"Lexer.h"
using std::string;
using std::ifstream;
using std::cerr;
using std::endl;
using std::cout;
using std::cin;
using std::streamoff;

class FileOperation
{
private:
	//static int codeLine;
	string filePath;
	ifstream inFile;
	string buffer;
	Lexer *testLexer;
private:
	void lexerAnalysis(const string& currendCode);
	string returnTokenKindString(TokenKind tempKind);
public:
	FileOperation() {};
	FileOperation(const string& filePath);
	//static function
	static string getFilePath();

	string readLine();
	void output();
	~FileOperation();
};
#endif