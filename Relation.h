#ifndef RELATION_H
#define RELATION_H
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include "Tuple.h"
#include "Header.h"
using namespace std;

class Relation
{
public:
	Relation(string name, Header& header);
	Relation() {};
	~Relation();
	void addTuple(Tuple& newTuple);
	string getName();
	int getSizeOfParameters();
	string toString(unsigned int j);
	set<Tuple>& getSetOfTuples();
	Header& getHeader();
private:
	string relationName;
	Header header;
	set<Tuple> tuples;
};

#endif