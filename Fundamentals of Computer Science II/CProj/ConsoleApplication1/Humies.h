#pragma once
#include <vector>
#include <string>
#include "WorldTile.h"
using namespace std;
struct items {
	int boost = 0;
	std::string itemname;
};
class Humies : public WorldTile
{
private:
	int equipcount;
	int chances;
	vector<items> inventory;
	
public:
	Humies();
	Humies(int equips, int chance);
	void Equip();
	vector<items> GetInventory();
	void Survivability();
};

