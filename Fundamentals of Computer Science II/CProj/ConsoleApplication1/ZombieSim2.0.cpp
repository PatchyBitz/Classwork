//Author: Yenshae
//Class: Fundamentals of computer science.
//Teacher: Melissa Holmes
//Description: Zombie Sim V2
#include <iostream>
using namespace std;
#include "Humies.h"
#include "Zombs.h"
#include <string>

void printWorld(vector<vector<WorldTile*>>& world) {
	using namespace std;
	for (int iy = 0; iy < world.size(); iy++) {
		cout << "\n";
		for (int ix = 0; ix < world[iy].size(); ix++) {
			cout << world[iy][ix]->sprite << " ";
		}
	}
}


vector<vector<WorldTile*>> initWorld(int xz, int yz,int hequip,int hskill) {

	vector<vector<WorldTile*>> World1;

	vector<WorldTile*> row;
	for (int x = 0; x < xz; x++) {
		Humies* newhuman = new Humies(hequip, hskill);
		row.push_back(newhuman);
	}

	for (int y = 0; y < yz; y++) {
		vector<WorldTile*> row;
		for (int x = 0; x < xz; x++) {
			Humies* newhuman = new Humies(hequip, hskill);
			row.push_back(newhuman);
		}
		World1.push_back(row);
	}

	return World1;
}

int infectable(WorldTile*& infector, WorldTile*& infectee) {
	if (infectee->infectable == 0 and infector->imminf > infectee->imminf) {
		return 1;
	}
	else {
		return 0;
	}

}

void infect(int x, int y, vector<vector<WorldTile*>>& location,int zmuta,int zskill) {

	if (x + 1 < location[y].size() and infectable(location[y][x], location[y][x + 1]) == 1) { //Right
		delete location[y][x + 1];
		location[y][x + 1] = new Zombs(zmuta, zskill);
	}
	if (x - 1 >= 0 and infectable(location[y][x], location[y][x - 1]) == 1) { //Left
		delete location[y][x - 1];
		location[y][x - 1] = new Zombs(zmuta, zskill);
	}

	if (y - 1 >= 0 and infectable(location[y][x], location[y - 1][x]) == 1) { //Up
		delete location[y - 1][x];
		location[y - 1][x] = new Zombs(zmuta, zskill);
	}

	if (y + 1 < location.size() and infectable(location[y][x], location[y + 1][x]) == 1) { //Down
		delete location[y + 1][x];
		location[y + 1][x] = new Zombs(zmuta, zskill);
	}

	if (y + 1 < location.size() and x - 1 >= 0 and infectable(location[y][x], location[y + 1][x - 1]) == 1) { //Bottom left
		delete location[y + 1][x - 1];
		location[y + 1][x - 1] = new Zombs(zmuta, zskill);
	}
	if (y - 1 < location.size() and x + 1 < location[y].size() and infectable(location[y][x], location[y - 1][x + 1]) == 1) { //Top right
		delete location[y - 1][x + 1];
		location[y - 1][x + 1] = new Zombs(zmuta, zskill);
	}
	if (y + 1 < location.size() and x - 1 >= 0 and infectable(location[y][x], location[y + 1][x - 1]) == 1) { //Top left
		delete location[y + 1][x - 1];
		location[y + 1][x - 1] = new Zombs(zmuta, zskill);
	}

	if (y + 1 < location.size() and x + 1 < location[y].size() and infectable(location[y][x], location[y + 1][x + 1]) == 1) { //Bottom right
		delete location[y + 1][x + 1];
		location[y + 1][x + 1] = new Zombs(zmuta, zskill);
	}
}

void infectWorld(int Zzx, int Zzy, vector<vector<WorldTile*>>& world,int max,int zmuta,int zskill) {
	int test = 0;
	delete world[Zzy - 1][Zzx - 1];
	world[Zzy - 1][Zzx - 1] = new Zombs(zmuta, zskill); // Initial Zombie
	vector<int> zomblocations;
	int humanstanding = 0;

	cout << "\n";

	if (world[0].size() == 1 and world.size() == 1) {
		cout << "World dimension one; Which one came first? The sapian or the zombie?";

	}

	else if (world[0].size() == 1) { //Case for only one row
		do {
			printWorld(world);
			zomblocations.clear();
			humanstanding = 0;
			for (int i = 0; i < world.size(); i++) {
				if (world[i][0]->infected == 1) {
					//zomblocations.push_back(0);
					zomblocations.push_back(i);
				}
				else if (world[i][0] -> sprite == '.') {
					humanstanding = 1;
				}
			}
			for (int it = 0; it < zomblocations.size(); it += 1) {
				infect(0, zomblocations[it], world,zmuta,zskill);
			}
			cout << "\n";
			test++;

		} while (humanstanding != 0 and test <= max);


	}

	else if (world.size() == 1) {	//Case for only one column
		do {
			printWorld(world);
			zomblocations.clear();
			humanstanding = 0;
			for (int i = 0; i < world[0].size(); i++) {
				if (world[0][i]->infected == 1) {
					//zomblocations.push_back(0);
					zomblocations.push_back(i);
				}
				else if (world[0][i] ->infected == 0) {
					humanstanding = 1;
				}
			}
			for (int it = 0; it < zomblocations.size(); it += 1) {
				infect(zomblocations[it], 0, world, zmuta,zskill);
			}
			cout << "\n";
			test++;

		} while (humanstanding != 0 and test <= max);
	}
	else { //General case for a square or rectangle.
		do {   //Flow : Do loop - Iteration of the world. for loop 1 - scans the worlds for zombies and adds them to a list. for loop 2 - goes through zombie list and infects based on their location.
			printWorld(world);
			zomblocations.clear();
			humanstanding = 0;

			for (int iy = 0; iy < world.size() - 1; iy++) {
				for (int ix = 0; ix < world[iy].size() - 1; ix++) {
					if (world[iy][ix]->infected == 1) {
						zomblocations.push_back(iy);
						zomblocations.push_back(ix);
					}
					else if (world[iy][ix]->infected == 0) { //If there is any human left during the scan, this flag is set and another iteration is run
						humanstanding = 1;
					}
				}
			}

			for (int it = 0; it < zomblocations.size(); it += 2) {
				infect(zomblocations[it + 1], zomblocations[it], world,zmuta,zskill);
			}
			cout << "\n";
			test++;
		} while (humanstanding != 0 and test <= max);
		printWorld(world);
	}
}

int main(int argc, char* argv[]) {
	int sizex = atoi(argv[1]);
	int sizey = atoi(argv[2]);
	int zZx = atoi(argv[3]);
	int zZy = atoi(argv[4]);
	int maxiter = 5; //Max world iterations.
	int humanequipment = 3; // Amount of "boosts" that humans can get, random between 1-5
	int humanskill = 1; // Base survivabilty without boosts
	int zombmuta = 3; //Same as humanequipment but for zombies
	int zombskill = 1; // Base infection without the boosts
	vector<vector<WorldTile*>> World1;
	World1 = initWorld(sizex, sizey,humanequipment,humanskill);
	printWorld(World1);
	infectWorld(zZx, zZy, World1,maxiter,zombmuta,zombskill);


	// Zombs(x,y) x is the amount of mutations a zombie gets and y is their base power 
	// Same with Humies(x,y) except x is equipment and y is their base survivability.
	// Modifying the Humies,Zombs, and the survivability checks should be able to make it look interesting
	// Still need to test from 0,1 and take args again.
	//Core is working, still needs tweaks to make it look more interesting. 
}

