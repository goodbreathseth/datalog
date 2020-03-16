#ifndef RULE_H
#define RULE_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Rule
{
public:
	Rule(vector<string>& ruleVect);
	~Rule();
	string toString();
	int vectSize();

private:
	vector<string> ruleVect;
	stringstream ss;
};

#endif