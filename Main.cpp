//Seth Hinton

#include <iostream>
#include <string>
#include <vector>
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"
using namespace std;

//Includes to detect memory leaks

/*
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif
*/

int main(int argc, char * argv[]) {
//	VS_MEM_CHECK

	//Set up file in scanner class
	string filename = argv[1];
	Scanner s = Scanner(filename);

	vector<Token*> tokenVect = s.tokenize();
	int size = tokenVect.size();

	/* --- THIS WAS USED FOR THE OUTPUT IN LAB 1 ---
	//Tokenize entire file and output tokens to display
	for (int i = 0; i < size; i++)
		cout << tokenVect.at(i)->toString() << endl;
	cout << "Total Tokens = " << size;
	*/

	Parser p = Parser(tokenVect);
	p.parse();

	//Delete tokens to free memory
	for (int i = 0; i < size; i++)
		delete tokenVect.at(i);
	
	return 0;
}