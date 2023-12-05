//
// Created by Josh Perkins on 4/14/23.
//

#ifndef HW5_PLANT_H
#define HW5_PLANT_H

#include <string>
using namespace std;

class Plant {
public:
    virtual ~Plant();

    void SetPlantName(string userPlantName);

    string GetPlantName() const;

    void SetPlantCost(int userPlantCost);

    int GetPlantCost() const;

    virtual void PrintInfo() const;

protected:
    string plantName;
    int plantCost;
};

#endif //HW5_PLANT_H
