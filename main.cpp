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
int map_19[10][10] = {
{10, 20, 30, 40, 50, 60,
70, 80, 90, 100},
{15, 25, 35, 45, 55, 65,
75, 85, 95, 105},
{12, 22, 32, 42, 52, 62,
72, 82, 92, 175},
{118, 128, 138, 50, 58, 68,
78, 88, 98, 108},
{14, 24, 34, 44, 54, 64,
74, 84, 94, 104},
{19, 29, 39, 49, 59, 69,
79, 89, 99, 109},
{11, 21, 31, 41, 51, 61,
71, 81, 91, 101},
{16, 26, 36, 46, 56, 66,
76, 186, 96, 106},
{17, 27, 37, 47, 57, 67,
196, 87, 90, 107},
{11, 23, 33, 43, 53, 63,
73, 153, 93, 170}};
int playerDamage_19 = 150;
totalTime(map_19,
    
playerDamage_19, 20);



    return 0;
}
