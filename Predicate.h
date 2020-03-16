#ifndef PREDICATE_H
#define PREDICATE_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Predicate
{
public:
	Predicate(vector<string>& predicateVect);
	~Predicate();
	string toString();
	int vectSize();

private:
	vector<string> predicateVect;
	stringstream ss;
};

#endif