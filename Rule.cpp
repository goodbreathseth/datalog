#include "Rule.h"

Rule::Rule(vector<string>& ruleVect) {
	this->ruleVect = ruleVect;

}

Rule::~Rule()
{
}

string Rule::toString() {
	for (unsigned int i = 0; i < ruleVect.size(); i++)
		ss << "  " << ruleVect.at(i) << endl;
	return ss.str();
}

int Rule::vectSize() {
	return ruleVect.size();
}
