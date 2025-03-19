#include "Humies.h"
#include <random>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;

//int chances = 0;
//int equipcount = 0;



//struct items {
//    int boost;
//    string itemname;
//};

// Initialize a random number generator
vector<items> inventory;
Humies::Humies() {
    sprite = '.';
    infectable = 1;
    equipcount = 2;
    chances = 10;
    Humies::Equip();
    Humies::Survivability();
}
Humies::Humies(int equips,int chance) {
    sprite = '.';
    equipcount = equips;
    chances = chance;
    Humies::Equip();
    Humies::Survivability();

}
void Humies::Equip() {
    random_device rd;     //Not sure if this is a good implementation to randomize the human or if it'd be better to hand this over to the zombsim to seed the person as part of the call. I might redo this later (Or never)
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 4);
    vector<string> loot= {"Shotgun","Leather Jacket","Radio","Camping Stove","Map"};
    vector<int> assist = {4,2,2,3,1};
    for (int i = 0; i < equipcount; i++) {
        int randomValue = distrib(gen);
        items newItem;
        newItem.boost = assist[randomValue];
        newItem.itemname = loot[randomValue];
        inventory.push_back(newItem);
    }
}

vector<items> Humies::GetInventory() {
    return inventory;
}
void Humies::Survivability() {
    int survival = 0;
    for (auto i : inventory)
    {
        survival += i.boost;
    }
    survival += chances;
    imminf = survival;
}



