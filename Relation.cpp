#include "Relation.h"


Relation::Relation(string name, Header & header) {
	relationName = name;
	this->header = header;
}

Relation::~Relation()
{
}

void Relation::addTuple(Tuple & newTuple) {
	tuples.insert(newTuple);
}

string Relation::getName() {
	return relationName;
}

int Relation::getSizeOfParameters() {
	return header.size();
}

string Relation::toString(unsigned int j) {
	stringstream ss;
	for (set<Tuple>::iterator it = tuples.begin(); it != tuples.end(); ++it) {
		for (unsigned int i = 0; i < it->size(); i++) {
			if (i == j)
				ss << it->at(i) << endl;
		}
	}
	return ss.str();
}

set<Tuple>& Relation::getSetOfTuples() {
	return tuples;
}

Header & Relation::getHeader() {
	return header;
}
