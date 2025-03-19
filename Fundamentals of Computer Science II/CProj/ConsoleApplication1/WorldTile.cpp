#include "WorldTile.h"
#include <vector>
#include <string>
#include <random>
std::random_device rd;     //Not sure if this is a good implementation to randomize the human or if it'd be better to hand this over to the zombsim to seed the person as part of the call. I might redo this later (Or never)
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 4);
WorldTile::WorldTile() {
	infectable = 0;
	sprite = 'L';
	imminf = 0;
	infected = 0;
}