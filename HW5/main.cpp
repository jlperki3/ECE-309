#include "Plant.h"
#include "Flower.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// TODO: Define a PrintVector function that prints an vector of plant (or flower) object pointers
void PrintVector(const vector<Plant*>& xgarden) {
    for (size_t i = 0; i < xgarden.size(); i++) {
        cout << "Plant " << i + 1 << " Information:" << endl;
        xgarden.at(i)->PrintInfo();
        cout << endl;
    }
}

int main() {
    // TODO: Declare a vector called myGarden that can hold object of type plant pointer
    vector<Plant*> myGarden;

    // TODO: Declare variables - plantName, plantCost, flowerName, flowerCost,
    //       colorOfFlowers, isAnnual
    string input;
    string plantName;
    string flowerName;
    string colorOfFlowers;
    int plantCost;
    bool isAnnual;

    cin >> input;

    while(input != "-1") {
        if (input == "plant") {
            cin >> plantName;
            cin >> plantCost;
            Plant* newPlant = new Plant();
            newPlant->SetPlantName(plantName);
            newPlant->SetPlantCost(plantCost);
            myGarden.push_back(newPlant);
        }
         if (input == "flower") {
            cin >> flowerName;
            cin >> plantCost;
            cin >> isAnnual;
            cin >> colorOfFlowers;
            Flower* newFlower = new Flower();
            newFlower->SetPlantName(flowerName);
            newFlower->SetPlantCost(plantCost);
            newFlower->SetPlantType(isAnnual);
            newFlower->SetColorOfFlowers(colorOfFlowers);
            myGarden.push_back(newFlower);
         }
        cin >> input;
    }

    // TODO: Call the method PrintVector to print myGarden
    PrintVector(myGarden);

    for (size_t i = 0; i < myGarden.size(); i++) {
        delete myGarden.at(i);
    }
    return 0;
}