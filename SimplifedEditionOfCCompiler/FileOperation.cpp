#include"FileOperation.h"
//int FileOperation::codeLine=0;
void FileOperation::lexerAnalysis(const string& currendCode)
{
	testLexer->setCurrentCode(currendCode);
	testLexer->run();
}

string FileOperation::returnTokenKindString(TokenKind tempKind)
{
	string tempString="";
	switch(tempKind)
	{
	case BAD:tempString="BAD";break;
	case RESERVED_WORD:tempString="RESERVED_WORD";break;
	case ID:tempString="ID";break;
	case NUM:tempString="NUM";break;
	case ADD:tempString="ADD";break;
	case SUB:tempString="SUB";break;
	case MULTIPLY:tempString="MULTIPLY";break;
	case DIVIDE:tempString="DIVIDE";break;
	case LEFT_ANGLE_BRACKETS:tempString="LEFT_ANGLE_BRACKETS";break;
	case RIGHT_ANGLE_BACKETS:tempString="RIGHT_ANGLE_BACKETS";break;
	case LEFT_BRACES:tempString="LEFT_BRACES";break;
	case RIGHT_BRACES:tempString="RIGHT_BRACES";break;
	case LEFT_PARENTHESIS:tempString="LEFT_PARENTHESIS";break;
	case RIGHT_PARENTHESIS:tempString="RIGHT_PARENTHESIS";break;
	case LEFT_SQUARE_BRACKETS:tempString="LEFT_SQUARE_BRACKETS";break;
	case RIGHT_SQUARE_BRACKETS:tempString="RIGHT_SQUARE_BRACKETS";break;
	case EQUEAL:tempString="EQUEAL";break;
	case END:tempString="END";break;
	case SHARP:tempString="SHARP";break;
	case NOT:tempString="NOT";break;
	case COMMA:tempString="COMMA";break;
	case DOUBLE_QUOTATION_MARKS:tempString="DOUBLE_QUOTATION_MARKS";break;
	case SINGLE_QUATATION_MARKS:tempString="SINGLE_QUATATION_MARKS";break;
	case COLON:tempString="COLON";break;
	case PERCERT:tempString="PERCERT";break;
	case QUESTION_MARK:tempString="QUESTION_MARK";break;
	case AND:tempString="AND";break;
	case AMPERSAND:tempString="AMPERSAND";break;
	case OR:tempString="OR";break;
	case BAR:tempString="BAR";break;
	case HEAD_FILE:tempString="HEAD_FILE";break;
	}
	return tempString;
}

FileOperation::FileOperation(const string& filePath)
{
	this->filePath=filePath;
	this->inFile.open(filePath);
	if(!inFile.is_open())
	{
		cerr<<Exception::FIlE_INPUT_EXCEPTION<<endl;
		exit(1);
	}
	//this->offsets=inFile.beg;
	this->testLexer=new Lexer();
}
string FileOperation::getFilePath()
{
	string filePath;
	cout<<"请输入文件路径:(e.g C:/test/test.c)"<<endl;
	cin>>filePath;
	return filePath;
}

string FileOperation::readLine()
{
	if(!inFile.is_open())
	{
		cerr<<Exception::FIlE_INPUT_EXCEPTION<<endl;
		exit(1);
	}
	while(getline(inFile,buffer))
	{
		Exception::codeLine++;
		lexerAnalysis(buffer);
		buffer="";
	}
	return buffer;
}
void FileOperation::output()
{
	using std::left;
	using std::setw;
	vector<Token*> tokenList=testLexer->getTokenList();
	TokenKind tempKind;
	cout<<left;
	cout<<"-----------------------------------------"<<endl;
	cout<<setw(23)<<"kind"<<setw(17)<<"|value"<<setw(2)<<"|"<<endl;
	cout<<"-----------------------|----------------|"<<endl;
	for(auto item:tokenList)
	{
		tempKind=item->getTokenKind();
		if(tempKind==NUM)
		{
			cout<<setw(23)<<returnTokenKindString(tempKind)<<"|";
			cout<<setw(16)<<static_cast<Number*>(item)->getValue()<<setw(2)<<"|"<<endl;
			cout<<"-----------------------|----------------|"<<endl;
		}
		else
		{
			cout<<setw(23)<<returnTokenKindString(tempKind)<<"|";
			cout<<setw(16)<<static_cast<Word*>(item)->getValue()<<setw(2)<<"|"<<endl;
			cout<<"-----------------------|----------------|"<<endl;
		}
	}
}

FileOperation::~FileOperation()
{
	delete testLexer;
}