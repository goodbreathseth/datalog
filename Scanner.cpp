#include "Scanner.h"

Scanner::Scanner() {}

Scanner::Scanner(string fileName) {
	file = fileName;
	in.open(file);
	next = in.get();
	lineNum = 1;
}

vector<Token*>& Scanner::tokenize() {
	
	while ((in.peek()) != EOF) {
		ss.str("");
		match = true;
		lengthOfStrEvaluated = 0;

		switch (next) {
		case '\n':
			lineNum++;
			break;

		case ',':
			enumNum = 0; 
			tokenString = next;
			tokens.push_back(new Token(enumNum, tokenString, lineNum));
			break;

		case '.':
			enumNum = 1;
			tokenString = next;
			tokens.push_back(new Token(enumNum, tokenString, lineNum));
			break;

		case '?':
			enumNum = 2;
			tokenString = next;
			tokens.push_back(new Token(enumNum, tokenString, lineNum));
			break;

		case '(':
			enumNum = 3;
			tokenString = next;
			tokens.push_back(new Token(enumNum, tokenString, lineNum));
			break;

		case ')':
			enumNum = 4;
			tokenString = next;
			tokens.push_back(new Token(enumNum, tokenString, lineNum));
			break;

		case ':': 
			if (in.peek() == '-') {
				in.get();
				enumNum = 6;
				tokenString = ":-";
				tokens.push_back(new Token(enumNum, tokenString, lineNum));
				break;
			}
			else {
				enumNum = 5;
				tokenString = next;
				tokens.push_back(new Token(enumNum, tokenString, lineNum));
				break;
			}

		case '*':
			enumNum = 7;
			tokenString = next;
			tokens.push_back(new Token(enumNum, tokenString, lineNum));
			break;

		case '+':
			enumNum = 8;
			tokenString = next;
			tokens.push_back(new Token(enumNum, tokenString, lineNum));
			break;

		case 'S':
			caseS();
			break;

		case 'F':
			caseF();
			break;

		case 'R':
			caseR();
			break;

		case 'Q':
			caseQ();
			break;
			
		case '\'': 
			caseString();
			break;
		
		case '#': 
			caseComment();
			break;

		case ' ':
			break;

		case '\t':
			break;

		default:
			//Evaluate if it's an ID or UNDEFINED
			if (isalpha(next)) {
				ss << next;
				while (((in.peek()) != ' ') && isalnum(in.peek())) {
					next = in.get();
					ss << next;
				}
				//Create ID token
				enumNum = 13;
				tokenString = ss.str();
				tokens.push_back(new Token(enumNum, tokenString, lineNum));
			}
			//Create UNDEFINED token
			else {
				enumNum = 16;
				tokenString = next;
				tokens.push_back(new Token(enumNum, tokenString, lineNum));
			}
			break;
		} //End of switch statement

		next = in.get();
	} //End of while loop

	createEOFtoken();

	return tokens;
}

void Scanner::caseS() {
	//Compare letters of "Schemes" with the corresponding letters of input file
	testStr = "Schemes";
	compareStrings(testStr);
	checkIfID();

	//Create SCHEMES token if it matched
	if (match) {
		enumNum = 9;
		tokenString = testStr;
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
	//Create ID token if it didn't
	else {
		enumNum = 13;
		tokenString = ss.str();
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
}

void Scanner::caseF() {
	//Compare letters of "Facts" with the corresponding letters of input file
	testStr = "Facts";
	compareStrings(testStr);
	checkIfID();

	//Create FACTS token if it matched
	if (match) {
		enumNum = 10;
		tokenString = testStr;
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
	//Create ID token if it didn't
	else {
		enumNum = 13;
		tokenString = ss.str();
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
}

void Scanner::caseR() {
	//Compare letters of "Rules" with the corresponding letters of input file
	testStr = "Rules";
	compareStrings(testStr);
	checkIfID();

	//Create RULES token if it matched
	if (match) {
		enumNum = 11;
		tokenString = testStr;
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
	//Create ID token if it didn't
	else {
		enumNum = 13;
		tokenString = ss.str();
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
}

void Scanner::caseQ() {
	//Compare letters of "Queries" with the corresponding letters of input file
	testStr = "Queries";
	compareStrings(testStr);
	checkIfID();
	
	//Create QUERIES token if it matched
	if (match) {
		enumNum = 12;
		tokenString = testStr;
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
	//Create ID token if it didn't
	else {
		enumNum = 13;
		tokenString = ss.str();
		tokens.push_back(new Token(enumNum, tokenString, lineNum));
	}
}

void Scanner::compareStrings(string testStr) {
	for (unsigned int i = 1; i < testStr.length(); i++) {
		next = in.peek();
		if (testStr.at(i) != next) {
			match = false;
			lengthOfStrEvaluated = i;
			break;
		}
		in.get();
	}

	if (match == true)
		lengthOfStrEvaluated = testStr.length();
	//To get the amount of the string already evaluated
	for (int i = 0; i < lengthOfStrEvaluated; i++) {
		ss << testStr.at(i);
	}
}

void Scanner::checkIfID() {
	//Check if it's an ID
	if (isalnum(in.peek())) {
		match = false;
		//Keep on evaluating the file till it can't be an ID
		while (((in.peek()) != ' ') && isalnum(in.peek())) {
			next = in.get();
			ss << next;
		}
	}
}

void Scanner::caseString() {
	//Case for if it is a string
	ss << next;
	beginningOfStringLine = lineNum;
	while (in.peek() != EOF) {
		next = in.get();
		incrementLine();
		if (next == '\'') {
			ss << next;
			if (in.peek() != '\'') {
				break;
			}
			next = in.get();
		}
		ss << next;
	} //End of while loop

	createStringCommentToken(14);
}

void Scanner::caseComment() {
	//Case for if it is a comment
	beginningOfStringLine = lineNum;
	ss << next;
	if (in.peek() != '|') {
		while ((in.peek() != '\n') && (in.peek() != EOF)) {
			next = in.get();
			ss << next;
		}
	}
	else {
		while (in.peek() != EOF) {
			incrementLine();
			if ((next = in.get()) == '|' && in.peek() == '#') {
				ss << next;
				next = in.get();
				ss << next;
				break;
			}
			else
				ss << next;
		}
	}
	createStringCommentToken(15);
}

void Scanner::incrementLine() {
	if (next == '\n' && in.peek() != EOF)
		lineNum++;
}

void Scanner::createStringCommentToken(int num) {
	//If it's a comment, create comment token
	if (in.peek() != EOF) {
		enumNum = num;
		tokenString = ss.str();
		//If it's string, create string token. Comments will not be created
		if (enumNum != 15)
			tokens.push_back(new Token(enumNum, tokenString, beginningOfStringLine));
	}
	//If it encounters end of file, create an UNDEFINED token
	else {
		enumNum = 16;
		tokenString = ss.str();
		tokens.push_back(new Token(enumNum, tokenString, beginningOfStringLine));
	}
}

void Scanner::createEOFtoken() {
	if (tokens.size() != 0)
		lineNum++;
	tokenString = "";
	tokens.push_back(new Token(17, tokenString, lineNum));
}


