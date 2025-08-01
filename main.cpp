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
    cout <<readFile("tnc_tc_12_input.txt", dragons,dragonDamages, N)<< endl;
    string warriors_14[3][3] = {{"Valka", "10", "0"},{"Eret", "6", "1"},{"Gobber", "4", "2"},};
    buddyMatching(dragons, warriors_14);

    return 0;
}
