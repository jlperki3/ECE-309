//
// Created by Josh Perkins on 4/14/23.
//

#ifndef HW5_FLOWER_H
#define HW5_FLOWER_H


#include "Plant.h"
#include <string>
using namespace std;

class Flower : public Plant {
public:
    void SetPlantType(bool userIsAnnual);

    bool GetPlantType() const;

    void SetColorOfFlowers(string userColorOfFlowers);

    string GetColorOfFlowers() const;

    void PrintInfo() const;

private:
    bool isAnnual;
    string colorOfFlowers;
};
#endif //HW5_FLOWER_H
