#include "Parser.h"

Parser::Parser(vector<Token*>& tokenVect) {
	this->tokenVect = tokenVect;
	index = 0;
}

void Parser::parse() { //SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList

	


	try {
		notifier = " ";
		match(SCHEMES);
		match(COLON);
		scheme();
		schemeList();
		Predicate schemePred(schemeVect);
		
		for (unsigned int i = 0; i < schemeNames.size(); i++) {
			relationVect.push_back(Relation(schemeNames.at(i), headerVect.at(i)));
		}
		
		
		match(FACTS);
		match(COLON);
		domainString.str("");
		factList();
		Predicate factPred(factVect);
		Parameter domainPara(domainVect);

		notifier = "rules";
		match(RULES);
		match(COLON);
		ruleList();
		Rule rulesObj(ruleVect);
		notifier = "queries";
		match(QUERIES);
		match(COLON);
		query();
		queryList();
		Predicate queryPred(queryVect);
		match(EOF_TYPE);
//		cout << "Success!" << endl;
		DatalogProgram dataProg(schemePred, factPred, rulesObj, queryPred, domainPara);
		//cout << dataProg.toString();
		Interpreter intepreter = Interpreter(relationVect, factVect, queryVect);
	}
	catch (Token error) {
		cout << "Failure!" << endl <<
			"\t\t" << error.toString();
	}
	
	catch (...) {
		cout << "Failure!" << endl << 
			"\t\t" << tokenVect.at(index)->toString();
	}
	
}

//Compare if the correct token that is expected is the same as the current token type in tokenVect
void Parser::match(int tokenType) {
	if (tokenType == tokenVect.at(index)->getEnum()) {
		//cout << "matching: " << tokenVect.at(index)->toString() << endl;
		if (tokenType != COLON && tokenType != SCHEMES && tokenType != FACTS &&
			tokenType != RULES && tokenType != QUERIES)
			ss << tokenVect.at(index)->getString();
		if (tokenType == STRING) 
			domainString << tokenVect.at(index)->getString();
		if (tokenType == STRING || tokenType == ID)
			addToCorrespondingVector();
		index++;
	}
	else {
		//cout << "throwing: " << tokenType << endl;
		throw tokenVect.at(index);
	}
}

void Parser::schemeList() {
	if (tokenVect.at(index)->getEnum() == ID)
		scheme();
	if (tokenVect.at(index)->getEnum() == ID)
		schemeList();
}

void Parser::factList() {
	if (tokenVect.at(index)->getEnum() == ID)
		fact();
	if (tokenVect.at(index)->getEnum() == ID)
		factList();
}

void Parser::ruleList() {
	if (tokenVect.at(index)->getEnum() == ID)
		rule();
	if (tokenVect.at(index)->getEnum() == ID)
		ruleList();
}

void Parser::queryList() {
	if (tokenVect.at(index)->getEnum() == ID)
		query();
	if (tokenVect.at(index)->getEnum() == ID)
		queryList();
}

//Do this in fact() and query()
void Parser::scheme() {
	notifier = "schemes";
	headerVect.push_back(Header());
	headPredicate();
	schemeVect.push_back(ss.str());
	ss.str("");
}

void Parser::fact() {
	notifier = "facts";
	match(ID);
	match(LEFT_PAREN);
	notifier = "individualTuples";
	match(STRING);
	if ((tokenVect.at(index)->getEnum() == COMMA))
		stringList();
	match(RIGHT_PAREN);
	match(PERIOD);
	factVect.push_back(ss.str());
	ss.str("");
	domainVect.push_back(domainString.str());
	domainString.str("");
}

void Parser::rule() {
	headPredicate();
	ss << " ";
	match(COLON_DASH);
	ss << " ";
	predicate();
	predicateList();
	match(PERIOD);
	ruleVect.push_back(ss.str());
	ss.str("");
}

void Parser::query() {
	predicate();
	match(Q_MARK);
	queryVect.push_back(ss.str());
	ss.str("");
}

void Parser::headPredicate() {
	match(ID);
	match(LEFT_PAREN);
	if (notifier == "schemes")
		notifier = "schemeHeaders";
	match(ID);
	if (tokenVect.at(index)->getEnum() != RIGHT_PAREN)
		idList();
	match(RIGHT_PAREN);
}

void Parser::predicate() {
	match(ID);
	match(LEFT_PAREN);
	if (tokenVect.at(index)->getEnum() == STRING)
		stringParameter();
	else if (tokenVect.at(index)->getEnum() == ID)
		idParameter();
	else
		expression();
	parameterList();
	match(RIGHT_PAREN);
}

void Parser::predicateList() {
	if (tokenVect.at(index)->getEnum() != PERIOD) {
		match(COMMA);
		if (tokenVect.at(index)->getEnum() == ID)
			predicate();
		if (tokenVect.at(index)->getEnum() == COMMA)
			predicateList();
	}
}

void Parser::parameterList() {
	if (tokenVect.at(index)->getEnum() != RIGHT_PAREN) {
		match(COMMA);
		if (tokenVect.at(index)->getEnum() == STRING)
			stringParameter();
		else if (tokenVect.at(index)->getEnum() == ID)
			idParameter();
		else
			expression();
		if (tokenVect.at(index)->getEnum() == COMMA)
			parameterList();
	}
}

void Parser::stringList() {
	match(COMMA);
	match(STRING);
	if (tokenVect.at(index)->getEnum() == COMMA)
		stringList();
}

void Parser::idList() {
	match(COMMA);
	match(ID);
	if (tokenVect.at(index)->getEnum() == COMMA)
		idList();
}

void Parser::stringParameter() {
	match(STRING);
}

void Parser::idParameter() {
	match(ID);
}

void Parser::expressionParameter() {
	expression();
}

void Parser::expression() {
	match(LEFT_PAREN);
	if (tokenVect.at(index)->getEnum() == STRING)
		stringParameter();
	else if (tokenVect.at(index)->getEnum() == ID)
		idParameter();
	else
		expression();
	Operator();
	if (tokenVect.at(index)->getEnum() == STRING)
		stringParameter();
	else if (tokenVect.at(index)->getEnum() == ID)
		idParameter();
	else
		expression();
	match(RIGHT_PAREN);
}

void Parser::Operator() {
	if (tokenVect.at(index)->getEnum() == ADD)
		match(ADD);
	else
		match(MULTIPLY);
}

void Parser::addToCorrespondingVector() {
	if (notifier == "schemes")
		schemeNames.push_back(tokenVect.at(index)->getString());
	else if (notifier == "schemeHeaders")
		headerVect.at(schemeNames.size() - 1).push_back(tokenVect.at(index)->getString());
	else if (notifier == "facts") 
		factNames.insert(tokenVect.at(index)->getString());
	/*else if (notifier == "individualTuples") {
		for (set<string>::iterator it = factNames.begin(); 
			it != factNames.end(); ++it)

	}*/

}

