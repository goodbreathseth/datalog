#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
using namespace std;

class Token {
public:
	Token(int enumNumber, string str, int lineNumber);
	enum TokenType {
		COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
		MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF_TYPE
	};
	int getEnum();
	string getString();
	string toString();

private:
	int enumNum;
	string tokenString;
	int lineNum; 
	char *enumTypes;
	vector<string> enumVect;

};

#endif