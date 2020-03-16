#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include "Interpreter.h"
#include "Header.h"

using namespace std;

class Parser {
public:
	Parser(vector<Token*>& tokenVect);
	void parse();
	void match(int tokenType);
	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	void headPredicate();
	void predicate();
	void predicateList();
	void parameterList();
	void stringList();
	void idList();
	void stringParameter();
	void idParameter();
	void expressionParameter();
	void expression();
	void Operator();

	void addToCorrespondingVector();


	enum TokenType {
		COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
		MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF_TYPE
	};
private:
	int index;
	vector<Token*> tokenVect;
	stringstream ss;
	stringstream domainString;
	vector<string> schemeVect;
	vector<string> factVect;
	vector<string> ruleVect;
	vector<string> queryVect;
	vector<string> domainVect;


	string notifier;
	vector<string> schemeNames;
	vector<Header> headerVect;
	vector<Relation> relationVect;
	set<string> factNames;
	vector<Tuple> tupleVect;
	int schemeCounter;
	

};

#endif