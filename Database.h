#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Relation.h"
using namespace std;

class Database : public map<string, Relation>
{
public:
	Database();
	~Database();
};

#endif