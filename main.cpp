/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Summer 2025
* Date: 13.07.2025
*/

// The library here is concretely set, students are not allowed to include any other libraries.

#include "dragon.h"

void sampleTest(string filename = "input/tnc_tc_12_input.txt", string outputFile = "tnc_tc_01_output.txt") {
    // freopen(outputFile.c_str(), "w", stdout); 
    const string inputFile = filename;

    int result = readFile(inputFile, dragons, dragonDamages, N);
    if (result != 1) {
        cout << "Error code: " << result << endl;
        return;
    }

    cout << "File read successfully." << endl;
    cout << "Number of dragons: " << N << endl;
    
    // Display detailed dragon statistics
    // displayDragonStats(dragons, dragonDamages, N);
}
int main() {
    string fighters_15[5][3] ={
    {"Hiccup", "8","0"},
    {"Astrid", "7", "1"},
    {"Snotlout", "9","2"},
    {"Fishlegs", "6","3"},
    {"Ruff&Tuff", "7","4"},
    };

    int map_15[10][10] ={
    {11, 20, 30, 40, 50,
    60, 70, 80, 90, 100},
    {15, 25, 35, 45, 55,
    65, 75, 85, 1, 105},
    {12, 22, 32, 42, 52,
    62, 72, 82, 10, 175},
    {118, 128, 138, 50,
    58, 68, 78, 88, 98,108},
    {14, 24, 34, 44, 54,
    64, 74, 84, 94, 104},
    {19, 29, 39, 49, 59,
    33, 79, 89, 99, 109},
    {11, 21, 14, 41, 51,
    61, 71, 81, 91, 101},
    {16, 26, 36, 46, 56,
    66, 76, 186, 96, 106},
    {17, 27, 37, 47, 57,
    67, 196, 87, 90, 107},
    {13, 23, 33, 43, 53,
    63, 73, 153, 93, 22}};
    computeChallengeTime(fighters_15, map_15);
    return 0;
}
