#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
using namespace std;

class DatalogProgram
{
public:
	DatalogProgram(Predicate& schemePred, Predicate& factPred, Rule& rulesObj,
		Predicate& queryPred);
	DatalogProgram(Predicate& schemePred, Predicate& factPred, Rule& rulesObj,
		Predicate& queryPred, Parameter& domainPara);
	~DatalogProgram();
	string toString();
	//Predicate& getSchemePred();

private:
	stringstream ss;
	vector<string> schemePred;
	//Predicate& schemePred;
	string schemes;
	int schemeSize;
	string facts;
	int factSize;
	string rules;
	int ruleSize;
	string queries;
	int querySize;
	string domain;
	int domainSize;
};

#endif