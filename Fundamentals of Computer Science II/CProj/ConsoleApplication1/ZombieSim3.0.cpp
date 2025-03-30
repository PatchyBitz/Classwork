//Author: Yenshae
//Class: Fundamentals of computer science.
//Teacher: Melissa Holmes
//Description: Zombie Sim V3 - With added conditions
#include <iostream>
using namespace std;
#include "Humies.h"
#include "Zombs.h"
#include <string>
#include <random>

std::random_device rdi ;//Not sure if this is a good implementation to randomize the human or if it'd be better to hand this over to the zombsim to seed the person as part of the call. I might redo this later (Or never)
std::mt19937 gen2(rdi());	
 //This determines the max amount of items/traits available due to limiting the mutate and equip functions indexes.

void printWorld(vector<vector<WorldTile*>>& world) {
	using namespace std;
	for (int iy = 0; iy < world.size(); iy++) {
		cout << "\n";
		for (int ix = 0; ix < world[iy].size(); ix++) {
			cout << world[iy][ix]->sprite << " ";
		}
	}
}


vector<vector<WorldTile*>> initWorld(int xz, int yz,int hskill,int minhequip,int maxhequip) {

	vector<vector<WorldTile*>> World1;
	std::uniform_int_distribution<> hdis(minhequip, maxhequip);
	int hequip = hdis(gen2);

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

void tower(vector<vector<WorldTile*>>& location) {
	if (location.size() > 3 and location[0].size() - 1 > 3) {
	
		delete location[location.size() - 2][location.size() - 2];
		location[location.size() - 2][location.size() - 2] = new WorldTile();

		delete location[location.size() - 2][location.size() - 1];
		location[location.size() - 2][location.size() - 1] = new WorldTile();

		delete location[location.size() - 1][location.size() - 2];
		location[location.size() - 1][location.size() - 2] = new WorldTile();

	}
}
int infectable(WorldTile*& infector, WorldTile*& infectee) {
	if (infectee->infectable == 1 and infector->imminf > infectee->imminf) {
		return 1;
	}
	else {
		return 0;
	}

}

void infect(int x, int y, vector<vector<WorldTile*>>& location,int zmuta,int zskill,int hskill,int hequip) {


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

// Cure
	if (y - 1 < location.size() and x + 1 < location[y].size() and infectable(location[y][x], location[y - 1][x + 1]) == 0 and location[y-1][x+1]-> sprite == '.') { //Top right
		delete location[y][x];
		location[y][x] = new Humies(hequip, hskill + 1);

	}

	if (y + 1 < location.size() and x - 1 >= 0 and infectable(location[y][x], location[y + 1][x - 1]) == 0 and location[y + 1][x - 1]->sprite == '.') { //Top left
		delete location[y][x];
		location[y][x] = new Humies(hequip, hskill + 1);
	}


}

void infectWorld(int Zzx, int Zzy, vector<vector<WorldTile*>>& world,int max,int minzmuta,int maxzmuta, int zskill, int minhequip, int maxhequip,  int hskill) {
	int test = 0;
	delete world[Zzy - 1][Zzx - 1];
	std::uniform_int_distribution<> dis(minzmuta, maxzmuta);
	int zmuta = dis(gen2);
	
	std::uniform_int_distribution<> hdis(minhequip, maxhequip);
	int hequip = hdis(gen2);

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
				infect(0, zomblocations[it], world,zmuta,zskill,hskill,hequip);
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
				infect(zomblocations[it], 0, world, zmuta,zskill,hskill,hequip);
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
				infect(zomblocations[it + 1], zomblocations[it], world,zmuta,zskill,hskill,hequip);
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
	int maxiter = 30; //Max world iterations.
	int hskill = 3; // Base survivabilty without boosts


	int minhumanequip = 3; // Min Amount of "boosts" that humans can get
	int maxhumanequip = 4; 
	

	int minzombmuta = 3; //Same as humanequipment but for zombies
	int maxzombmuta = 5;

	int zombskill = 1; // Base infection without the boosts
	
	vector<vector<WorldTile*>> World1;
	World1 = initWorld(sizex, sizey,hskill,minhumanequip,maxhumanequip);
	tower(World1);
	printWorld(World1);
	infectWorld(zZx, zZy, World1,maxiter,minzombmuta,maxzombmuta,zombskill,minhumanequip, maxhumanequip, hskill);


	// Zombs(x,y) x is the amount of mutations a zombie gets and y is their base power 
	// Same with Humies(x,y) except x is equipment and y is their base survivability.
	// Modifying the Humies,Zombs, and the survivability checks should be able to make it look interesting
	// Still need to test from 0,1 and take args again.
	//Core is working, still needs tweaks to make it look more interesting. 
}

