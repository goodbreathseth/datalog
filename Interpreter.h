#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "Database.h"
#include "DatalogProgram.h"
#include "Parameter.h"
using namespace std;

class Interpreter
{
public:
	Interpreter(const Interpreter& a) {};
	Interpreter(vector<Relation>& relationVect, vector<string>& factVect,
		vector<string>& queryVect) {
		this->relationVect = relationVect;
		this->factVect = factVect;
		this->queryVect = queryVect;
		factVectIndexToAdd = 0;
		relationVectIndexToAdd = 0;

		for (unsigned int i = 0; i < factVect.size(); i++) {
			relationName = factVect.at(i).substr(0, factVect.at(i).find('('));
			for (unsigned int j = 0; j < relationVect.size(); j++) {
				if (relationVect.at(j).getName() == relationName) {
					factVectIndexToAdd = i;
					relationVectIndexToAdd = j;
					parseTuples();
				}
			}
		}
		parseAllQueries();
		

		//printTuples();

	};
	~Interpreter() {};
	void parseTuples() {
		Tuple a = Tuple();
		line = factVect.at(factVectIndexToAdd);
		
		//cout << "All parameters in the tuples:" << endl;
		//cout << line << endl;

		line = line.substr(line.find('(') + 1);
		//FIXME: the above statement might prove to be a bad idea because it doesn't refresh
		if (relationVect.at(relationVectIndexToAdd).getSizeOfParameters() == 1) {
			a.push_back(line.substr(0, line.find(')')));
		}
		else if (relationVect.at(relationVectIndexToAdd).getSizeOfParameters() > 1) {
			a.push_back(line.substr(0, line.find(',')));
			//cout << line.substr(0, line.find(',')) << endl;
			line = line.substr(line.find(',') + 1);
			for (int i = 0; i < relationVect.at(relationVectIndexToAdd).getSizeOfParameters() - 2; i++) {
				a.push_back(line.substr(0, line.find(',')));
				//cout << line.substr(0, line.find(',')) << endl;
				line = line.substr(line.find(',') + 1);
			}
			a.push_back(line.substr(0, line.find(')')));
			//cout << line.substr(0, line.find(')')) << endl;
		}
		relationVect.at(relationVectIndexToAdd).addTuple(a);

	}
/*
	void printTuples() {
		for (unsigned int i = 0; i < relationVect.size(); i++) {
			cout << relationVect.at(i).toString() << endl;
		}
	}
*/
	void parseQuery(unsigned int i) {
		queryVectIndex = i;
		line = queryVect.at(i).substr(queryVect.at(i).find('(') + 1);
		//cout << "ALL THE PARAMETERS" << line << endl;
		vector<Parameter*> newQueryVect;
		relationName = queryVect.at(i).substr(0, queryVect.at(i).find('('));
		//To get the size of the parameter
		for (unsigned int j = 0; j < relationVect.size(); j++) {
			if (relationVect.at(j).getName() == relationName) {
				//cout << relationName << endl;
				relationVectIndexToAdd = j;
				parameterSize = relationVect.at(j).getSizeOfParameters();
				break;
			}
		}

		if (parameterSize == 1) {
			newQueryVect.push_back(new Parameter(line.substr(0, line.find(')'))));
		}
		else if (parameterSize > 1) {
			newQueryVect.push_back(new Parameter(line.substr(0, line.find(','))));
			line = line.substr(line.find(',') + 1);
			for (int j = 0; j < parameterSize - 2; j++) {
				newQueryVect.push_back(new Parameter(line.substr(0, line.find(','))));
				line = line.substr(line.find(',') + 1);
			}
			newQueryVect.push_back(new Parameter(line.substr(0, line.find(')'))));
		}
		setQueryConstants(newQueryVect);
		evaluateQueries(relationName, newQueryVect);


		//Free memory allocations
		for (unsigned int z = 0; z < newQueryVect.size(); z++) 
			delete newQueryVect.at(z);
		
	}

	void setQueryConstants(vector<Parameter*>& newQueryVect) {
		for (unsigned int i = 0; i < newQueryVect.size(); i++) {
			if (newQueryVect.at(i)->getParameter().at(0) == '\'')
				newQueryVect.at(i)->setConstant(true);
			else 
				newQueryVect.at(i)->setConstant(false);
		}
	}

	void parseAllQueries() {
		for (unsigned int i = 0; i < queryVect.size(); i++) {
			parseQuery(i);
		}
	}

	void evaluateQueries(string relationName, vector<Parameter*>& newQueryVect) {
		map<string, int> firstInstances;
		Header newHead = Header();
		vector<int> colToKeep;
		relationToEdit = relationVect.at(relationVectIndexToAdd);

		//Select operations
		for (unsigned int i = 0; i < newQueryVect.size(); i++) {
			if (newQueryVect.at(i)->getConstant()) {
				relationToEdit = select1(newQueryVect.at(i)->getParameter(), i);
			}
			else {
				//If the parameter hasn't been seen, put it into the map, add what column its in
				//and start creating a new header
				if (firstInstances.count(newQueryVect.at(i)->getParameter()) == 0) {
					firstInstances.insert(pair<string, int>(newQueryVect.at(i)->getParameter(), i));
					colToKeep.push_back(i);
					newHead.push_back(newQueryVect.at(i)->getParameter());
				}
				//If it has been seen, call the second select function with the columns that it is in
				else {
					int firstCol = firstInstances[newQueryVect.at(i)->getParameter()];
					relationToEdit = select2(firstCol, i);
				}
			}
		}

		//Project operation
		relationToEdit = project(colToKeep);

		//Rename operation
		relationToEdit = rename(newHead);

		printResults();
		

	}

	void printResults() {
		if (relationToEdit.getSetOfTuples().size() == 0)
			cout << queryVect.at(queryVectIndex) << " No" << endl;
		else {
			cout << queryVect.at(queryVectIndex) << " Yes(" <<
				relationToEdit.getSetOfTuples().size() << ")" << endl;
			for (Tuple t : relationToEdit.getSetOfTuples()) {
				if (relationToEdit.getHeader().size() >= 1) {
					cout << " ";
					cout << " " << relationToEdit.getHeader().at(0) << "=" << t.at(0);
					for (unsigned int l = 1; l < relationToEdit.getHeader().size(); l++) {
						cout << ", " << relationToEdit.getHeader().at(l) << "=" << t.at(l);
					}
					cout << endl;
				}
			}
		}
	}

	Relation rename(Header& header) {
		//Rename the header to be the variables in the particular columns
		Relation newRel(relationName, header);
		for (Tuple t : relationToEdit.getSetOfTuples()) {
			newRel.addTuple(t);
		}
		
		return newRel;
	}

	Relation project(vector<int>& colToKeep) {
		//Create new header
		Header newHead = Header();

		//For each column number in the vector of colToKeep, add that column to new header
		for (unsigned int i = 0; i < colToKeep.size(); i++)
			newHead.push_back(relationToEdit.getHeader().at(colToKeep.at(i)));

		//Make new relation with same name and new header
		Relation newRel = Relation(relationName, newHead);
	//	cout << "new header to keep" << newHead.at(0) << endl;
		//For each tuple in the current relation, make a new tuple
		for (Tuple t : relationToEdit.getSetOfTuples()) {
			Tuple newT = Tuple();
			for (unsigned int j = 0; j < colToKeep.size(); j++)
				newT.push_back(t.at(colToKeep.at(j)));

			newRel.addTuple(newT);
		}

		//Return new relation
		return newRel;
	}

	Relation select1(string value, int columnNum) {
		Relation newRel = Relation(relationName, relationToEdit.getHeader());
		for (Tuple t : relationToEdit.getSetOfTuples()) {
			if (t.at(columnNum) == value)
				newRel.addTuple(t);
		}
		return newRel;
		
	}

	Relation select2(int colN, int colM) {
		Relation newRel = Relation(relationName, relationToEdit.getHeader());
		for (Tuple t : relationToEdit.getSetOfTuples()) {
			if (t.at(colN) == t.at(colM))
				newRel.addTuple(t);
		}
		return newRel;
	}
private:
	vector<Relation> relationVect;
	vector<string> factVect;
	vector<string> queryVect;
	stringstream ss;
	int factVectIndexToAdd;
	int relationVectIndexToAdd;
	int parameterSize;
	int queryVectIndex;
	string relationName;
	string line;
	Relation relationToEdit;

};

#endif