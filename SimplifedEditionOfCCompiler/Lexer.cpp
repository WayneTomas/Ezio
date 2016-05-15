#include"Lexer.h"
//Lexer::Lexer(const string& currentCode)
//{
//this->currentCode=currentCode;
//}
void Lexer::setCurrentCode(const string& currentCode)
{
	this->currentCode=currentCode;
	this->currentPosition=0;
	this->currentChar=currentCode[currentPosition];
}
void Lexer::jumpSpace()
{
	while (currentCode[currentPosition]!='\0')
	{
		if(currentCode[currentPosition]==' ')
		{
			currentPosition++;
			continue;
		}
		else
		{
			currentChar=currentCode[currentPosition];
			nextChar=currentCode[currentPosition+1];
			break;
		}
	}
}
void Lexer::shift()
{
	currentChar=nextChar;
	currentPosition++;
	if(nextChar!='\0')
	{
		nextChar=currentCode[currentPosition+1];
	}
}

bool Lexer::isRepeatPoint(const string& tempNum)
{
	int i=0;
	for(size_t j=0;j<tempNum.size();j++)
	{
		if(tempNum[j]=='.')
			i++;
	}
	if(i>1)
		return false;
	else
		return true;
}

bool Lexer::isReservedWord(const string& tempWord)
{
	static string ReservedWordTable[25]=
	{
		"if","else","for","return","while","do","switch","case","break","defalt"
		"char","const","double","float","int","long","short","struct","void",
		"inline","typedef","bool","true","false",
		"include","main"
	};
	vector<string> ReservedWordVector(ReservedWordTable,ReservedWordTable+25);
	if(std::find(ReservedWordVector.begin(),ReservedWordVector.end(),tempWord)!=ReservedWordVector.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Lexer::isWord(vector<Token*>& currentTokenList,string &tempWord)
{
	while(1)					//可能出错
	{
		//jumpSpace();
		if(isalpha(currentChar)||currentChar=='_'||isdigit(currentChar))
			tempWord+=currentChar;
		else if(currentChar=='.')
		{
			if(nextChar!='h'||currentCode[currentPosition+2]!='>')
			{
				cout<<Exception::INVALID_C_HEAD_FILE<<endl;
				cout<<"error line:"<<Exception::codeLine<<endl;
				cout<<"error code:"<<currentCode<<endl;
				system("pause");
				exit(1);
			}
			else
			{
				tempWord+=".h";
				Word *currentToken=new Word();
				currentToken->setTokenKind(HEAD_FILE);
				currentToken->setValue(tempWord);
				currentTokenList.push_back(currentToken);
				tempWord="";
				shift();
				shift();
				break;
			}
		}
		else
		{
			Word *currentToken=new Word();
			bool flag=isReservedWord(tempWord);
			if(flag)
			{
				currentToken->setTokenKind(RESERVED_WORD);
			}
			else
			{
				currentToken->setTokenKind(ID);
			}
			currentToken->setValue(tempWord);
			currentTokenList.push_back(currentToken);
			tempWord="";
			//delete currentToken;
			break;
		}
		shift();
	}
}
void Lexer::isNum(vector<Token*>& currentTokenList,string &tempNum)
{	
	while (1)
	{
		if(isdigit(currentChar)||currentChar=='.')		//因为之前在getToken()里经过else if(isdigital(currentChar))
		{												//的判断，所以currentChar=='.'实际上是从Num的第二个字符才开始作用的
			if(isRepeatPoint(tempNum))	//检测是否多个"."
			{
				tempNum+=currentChar;
			}
			else
			{
				cout<<Exception::REPEAT_DECIMAL_POINT<<endl;
				cout<<"error line:"<<Exception::codeLine<<endl;
				cout<<"error code:"<<currentCode<<endl;
				system("pause");
				exit(1);
			}
		}
		else
		{
			double value =atof(tempNum.c_str());
			Number *currentNumToken=new Number();
			currentNumToken->setTokenKind(NUM);
			currentNumToken->setValue(value);
			currentTokenList.push_back(currentNumToken);
			tempNum="";
			break;
		}
		shift();
	}
}

void Lexer::handleSymbolToken(const TokenKind symbolKind,vector<Token*>& currentTokenList,string &tempSymbol)
{
	Word* currentSymbolToken=new Word();
	currentSymbolToken->setTokenKind(symbolKind);
	currentSymbolToken->setValue(tempSymbol);
	currentTokenList.push_back(currentSymbolToken);
	tempSymbol="";
	shift();
}

void Lexer::isSymbol(vector<Token*>& currentTokenList,string &tempSymbol)
{
	switch(currentChar)
	{
	case '+':tempSymbol+="+";handleSymbolToken(ADD,currentTokenList,tempSymbol);break;
	case '-':tempSymbol+="-";handleSymbolToken(SUB,currentTokenList,tempSymbol);break;
	case '*':tempSymbol+="*";handleSymbolToken(MULTIPLY,currentTokenList,tempSymbol);break;
	case '/':tempSymbol+="/";handleSymbolToken(DIVIDE,currentTokenList,tempSymbol);break;
	case '<':tempSymbol+="<";handleSymbolToken(LEFT_ANGLE_BRACKETS,currentTokenList,tempSymbol);break;
	case '>':tempSymbol+=">";handleSymbolToken(RIGHT_ANGLE_BACKETS,currentTokenList,tempSymbol);break;
	case '{':tempSymbol+="{";handleSymbolToken(LEFT_BRACES,currentTokenList,tempSymbol);break;
	case '}':tempSymbol+="}";handleSymbolToken(RIGHT_BRACES,currentTokenList,tempSymbol);break;
	case '(':tempSymbol+="(";handleSymbolToken(LEFT_PARENTHESIS,currentTokenList,tempSymbol);break;
	case ')':tempSymbol+=")";handleSymbolToken(RIGHT_PARENTHESIS,currentTokenList,tempSymbol);break;
	case '[':tempSymbol+="[";handleSymbolToken(LEFT_SQUARE_BRACKETS,currentTokenList,tempSymbol);break;
	case ']':tempSymbol+="]";handleSymbolToken(RIGHT_ANGLE_BACKETS,currentTokenList,tempSymbol);break;
	case '#':tempSymbol+="#";handleSymbolToken(SHARP,currentTokenList,tempSymbol);break;
	case '=':tempSymbol+="=";handleSymbolToken(EQUEAL,currentTokenList,tempSymbol);break;
	case ',':tempSymbol+=",";handleSymbolToken(COMMA,currentTokenList,tempSymbol);break;
	case ';':tempSymbol+=";";handleSymbolToken(END,currentTokenList,tempSymbol);break;
	case '\"':tempSymbol+="\"";handleSymbolToken(DOUBLE_QUOTATION_MARKS,currentTokenList,tempSymbol);break;
	case '\'':tempSymbol+="\'";handleSymbolToken(SINGLE_QUATATION_MARKS,currentTokenList,tempSymbol);break;
	case ':':tempSymbol+=":";handleSymbolToken(COLON,currentTokenList,tempSymbol);break;
	case '%':tempSymbol+="%";handleSymbolToken(PERCERT,currentTokenList,tempSymbol);break;
	case '?':tempSymbol+="?";handleSymbolToken(QUESTION_MARK,currentTokenList,tempSymbol);break;
	case '&':if(nextChar=='&')
			 {
				tempSymbol+="&&";
				handleSymbolToken(AND,currentTokenList,tempSymbol);
				shift();
			 }
			 else
			 {
				 tempSymbol+="&";
				 handleSymbolToken(AMPERSAND,currentTokenList,tempSymbol);
			 }
			break;
	case '|':if(nextChar=='|')
			 {
				 tempSymbol+="||";
				 handleSymbolToken(OR,currentTokenList,tempSymbol);
				 shift();
			 }
			 else
			 {
				 tempSymbol+="|";
				 handleSymbolToken(BAR,currentTokenList,tempSymbol);
			 }
	default:cout<<Exception::INVALID_SYMBOL<<endl;
			cout<<"error line:"<<Exception::codeLine<<endl;
			cout<<"error code:"<<currentCode<<endl;
			system("pause");
			exit(1);break;
	}
}

void Lexer::getToken(vector<Token*>& currentTokenList)
{
	string temp="";
	while(currentChar!='\0')
	{
		jumpSpace();
		if(isalpha(currentChar)||currentChar=='_')
		{
			isWord(currentTokenList,temp);
		}
		else if(isdigit(currentChar))
		{
			isNum(currentTokenList,temp);
		}
		else
		{
			isSymbol(currentTokenList,temp);
		}
	}
}
void Lexer::run()
{
	getToken(tokenList);
}
Lexer::~Lexer()
{
	for(vector<Token*>::iterator item=tokenList.begin();item!=tokenList.end();item++)
	{
		if(NULL!=*item)
		{
			delete *item;
			*item=NULL;
		}
	}
	tokenList.clear();
}