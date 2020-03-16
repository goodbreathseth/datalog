#include <iostream>
#include <string>
#include <sstream>
#include<vector>
#include "Token.h"
using namespace std;

Token::Token(int enumNumber, string str, int lineNumber) {
	enumNum = enumNumber;
	tokenString = str;
	lineNum = lineNumber;

	enumVect = {
		"COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
		"MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING",
		"COMMENT", "UNDEFINED", "EOF"
	};
}

int Token::getEnum() {
	return enumNum;
}

string Token::getString() {
	return tokenString;
}

string Token::toString() {
	ostringstream os;
	os << "(" << enumVect.at(enumNum) << ",\""
		<< tokenString << "\"," << lineNum << ")";
	return os.str();
}
