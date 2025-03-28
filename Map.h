#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Actor;

class Map {
private:
	vector<char> map;
	string sName;
	int iMapIndex;
public:
	// Generate Map
	Map(string sMapData);

	// Show Map
	void ShowMap();
};