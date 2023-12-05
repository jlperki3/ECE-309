#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#define GRADES 3

using namespace std;
struct Student {
    string firstName;
    string lastName;
    float studentGrade1;
    float studentGrade2;
    float studentGrade3;
    float averagGrade;
    char letterGrade;
};

int main() {
    //variable declarations
    ifstream inFS;
    ofstream outFS;
    string fileName;
    vector<Student> stud;
    int studCount = 0;
    float midterm1 = 0;
    float midterm2 = 0;
    float midterm3 = 0;

    //file name input from user
    cout << "Enter file name:" << endl;
    cin >> fileName;

    //open user specified file
    inFS.open(fileName);

    if (!inFS.is_open()) {
        cout << "Could not open file: " << fileName << endl;
        return 1;
    }

    //read all student info from file
    while (!inFS.eof()) {
        stud.push_back(Student());
        inFS >> stud[studCount].lastName;
        inFS >> stud[studCount].firstName;
        inFS >> stud[studCount].studentGrade1;
        inFS >> stud[studCount].studentGrade2;
        inFS >> stud[studCount].studentGrade3;
        ++studCount;
        //stud.push_back(Student());
    }

    for (int i = 0; i < studCount; i++) {
        if (stud[i].studentGrade1 == 0) {
            stud.pop_back();
            studCount = studCount -1;
        }
    }

//Compute average grade per student
    for (int i = 0; i < studCount; i++) {
        stud[i].averagGrade = (stud[i].studentGrade1 + stud[i].studentGrade2 + stud[i].studentGrade3) / GRADES;
    }

//Assign letter grades to each student based on exam averages
    for (int j = 0; j < studCount; j++) {

        if (90 <= stud[j].averagGrade) {
            stud[j].letterGrade = 'A';
        }
        if (80 <= stud[j].averagGrade && stud[j].averagGrade < 90) {
            stud[j].letterGrade = 'B';
        }
        if (70 <= stud[j].averagGrade && stud[j].averagGrade < 80) {
            stud[j].letterGrade = 'C';
        }
        if (60 <= stud[j].averagGrade && stud[j].averagGrade < 70) {
            stud[j].letterGrade = 'D';
        }
        if (stud[j].averagGrade < 60) {
            stud[j].letterGrade = 'F';
        }
    }

//Compute the average of each exam
    for (int x = 0; x < studCount; x++) {
        midterm1 += stud[x].studentGrade1;
        midterm2 += stud[x].studentGrade2;
        midterm3 += stud[x].studentGrade3;
    }

    midterm1 = midterm1 / studCount;
    midterm2 = midterm2 / studCount;
    midterm3 = midterm3 / studCount;

//close tsv file
inFS.close();

//Output info to report.txt
//Open file
    outFS.open("report.txt");
    if (!outFS.is_open()) {
        cout << "Could not open file: report.txt" << endl;
        return 1;
    }
//Write to file
    for (int y = 0; y < studCount; ++y) {
        outFS << stud[y].lastName << "\t" << stud[y].firstName << "\t" << stud[y].studentGrade1
              << "\t" << stud[y].studentGrade2 << "\t" << stud[y].studentGrade3
              << "\t" << stud[y].letterGrade << endl;
    }


    outFS << "\nAverages: midterm1 " << fixed << setprecision(2) << midterm1 << ", midterm2 " << midterm2
    << ", final " << midterm3 << endl;

//close txt file
outFS.close();

    return 0;
}