#include "FamilySet.h"

FamilySet::FamilySet()
{
    // Your code here
    iterCount = 0;
}

FamilySet::FamilySet(string file)
{
    ifstream myFile(file);
    
    // Your code here
    string command;
    myFile >> command;
    masterList.push_back(command);
    
    iterCount++;
    myFile.close();
}

FamilySet::FamilySet(string file, int len)
{
    ifstream myFile(file);
    
    if (!myFile) {
        cout << "File not found!" << endl;
        exit(0);
    }
    
    // Your code here
    string command;
    
    while (!myFile.eof()) {
        myFile >> command;
        if (command.length() == len) {
            masterList.push_back(command);
            iterCount++;
        }
        
    }
    cout << "Closing File" << " Size: " << masterList.size() << endl;
    cout << "\n";
    myFile.close();
}

FamilySet::~FamilySet()
{
    // Optional for this assignment
}
//string letter
void FamilySet::filterFamilies(char letter, string guessPattern)
{
    // The first step is to clear dictionaries to prepare
    // for the new filter based on the letter and pattern
    dictionaries.clear();
    
    // For each word in the master list, you need to classify
    // what family is part of based on the letter and pattern.
    // If you can find letter in the word, then we need to
    // create the new family.
    // Otherwise, if the letter does not exist in the word, then
    // the family is simply the guessPattern.
    // Example 1:Suppose letter is "a", word is "ally", and
    //           guessPattern is ***y.
    //           In this case, the family is a**y. Once this
    //           is determined, then "ally" can be added to
    //           the "a**y" dictionary.
    // Example 2:Suppose letter is "a", word is "cool", and
    //           guessPattern is ***y.
    //           In this case, the family is ***y and "cool"
    //           would be added to the ***y dictionary.
    string temp;
    for (vector<string>::iterator it = masterList.begin(); it != masterList.end(); it++) {
        temp = *it;
        
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] != letter) {
                temp[i] = '*';
            }
        }
        
        for (int i = 0; i < temp.size(); i++) {
            if(guessPattern[i] != '*') {
                temp[i] = guessPattern[i];
            }
        }
    
        if (dictionaries.find(temp) == dictionaries.end()) {
            vector<string> family;
            family.push_back(*it);
            dictionaries.insert(pair<string, vector<string> > (temp, family));
        }
        else {
            dictionaries[temp].push_back(*it);
        }
    }
    
    
    
}

void FamilySet::setFamily(string family)
{
    // This updates the master list.  The new master list
    // should contain the words within the dictionary for family.
    // dictionaries should be cleared after updating the master list.
    
    // Your code here
    masterList = getFamily(family);
}

vector<string> FamilySet::getFamily(string family)
{
    // Returns the dictionary associated with family.
    vector<string> temp;
    // Your code here
    unordered_map<std::string, vector<string> >::const_iterator got = dictionaries.find(family);
    temp = got->second;
    return temp;
}

string FamilySet::getRandomWord()
{
    // Returns random word from master list
    int temp = rand()%masterList.size();
    return masterList[temp];
}

long FamilySet::numWords()
{
    // This should return the number of words in the master list
    return  masterList.size();;
}

long FamilySet::numFamilies()
{
    // This should return how many families are in dictionaries
    // (Note FAMILIES, not words)
    
    return dictionaries.size();
}

//Didnt use
void FamilySet::resetFamilyIter()
{
    // The iterator should return each family from
    // dictionaries (Note, it should returns the family,
    // not the words).
    // The resetFamilyIter function should be starting
    // iterator for dictionaries.
   // unordered_map<string, vector<string> >::const_iterator it = dictionaries.begin();
    
    
    // Your code here
}

//Didnt use
bool FamilySet::hasNext() {
    // Returns true as long as there is another family to return
    return true;
}

string FamilySet::getNextFamily()
{
    // Returns the next family using the unordered_map iterator.
    
    // Your code here
    long familyLen = 0;
    string maxFamily;
    
    for (auto it = dictionaries.begin(); it != dictionaries.end(); it++) {
        if (it->second.size() > familyLen) {
            familyLen = it->second.size();
            maxFamily = it->first;
        }
    }
    
    return maxFamily;
}

//Didnt use
int FamilySet::familySize(string family)
{
    // Returns the size of the dictionary of family.
    
    return 0;
}

void FamilySet::displayDebug() {
    
    cout << "\n";
    
    for (auto it = dictionaries.begin(); it != dictionaries.end(); it++) {
        cout << "Fam: " << it->first << "      Size: " << it->second.size() << endl;;
    }
}


