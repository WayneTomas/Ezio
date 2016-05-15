#include"FileOperation.h"
#include"Token.h"
#include"Lexer.h"
using std::cout;
using std::cin;

int main(int argc,char* argv[])
{
	string filePath="";
	if(argc==1)
	{
		filePath=FileOperation::getFilePath();
	}
	else
	{
		filePath=argv[1];
	}
	FileOperation *fileOperation = new FileOperation(filePath);
	fileOperation->readLine();
	fileOperation->output();
	delete fileOperation;
	system("pause");
	return 0;
}