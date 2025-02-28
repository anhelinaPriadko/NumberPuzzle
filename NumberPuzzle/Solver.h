#pragma once
#include "DataManager.h"
#include <unordered_map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

class Solver
{
private:
	unordered_map <string, vector<string >> beginnings;
	unordered_map <string, vector<string>> endings;
	DataManager &manager;
	int matchingSize = 2;
	

public:
	Solver(DataManager& m);

	void fillMaps();
	string findStartKey();

	void removeFromMap(string &number, string &key, unordered_map<string, vector<string>> &map);
	void deleteNumber(string& number);
	int findSizeByKey(string& key);

	void moveToTheNext(string& key, bool first);
	void solve();
};

