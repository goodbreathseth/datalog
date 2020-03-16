#ifndef PARAMETER_H
#define PARAMETER_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

class Parameter
{
public:
	Parameter(vector<string>& parameterVect);
	Parameter(string parameter);
	Parameter(const Parameter&);
	~Parameter();
	string toString();
	int vectSize();
	vector<string>& separateParameters();
	void setConstant(bool t);
	bool getConstant();
	void setParameter(string s);
	string getParameter();
	void setSeen();
	bool seen();
	void setKeep();
	bool keep();
	void setRename();
	bool rename();

private:
	vector<string> parameterVect;
	stringstream ss;
	stringstream parameterStream;
	vector<string> newParameterVect;
	string parameter;
	bool isConstant;
	bool isSeen;
	bool isKeep;
	bool isRename;
};

#endif