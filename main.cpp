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
 cout << readFile("tnc_tc_12_input.txt", dragons, dragonDamages, N) << endl;

  string fighters_18[5][3] = {
      {"Valka", "8", "1"},
      {"Eret", "5", "2"},
      {"Stoick", "10", "3"},
      {"Grimmel", "7", "0"},
      {"Spitelout", "6", "4"},
  };

  int teamDamage_18[5];
  fighterDamage(dragons, fighters_18, teamDamage_18);
    return 0;
}
