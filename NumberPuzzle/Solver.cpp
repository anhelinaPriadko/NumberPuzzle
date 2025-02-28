#include "Solver.h"

Solver::Solver(DataManager& m) : manager(m)
{
	fillMaps();
}

void Solver::fillMaps()
{
	for (const auto& num : manager.numbers)
	{
		string key = num.substr(0, matchingSize);
		beginnings[key].push_back(num);
	}

	for (const auto& num : manager.numbers)
	{
		string key = num.substr(num.size() - matchingSize, matchingSize);
		endings[key].push_back(num);
	}
}

string Solver::findStartKey()
{
	int maxDifference = INT_MIN;
	string maxFoundKey;

	unordered_set<string> keys;

	for (auto& n : beginnings)
		keys.insert(n.first);

	for (auto& n : endings)
		keys.insert(n.first);

	for (auto& k : keys)
	{
		int beginSize = 0, endSize = 0;

		if (beginnings.count(k))
			beginSize = beginnings[k].size();

		if (endings.count(k))
			endSize = endings[k].size();

		int difference = beginSize - endSize;

		if (difference > maxDifference)
		{
			maxDifference = difference;
			maxFoundKey = k;
		}
	}

	return maxFoundKey;
}

void Solver::removeFromMap(string& number, string& key, unordered_map<string, vector<string>>& map)
{
	auto m = map.find(key);
	if (m != map.end())
	{
		auto& numberVector = m->second;
		auto numberPos = find(numberVector.begin(), numberVector.end(), number);

		if (numberPos != numberVector.end())
		{
			numberVector.erase(numberPos);

			if (numberVector.empty())
				map.erase(m);
		}
	}
}

void Solver::deleteNumber(string& number)
{
	string begin = number.substr(0, matchingSize);
	string end = number.substr(number.size() - matchingSize, matchingSize);

	removeFromMap(number, begin, beginnings);
	removeFromMap(number, end, endings);
}

int Solver::findSizeByKey(string& key)
{
	auto position = beginnings.find(key);

	if (position != beginnings.end())
	{
		return position->second.size();
	}

	return 0;
}

void Solver::moveToTheNext(string& key, bool first)
{
	auto position = beginnings.find(key);
	if (position == beginnings.end())
		return;

	int index = -1;
	int maxEndSize = -1;

	for (int i = 0; i < position->second.size(); ++i)
	{
		string number = position->second[i];
		string keyToFind = number.substr(number.size() - matchingSize, matchingSize);
		int size = findSizeByKey(keyToFind);

		if (size > maxEndSize)
		{
			maxEndSize = size;
			index = i;
		}
	}

	if (index == -1)
		return;

	string foundNumber = position->second[index];

	if (first)
		manager.writeData(foundNumber);
	else
		manager.writeData(foundNumber.substr(matchingSize, foundNumber.size() - matchingSize));

	deleteNumber(foundNumber);
	string nextKey = foundNumber.substr(foundNumber.size() - matchingSize, matchingSize);
	moveToTheNext(nextKey, false);
}

void Solver::solve()
{
	string firstKey = findStartKey();
	if (!firstKey.empty())
		moveToTheNext(firstKey, true);
}
