#include "Predicate.h"

Predicate::Predicate(vector<string>& predicateVect) {
	this->predicateVect = predicateVect;
}

Predicate::~Predicate()
{
}

string Predicate::toString() {
	for (unsigned int i = 0; i < predicateVect.size(); i++)
		ss << "  " << predicateVect.at(i) << endl;
	return ss.str();
}

int Predicate::vectSize() {
	return predicateVect.size();
}
