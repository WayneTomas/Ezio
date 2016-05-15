#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include<string>
using std::string;
class Exception
{
public:
	static int codeLine;
	static const string FIlE_INPUT_EXCEPTION;
	static const string REPEAT_DECIMAL_POINT;
	static const string INVALID_SYMBOL;
	static const string INVALID_C_HEAD_FILE;
};

#endif