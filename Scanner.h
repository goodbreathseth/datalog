#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Token.h"

using namespace std;

class Scanner {
public:
	Scanner();
	Scanner(string fileName);
	vector<Token*>& tokenize();
	void caseS();
	void caseF();
	void caseR();
	void caseQ();
	void compareStrings(string testStr);
	void checkIfID();
	void caseString();
	void caseComment();
	void incrementLine();
	void createStringCommentToken(int enumNum);
	void createEOFtoken();

private:
	string file;
	ifstream in;
	vector<Token*> tokens;
	int enumNum;
	string tokenString;
	int beginningOfStringLine;
	int lineNum;
	char next;
	stringstream ss;
	string testStr;
	bool match;
	int lengthOfStrEvaluated;

};

#endif