#include "Zombs.h"
#include "WorldTile.h"
#include <string>
#include <vector>
#include <random>

//struct mutation {
//	int boost = 0;
//	std::string traitname;
//};
std::vector<mutation> constitution;
Zombs::Zombs() {
    sprite = 'X';
    infectable = 0;
	chances = 5;
	mutations = 2;
    infected = 1;
    Zombs::Mutate();
    Zombs::Danger();
}
Zombs::Zombs(int mutationlimit , int chance) {
    sprite = 'X';
    chances = chance;
    mutations = mutationlimit;
    infectable = 0;
    infected = 1;
    Zombs::Mutate();
    Zombs::Danger();
}

void Zombs::Mutate() {
    /*Imported from GeeksForGeeks*/
    std::random_device rd;     //Not sure if this is a good implementation to randomize the human or if it'd be better to hand this over to the zombsim to seed the person as part of the call. I might redo this later (Or never)
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 4); //This determines the max amount of items/traits available due to limiting the mutate and equip functions indexes.
    using namespace std;
	vector<string> traits = { "Shotgun","Leather Jacket","Radio","Camping Stove","Map" };
    vector<int> assist = { 4,2,2,3,1 };
    for (int i = 0; i < mutations; i++) {
        int randomValue = distrib(gen);
        mutation newTrait;
        newTrait.boost = assist[randomValue];
        newTrait.traitname = traits[randomValue];
        constitution.push_back(newTrait);
    }
}

void Zombs::Danger() {
    int danger = 0;
    for (auto x : constitution) {
        danger += x.boost;
    }
    danger += chances;
    imminf = danger;
}

//Some way to stack both into the same