#include "Parameter.h"

Parameter::Parameter(vector<string>& parameterVect) {
	this->parameterVect = parameterVect;
	separateParameters();
}

Parameter::Parameter(const Parameter &)
{
}

Parameter::Parameter(string p) {
	parameter = p;
	isSeen = false;
	isKeep = false;
	isRename = false;
}

Parameter::~Parameter()
{
}

string Parameter::toString() {
	ss.str("");
	for (unsigned int i = 0; i < newParameterVect.size(); i++)
		ss << "  " << newParameterVect.at(i) << endl;
	return ss.str();
}

int Parameter::vectSize() {
	return newParameterVect.size();
}

vector<string>& Parameter::separateParameters() {
	
	for (unsigned int i = 0; i < parameterVect.size(); i++) {
		parameterStream << parameterVect.at(i);
	}
	string inputStr = parameterStream.str();
	
	char next, peek;
	while (parameterStream.peek() != EOF) {
		next = parameterStream.get();
		peek = parameterStream.peek();

		if (next == '\'') {
			ss << next;
			while (peek != EOF) {
				next = parameterStream.get();
				peek = parameterStream.peek();
				if (next == '\'') {
					ss << next;
	//				cout << ss.str() << endl;
					newParameterVect.push_back(ss.str());
					ss.str("");
					next = parameterStream.get();
				}
				ss << next;
			} //End of while loop
		}
	}

	sort(newParameterVect.begin(), newParameterVect.end());
	newParameterVect.erase(unique(newParameterVect.begin(), 
		newParameterVect.end()), newParameterVect.end());

	return newParameterVect;
}

void Parameter::setConstant(bool t) {
	isConstant = t;
}

bool Parameter::getConstant() {
	return isConstant;
}

void Parameter::setParameter(string s) {
	parameter = s;
}

string Parameter::getParameter() {
	return parameter;
}

void Parameter::setSeen() {
	isSeen = true;
}

bool Parameter::seen() {
	return isSeen;
}

void Parameter::setKeep() {
	isKeep = true;
}

bool Parameter::keep() {
	return isKeep;
}

void Parameter::setRename() {
	isRename = true;
}

bool Parameter::rename() {
	return isRename;
}

