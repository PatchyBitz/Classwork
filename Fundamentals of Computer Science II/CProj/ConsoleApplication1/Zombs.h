#pragma once
#include "WorldTile.h"
#include <vector>
#include <string>
struct mutation {
	int boost = 0;
	std::string traitname;
};

class Zombs : public WorldTile
{
public:
	Zombs(int x, int y);
	Zombs();
	void Mutate();
	void Danger();
	
private:
	std::vector<mutation> constitution;
	int mutations;
	int chances;
};

