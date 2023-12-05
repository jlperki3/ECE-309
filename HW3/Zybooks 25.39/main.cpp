#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void PrintMenu();
void ExecuteMenu(char a, string inputString);
int GetNumOfNonWSCharacters(const string inputStringWS);
int GetNumOfWords(const string inputStringWords);
int FindText(string search, const string inputStringFind);
void ReplaceExclamation(string inputStringReplace);
void ShortenSpace(string &inputStringShorten);

int main() {
    string userInput;
    char select = '\0';

// Get user input and display it to the console
    cout << "Enter a sample text:\n" << endl;
    getline(cin, userInput);
    cout << "You entered: " << userInput << "\n" << endl;

    while (select != 'q') {
            PrintMenu();
            cout << "\nChoose an option:";
            cin >> select;
            cin.ignore();
            ExecuteMenu(select, userInput);
            cout << endl;
    }



    return 0;
}

void PrintMenu() {
    cout << "MENU\n" << "c - Number of non-whitespace characters\n" << "w - Number of words\n" <<
    "f - Find text\n" << "r - Replace all !'s\n" << "s - Shorten spaces\n" << "q - Quit" << endl;
}

void ExecuteMenu(char a, string inputString) {
    string searchString;
    string replace;
    switch (a) {
        case 'q':
            break;
        case 'c':
            GetNumOfNonWSCharacters(inputString);
            break;
        case 'w':
            GetNumOfWords(inputString);
            break;
        case 'f':
            cout << "Enter a word or phrase to be found:" << endl;
            getline(cin, searchString);
            FindText(searchString, inputString);
            break;
        case 'r':
            ReplaceExclamation(inputString);
            break;
        case 's':
            ShortenSpace(inputString);
            break;
    }
}

int GetNumOfNonWSCharacters(const string inputStringWS) {
    int stringLength;
    int noSpaceLength;
    stringLength = inputStringWS.length();
    noSpaceLength = stringLength;

    for (int i = 0; i <= stringLength; i++) {
        if (isspace(inputStringWS[i])) noSpaceLength--;
    }
    cout << "Number of non-whitespace characters: " << noSpaceLength << endl;
    return noSpaceLength;

}

int GetNumOfWords(const string inputStringWords) {
    int stringLength;
    int wordCounter = 0;

    stringLength = inputStringWords.length();
    for (int i = 0; i < stringLength; i++) {
        if (!isspace(inputStringWords[i-1])) {
            if (isspace(inputStringWords[i])) wordCounter++;
        }
    }
    wordCounter += 1;
    cout << "Number of words: " << wordCounter << endl;
    return wordCounter;
}

int FindText(string search, const string inputStringFind) {
    int counter = 0;
    int location;
    location = inputStringFind.find(search, 0);
    while (location != string::npos)
    {
        location = inputStringFind.find(search, location + search.size());
        counter++;
    }
    cout << "\"" << search << "\"" << " instances: " << counter << endl;
    return counter;
}

void ReplaceExclamation(string inputStringReplace) {
    for (int i = 0; i <= inputStringReplace.length(); i++) {
        if (inputStringReplace[i] == '!') inputStringReplace[i] = '.';
    }
    cout << "Edited text: " << inputStringReplace << endl;
}

void ShortenSpace(string &inputStringShorten) {
    int length = inputStringShorten.length();
    for (int i = 0; i < length; i++) {
        if (isspace(inputStringShorten[i]) && isspace(inputStringShorten[i + 1]) && inputStringShorten[i + 1] != '\0') {
            inputStringShorten.erase(i + 1, 1);
            length--;
            i--;
        }
    }
    cout << "Edited text: " << inputStringShorten << endl;
}
