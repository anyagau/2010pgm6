//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Program: To output the which states had been hit by hurricanes, as well as hurricanes category 3+
// to console, and to output how many hits of category 3+ to file
// Process: Using multiple functions, it calculates the multiple steps needed to output the data to console
// and file. The program refers to each function to get the data it needs before moving to the next 
// and getting that data until the outputs.
// Results: A console output of the states hit by hurricanes and the total number of hurricanes, as well
// as all the hurricanes category 3 and up. A file output to out.txt that contains the states hit by
// hurricanes, the total hits, as well as all the major hurricane hits.
//
// Class: CS2010
// Section: 100x
// Term: Fall 2024
// Author: Anya Gau
//
// Reflection: The instructions made this assignment a *lot* harder than necessary, simply due to the 
// fact that there was just too many instructions. It was hard to read, and there was a random variable
// repeadtedly mentioned but not used in any capacity, at least that I know of. That was the most challenging
// part of the assignment, other than those it was mostly smooth sailing.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// the constant variables told to be stated, as well as the global variables
const int MAX_STATE = 18;
const string DATA_FILE = "pgm6.txt";
const string STATE_FILE_LOOKUP = "statelookup.txt";
const string OUT_FILE = "out.txt";

ifstream pgm6;
ifstream lookup;
ofstream out;

// intially reads the data
int readHurricaneData(string stateAbbr[], int numHur[], int cat3Hur[], int cat4Hur[], int cat5Hur[]){
    int i;
    int numState;
    numState = 0;
    pgm6.open("pgm6.txt");
    out.open("out.txt");

    for(i = 0; i < MAX_STATE; ++i){
        pgm6 >> stateAbbr[i];
        pgm6 >> numHur[i];
        pgm6 >> cat3Hur[i];
        pgm6 >> cat4Hur[i];
        pgm6 >> cat5Hur[i];

        ++numState;
    }
    if(pgm6.fail()) {
        return -1;
    }
    else {
        return numState;
    }
    
}

// converts abbrevited states to full names
int readStateLookUpTable(string stateAbbr[], string stateNames[]) {
    lookup.open("statelookup.txt");
    int num;
    num = 0;
    int i;

    for (i = 0; i < MAX_STATE; ++i) {
        lookup >> stateAbbr[i];

        if(stateAbbr[i].at(0) == 'N' || 'R' || 'S') {
            getline(lookup, stateNames[i]);
        }
        else {
            lookup >> stateNames[i];
        }

        ++num;
    }

    if(lookup.fail()) {
        return -1;
    }
    else {
        return num;
    }
}

// identifies the state hit by the most hurricanes
int mostHitState(int numHur[], int num){
    int i;
    int maxHur;
    maxHur = numHur[0];
    int maxIndex;

    for(i = 0; i < MAX_STATE; ++i) {
        if (numHur[i] > maxHur) {
            maxHur = numHur[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

// counts how many states have been hit by a cat 5 hurricanes, and how many hurricanes per those states
void statesHitByCat5Hur(string stateNames[], int cat5Hur[], int num){
    int indexOfStateHitByCat5Hur[MAX_STATE];
    int cntState;
    int i;
    int maxHits;
    string stateHits;
    maxHits = cat5Hur[0];

    for(i = 0; i < MAX_STATE; ++i) {
        if(cat5Hur[i] > 0){
            indexOfStateHitByCat5Hur[i] = i;
            ++cntState;
        }
        if(maxHits < cat5Hur[i]) {
            stateHits = stateNames[i];
            maxHits = cat5Hur[i];
        }
    }
    cout << "Among the 18 states, " << cntState << " states were hit with Category 5 hurricanes between 1900 and 2000" << endl;
    for(i = 0; i < MAX_STATE; ++i) {
        if(cat5Hur[i] > 0){
            cout << "- " << stateNames[i] << " with " << cat5Hur[i] << " Category 5 hurricane(s)" << endl;            
        }
    }
    cout << stateHits << " was hit with the most Category 5 hurricanes during this period." << endl;
}

// outputs the data from pgm6.txt to the console, but without the abbreviated states and with proper columns and labels
void printHurricaneData(string stateNames[], int numHur[], int cat3Hur[], int cat4Hur[], int cat5Hur[], int num){
    int i;

    cout << setw(70) << setfill('=') << "" << endl;
    cout << setfill(' ') << left << setw(20) << "State Name" << left << setw(20) << "Hurricane Hits" << left << setw(10);
    cout << "CAT3" << left << setw(10) << "CAT4" << left << setw(10) << "CAT5" << endl;

    for(i = 0; i < MAX_STATE; ++i) {
        cout << left << setw(20) << stateNames[i] << left << setw(20) << numHur[i] << left << setw(10) << cat3Hur[i];
        cout << left << setw(10) << cat4Hur[i] << left << setw(10) << cat5Hur[i] << endl;
    }

}

// I changed the name to prevent confusion since two with the same name were listed in the rubric
// but this outputs the hurricane hits and cat 3+ hits out to a file (out.txt)
void printHurricaneDataFile(string stateNames[], int numHur[], int cat3Hur[], int cat4Hur[], int cat5Hur[], int num, string OUT_FILE){
    out << left << setw(20) << "State Name" << left << setw(30) << "Total Hurricane Hits" << left << setw(10);
    out << "Major Hurricane Hits (Category 3 and above)" << endl;

    int i;

    for (i = 0; i < MAX_STATE; ++i) {
        out << left << setw(20) << stateNames[i] << left << setw(30) << numHur[i] << left << setw(10);
        out << cat3Hur[i] + cat4Hur[i] + cat5Hur[i] << endl;
    }
}

// main, this is where all the magic happens, pulling all the functions together and putting them in order
// as well as stating the variables necessary
int main() {
    string stateAbbr[MAX_STATE];
    string stateNames[MAX_STATE];
    int numHur[MAX_STATE];
    int cat3Hur[MAX_STATE];
    int cat4Hur[MAX_STATE];
    int cat5Hur[MAX_STATE];
    int cntCat3AndAbove[MAX_STATE];
    int num;

    readHurricaneData(stateAbbr, numHur, cat3Hur, cat4Hur, cat5Hur);
    readStateLookUpTable(stateAbbr, stateNames);
    mostHitState(numHur, num);
    printHurricaneData(stateNames, numHur, cat3Hur, cat4Hur, cat5Hur, num);
    statesHitByCat5Hur(stateNames, cat5Hur, num);
    printHurricaneDataFile(stateNames, numHur, cat3Hur, cat4Hur, cat5Hur, num, OUT_FILE);

    return 0;
}