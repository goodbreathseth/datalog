#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(Predicate & schemePred, Predicate & factPred, Rule & rulesObj, Predicate & queryPred) {
	schemes = schemePred.toString();
	schemeSize = schemePred.vectSize();
	facts = factPred.toString();
	factSize = factPred.vectSize();
	rules = rulesObj.toString();
	ruleSize = rulesObj.vectSize();
	queries = queryPred.toString();
	querySize = queryPred.vectSize();
}

DatalogProgram::DatalogProgram(Predicate& schemePred, Predicate& factPred, Rule& rulesObj,
	Predicate& queryPred, Parameter& domainPara) {
	schemes = schemePred.toString();
	schemeSize = schemePred.vectSize();
	facts = factPred.toString();
	factSize = factPred.vectSize();
	rules = rulesObj.toString();
	ruleSize = rulesObj.vectSize();
	queries = queryPred.toString();
	querySize = queryPred.vectSize();
	domain = domainPara.toString();
	domainSize = domainPara.vectSize();
	//this->schemePred = schemePred;
}

DatalogProgram::~DatalogProgram()
{
}

string DatalogProgram::toString() {
	ss << "Schemes(" << schemeSize << "):" << endl << schemes <<
		"Facts(" << factSize << "):" << endl << facts <<
		"Rules(" << ruleSize << "):" << endl << rules <<
		"Queries(" << querySize << "):" << endl << queries <<
		"Domain(" << domainSize << "):" << endl << domain;
	return ss.str();
}

//Predicate & DatalogProgram::getSchemePred() {
//	return schemePred;
//}
