#include <iostream>
#include <vector>
#include "array"
using namespace std;
void smallestNum();

int main() {
    smallestNum();
    return 0;
}

void smallestNum(){
    vector<int> inputData;
    array<int, 2> min;
    int userData;
    int j;
    int itemNumber;
    cout << "Input numbers " << endl;
    cin >> itemNumber;

    for(int x = 0; itemNumber > x; x++) {
        cin >> userData;
        inputData.push_back(userData);
    }
    min[0] = *min_element(inputData.begin(), inputData.end());
    for (auto i = 0; min[0] != inputData[i]; i++) {
        j = i+1;
    }
    inputData.erase(inputData.begin()+j);
    min[1] = *min_element(inputData.begin(), inputData.end());

    cout << min[0] << " and " << min[1] << endl;
}
