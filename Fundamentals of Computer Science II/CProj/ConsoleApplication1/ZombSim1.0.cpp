//Author: Yenshae
//Class: Fundamentals of computer science.
//Teacher: Melissa Holmes
//Description: Zombie Sim V1 - Revised 3/12/2025: Tightened up logic and sorted out edge cases such as having a single width or single length
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

void printWorld(vector<vector<char>> world){
	for (int iy = 0; iy < world.size(); iy++) {
		cout << "\n";
		for (int ix = 0; ix < world[iy].size(); ix++) {
			cout << world[iy][ix] <<" ";
		}
	}
}

vector<vector<char>> initWorld(int x,int y) {

	vector<vector<char>> world;
	vector<char> rows;
	for (int nx = 0; nx < x; nx++) {
		rows.push_back('.');
	}
	for (int iy = 0; iy < y; iy++) {
			world.push_back(rows);
	}
	return world;

}

void infect(int x,int y, vector<vector<char>> &location) {
		if (x + 1 < location[y].size()) { //Right
			location[y][x + 1] = 'Z';
		}
		if (x - 1 >= 0) { //Left
			location[y][x - 1] = 'Z';
		}

		if (y - 1 >= 0) { //Up
			location[y - 1][x] = 'Z';
		}

		if (y + 1 < location.size() ){ //Down 
			location[y + 1][x] = 'Z';
		}

		if (y + 1 < location.size() and x - 1 >= 0) { //Bottom left
			location[y + 1][x - 1] = 'Z';
		}
		if (y - 1 < location.size() and x + 1 < location[y].size()) { //Top right
			location[y - 1][x + 1] = 'Z';
		}
		if (y + 1 < location.size() and x - 1 >= 0) { //Top left
			location[y + 1][x - 1] = 'Z';
		}

		if (y + 1 < location.size() and x + 1 < location[y].size()) { //Bottom right
			location[y + 1][x + 1] = 'Z';
		}
}

void infectWorld(int Zzx, int Zzy, vector<vector<char>>& world) {
	world[Zzy - 1][Zzx - 1] = 'Z';
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
				if (world[i][0] == 'Z') {
					//zomblocations.push_back(0);
					zomblocations.push_back(i);
				}
				else if (world[i][0] == '.') {
					humanstanding = 1;
				}
			}
			for (int it = 0; it < zomblocations.size(); it += 1) {
				infect(0,zomblocations[it], world);
			}
			cout << "\n";

		} while (humanstanding != 0);


	} 

	else if (world.size() == 1) {	//Case for only one column
	do {
		printWorld(world);
		zomblocations.clear();
		humanstanding = 0;
		for (int i = 0; i < world[0].size(); i++) {
			if (world[0][i] == 'Z') {
				//zomblocations.push_back(0);
				zomblocations.push_back(i);
			}
			else if (world[0][i] == '.') {
				humanstanding = 1;
			}
		}
		for (int it = 0; it < zomblocations.size(); it += 1) {
			infect( zomblocations[it],0, world);
		}
		cout << "\n";
			
		}while (humanstanding != 0);
	}
	else { //General case for a square or rectangle.
		do {   //Flow : Do loop - Iteration of the world. for loop 1 - scans the worlds for zombies and adds them to a list. for loop 2 - goes through zombie list and infects based on their location.
			printWorld(world);
			zomblocations.clear();
			humanstanding = 0;

			for (int iy = 0; iy < world.size() - 1; iy++) {
				for (int ix = 0; ix < world[iy].size() - 1; ix++) {
					if (world[iy][ix] == 'Z') {
						zomblocations.push_back(iy);
						zomblocations.push_back(ix);
					}
					else if (world[iy][ix] == '.') { //If there is any human left during the scan, this flag is set and another iteration is run
						humanstanding = 1;
					}
				}
			}

			for (int it = 0; it < zomblocations.size(); it += 2) {
				infect(zomblocations[it + 1], zomblocations[it], world);
			}
			cout << "\n";
		} while (humanstanding != 0);
		printWorld(world);
	}
}


int main(int argc, char* argv[]) {
	int sizex = atoi(argv[1]);
	int sizey = atoi(argv[2]);
	int zZx = atoi(argv[3]);
	int zZy = atoi(argv[4]);
	vector<vector<char>> planet1;
	planet1 = initWorld(sizex, sizey);
	infectWorld(zZx, zZy, planet1);

	//vector <char> row;
	//vector <char> column;
	

}