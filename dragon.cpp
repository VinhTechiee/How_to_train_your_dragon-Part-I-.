#include "dragon.h"

// ***
// If you don't want to lose a LOT of points, please don't add any libraries here. T_T
// ***

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

//Global variables
Dragon dragons[MAX_DRAGONS];
int dragonDamages[5] = {0, 0, 0, 0, 0};
int N = 0;
int path[200][2];
int pathLen = 0;

int typeNameToType(const string typeName) {
    if (typeName == "Night Fury") return 1;
    if (typeName == "Deadly Nadder") return 2;
    if (typeName == "Monstrous Nightmare") return 3;
    if (typeName == "Gronckle") return 4;
    if (typeName == "Hideous Zippleback") return 5;
    if (typeName == "1") return 1;
    if (typeName == "2") return 2;
    if (typeName == "3") return 3;
    if (typeName == "4") return 4;
    if (typeName == "5") return 5;
    return 0;
}

bool countSpecialCharacters(string name){
    int count = 0;
    for (char c : name)
        if (!isalnum(c) && c != ' ' && c != '-' && c != '_') count++;
    return count;
}

int countBlankSpaces(string name) {
    int count = 0;
    for (int i=1;i<name.length();i++)
        if (name[i] == ' ' && name[i-1] == ' ') count++;
    return count;
}

bool checkMissLine(ifstream &ifs, string &line) {
    if (!getline(ifs, line)){
        ifs.close();
        return true;
    } 
    return false;
}

// Task 1
int readFile(const string filename, Dragon dragons[], int dragonDamages[5], int &N){
    if (filename.substr(filename.find_last_of(".") + 1) != "txt") return 2; 

    ifstream ifs(filename);
    int dragonCount = 0;
    string line;
    string typeNames[MAX_DRAGONS];
    int typeCount = 0;
    int tempCount = 0;
    int ammoCount = 0;
    int damageCount = 0;
    int riderCount = 0;
    if (!ifs.is_open()) return 3;

    checkMissLine(ifs, line);
    
    size_t start = line.find('"');
    while (start != string::npos && dragonCount < MAX_DRAGONS) {
        size_t end = line.find('"', start + 1);
        if (end != string::npos) {
            dragons[dragonCount].dragonNames = line.substr(start + 1, end - start - 1);
            dragonCount++;
            start = line.find('"', end + 1);
        } else {
            break;
        }
    }
    if (checkMissLine(ifs, line)) return 4;

    start = line.find('"');
    while (start != string::npos && typeCount < MAX_DRAGONS) {
        size_t end = line.find('"', start + 1);
        if (end != string::npos) {
            string typeName = line.substr(start + 1, end - start - 1);
            typeNames[typeCount] = typeName;
            typeCount++;
            start = line.find('"', end + 1);
        } else {
            break;
        }
    }

    if (checkMissLine(ifs, line)) return 4;

    start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        string token;
        while (getline(valStream, token, ';') && tempCount < MAX_DRAGONS) {
            if (tempCount < dragonCount) {
                dragons[tempCount].dragonTemperament = stoi(token);
            }
            tempCount++;
        }
    }
    
    if (checkMissLine(ifs, line)) return 4;
    
    start = line.find('[');
    end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        string token;
        while (getline(valStream, token, ';') && ammoCount < MAX_DRAGONS) {
            if (ammoCount < dragonCount) {
                dragons[ammoCount].ammoCounts = stoi(token);
            }
            ammoCount++;
        }
    }

    if (checkMissLine(ifs, line)) return 4;

    start = line.find('[');
    end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        string token;
        while (getline(valStream, token, ';') && damageCount < 5) {
            dragonDamages[damageCount] = stoi(token);
            damageCount++;
        }
    }
    
    if (checkMissLine(ifs, line)) return 4;

    start = line.find('"');
    while (start != string::npos && riderCount < MAX_DRAGONS) {
        size_t nameEnd = line.find('"', start + 1);
        if (nameEnd != string::npos) {
            if (riderCount < dragonCount) {
                dragons[riderCount].riderNames = line.substr(start + 1, nameEnd - start - 1);
            }
            riderCount++;
            start = line.find('"', nameEnd + 1);
        } else {
            break;
        }
    }

    if (checkMissLine(ifs, line)) return 4;

    N = stoi(line);
    ifs.close();

    if (dragonCount != N) return 5;
    if (typeCount != N) return 6; 
    if (tempCount != N) return 7; 
    if (ammoCount != N) return 8; 
    if (damageCount != 5) return 9; 
    if (riderCount != N) return 10; 

    for (int i = 0; i < N; i++) 
        if (countSpecialCharacters(dragons[i].dragonNames)!=0) return (100 + i); 
    
    int count = 0;
    for (int i=0; i < N; i++){
        count += countSpecialCharacters(typeNames[i]);
    } if (count != 0) return (500 + count);

    for (int i = 0; i < N;i++){
        dragons[i].dragonTypes = typeNameToType(typeNames[i]);
    } 

    for (int i = 0; i < N; i++) {
        if (countBlankSpaces(dragons[i].riderNames) > 0) return (900 + i);
    }

    int countBlankInNames = 0;
    for (int i = 0; i < N; i++) {
        countBlankInNames += countBlankSpaces(dragons[i].dragonNames);
    }if (countBlankInNames > 1) return (1000 + countBlankInNames);
    return 1; 
}

// Task 2
string findKthStrongestDragon(Dragon dragons[], int dragonDamages[5], int N, int T){
    float power = 0;
    int index_power[1000];
    int count = 0;
    float Max_power = -1.0;
    int index = -1; 

    for (int i = 0 ; i < N; i++){
        if (dragons[i].dragonTemperament >= T){

            if (dragons[i].dragonTypes == 1){
                power = (dragons[i].ammoCounts * dragonDamages[0] ) + dragons[i].dragonTemperament * 3;
            }
            else if (dragons[i].dragonTypes == 2){
                power = (dragons[i].ammoCounts * dragonDamages[1] ) + dragons[i].dragonTemperament * 2;
            }
            else if (dragons[i].dragonTypes == 3){
                power = (dragons[i].ammoCounts * dragonDamages[2] ) + dragons[i].dragonTemperament;
            }
            else if (dragons[i].dragonTypes == 4){
                power = (dragons[i].ammoCounts * dragonDamages[3] ) + dragons[i].dragonTemperament / 2;
            }
            else if (dragons[i].dragonTypes == 5){
                power = (dragons[i].ammoCounts * dragonDamages[4] * 0.9 ) + dragons[i].dragonTemperament * 1.5;
            }
            
            if (power > Max_power) {
                Max_power = power;
                index = i;  
            }
        }
    }


    if (index == -1) {
        return "None";
    }

    return dragons[index].dragonNames; 
}

// Task 3.1
void compatibilityCheck(Dragon dragons[], string warriorName, int warriorSkill){
    // TODO: Implement this function
    cout << "Warrior      Dragon        Compatibility    Review" << endl;
    float compatibility;
    for (int i = 0; i < N; i++){
        compatibility = (10 - abs(dragons[i].dragonTemperament - warriorSkill)) / 2.0 ;
        printCompatibilityTable(warriorName,dragons[i].dragonNames,compatibility);
    }
}

void printCompatibilityTable(string fighterName, string dragonName, float compatibility){
    string result = (compatibility > 4) ? "Compatible" : "Not Compatible";
    
    cout << left << setw(13) << fighterName
         << setw(14) << dragonName
         << setw(17) << fixed << setprecision(2) << compatibility
         << result << endl;
}


// Task 3.2
struct WarriorDragon{
    string warriorName;   
    string dragonName;    
    float compatibility;
};

WarriorDragon warriorDragonPairs[1000]; 

void buddyMatching(Dragon dragons[], string warriors[][3]){
    cout << "Warrior      Dragon        Compatibility    Review" << endl;
    bool dragonTaken[200] = {false};  
    float compatibility;      
    int count = 0;
    float maxCompatibility = -1;
    int bestDragonIdx= -1;

    for (int i = 0; i < N; i++){
        string WarriorName = warriors[i][0];
        int WarriorSkill = stoi(warriors[i][1]);


        for (int j = 0; j < N; j++){
            compatibility = (10 - abs(dragons[j].dragonTemperament - WarriorSkill)) / 2.0;

            if (compatibility > 4.0 && !dragonTaken[j] && compatibility > maxCompatibility) {
                maxCompatibility = compatibility;
                bestDragonIdx = j;
            }
        }


        if (bestDragonIdx != -1){
            dragonTaken[bestDragonIdx] = true;
            warriorDragonPairs[i].warriorName = WarriorName;
            warriorDragonPairs[i].dragonName = dragons[bestDragonIdx].dragonNames;
            warriorDragonPairs[i].compatibility = maxCompatibility;
        } 
        else{
            warriorDragonPairs[i].warriorName = WarriorName;
            warriorDragonPairs[i].dragonName = "None";
            warriorDragonPairs[i].compatibility = 0;
        }
    }
    int tempN = min(4, N);
    for (int i = 0; i < tempN; i++) {
        printCompatibilityTable(warriorDragonPairs[i].warriorName, warriorDragonPairs[i].dragonName, warriorDragonPairs[i].compatibility);
    }
}


// Task 4
void computeChallengeTime(string warriors[][3], int map[10][10])
{
    // TODO: Implement this function

}


// Task 5.1
void fighterDamage(Dragon dragons[], string warriors[][3], int teamsDamage[]){
    // TODO: Implement this function
    int damage;
    for (int i = 0; i < N; i++){
        int WarriorSkill = stoi(warriors[i][1]);
        damage = (dragonDamages[dragons[i].dragonTypes-1] * dragons[i].ammoCounts) + (WarriorSkill * 5);
        teamsDamage[i]= damage;
        cout << warriors[i][0] << "-" << dragons[i].dragonNames << ": damage = " << damage << endl;
        }
}

// Task 5.2
void findHeritageLocation(int map[10][10], int &heritageX, int &heritageY){
    // TODO: Implement this function
    for (int i = 0; i < 10; i++){
        int minValueRow= map[i][0]; 
        int minCol=0;

        for (int j = 0; j < 10; j++){
            if (minValueRow >  map[i][j]){
                minValueRow = map[i][j];
                minCol= j;
            }        
        }

        bool isSaddle = true;
        for (int k = 0; k < 10; k++){
            if (map[k][minCol] > minValueRow){
                isSaddle = false;
                break;
            }
        }


        if (isSaddle){
            heritageX = i;
            heritageY = minCol;
            return;
        }
    }
}


void findKeyLocation(int map[10][10], int &keyX, int &keyY){
    int sum=0;
    int maxSum = -1;
    int centerX = -1;
    int centerY = -1;

    for (int i = 1; i < 9; i++){
        for (int j = 1; j < 9; j++){
            for (int di = -1; di <= 1; di++){
                for (int dj = -1; dj <= 1; dj++){
                    sum += map[i+di][j+dj];
                }
            }

            if (sum > maxSum){
                maxSum = sum;
                centerX = i;
                centerY = j;
            }
        }
    }
    keyX = centerX;
    keyY = centerY;
}


void findTimeIllusionDragon(int map[10][10], int &timeIllusionDragonX, int &timeIllusionDragonY) {
    int maxVal = map[0][0];
    timeIllusionDragonX = -1;
    timeIllusionDragonY = -1;

    for (int j = 0; j < 10; j++){
        if (map[0][j] > maxVal){
            maxVal = map[0][j];
            timeIllusionDragonX = 0;
            timeIllusionDragonY = j;
        }
        if (map[9][j] > maxVal){
            maxVal = map[9][j];
            timeIllusionDragonX = 9;
            timeIllusionDragonY = j;
        }
    }

    for (int i = 1; i < 9; i++){
        if (map[i][0] > maxVal){
            maxVal = map[i][0];
            timeIllusionDragonX = i;
            timeIllusionDragonY = 0;
        }
        if (map[i][9] > maxVal){
            maxVal = map[i][9];
            timeIllusionDragonX = i;
            timeIllusionDragonY = 9;
        }
    }
}


void findChaosReversingDragon(int map[10][10], int &reversingDragonX, int  &reversingDragonY){
    int peakVal = -1;
    reversingDragonX = -1;
    reversingDragonY = -1;

    for (int i = 1; i < 9; ++i){ 

        // Even row: Go from left to right 
        if (i % 2 == 0) { 
            for (int j = 1; j < 9; ++j) {
                if (map[i][j] > map[i-1][j] && map[i][j] > map[i+1][j] && map[i][j] > map[i][j-1] && map[i][j] > map[i][j+1]) {

                    if (map[i][j] >= 1 && map[i][j] <= 200 && peakVal < map[i][j]){
                        peakVal = map[i][j];
                        reversingDragonX = i;
                        reversingDragonY = j;
                    }
                }
            }
        } 

        // Odd row: Go from right to left
        else{
            for (int j = 8; j > 0; --j){  
                if (map[i][j] > map[i-1][j] && map[i][j] > map[i+1][j] && map[i][j] > map[i][j-1] && map[i][j] > map[i][j+1]) {

                    if (map[i][j] >= 1 && map[i][j] <= 200 && peakVal < map[i][j]){
                        peakVal = map[i][j];
                        reversingDragonX = i;
                        reversingDragonY = j;
                    }
                }
            }
        }
    }
}

void swapPosition(int &x, int &y) {
    int temp = x;
    x = y;  
    y = temp;
}


int CalculateHP(int &x, int &y, int map[10][10], int warriorDamage, int &HP, int timeIllusionDragonX, int timeIllusionDragonY, int reversingDragonX, int reversingDragonY, int keyX, int keyY, int heritageX, int heritageY){
    int nextCellValue = map[x][y]; 

    // Normal Ground Cell or Treasure Cell or Key Cell
    if ( (nextCellValue == 0) || (x == keyX && y == keyY) || ( x == heritageX && y == heritageY ) ) {
        return HP;  
    }

    // Dragon Cell
    if (nextCellValue >= 1 && nextCellValue <= 200) {
        
        if ( x == timeIllusionDragonX && y == timeIllusionDragonY){
            if (warriorDamage < nextCellValue){
                HP -= 2;
                swapPosition (x, y);
                if (HP <= 0) {
                    cout << "Warrior defeated! Challenge failed!" << endl;
                    return HP;  
                }
            }
        }
        else if (x == reversingDragonX && y == reversingDragonY){
            if (warriorDamage < nextCellValue){
                HP -= 2;
                if (HP <= 0) {
                    cout << "Warrior defeated! Challenge failed!" << endl;
                    return HP;  
                }
            }
        }
        else {
            if (warriorDamage < nextCellValue){
                HP --;
                if (HP <= 0) {
                    cout << "Warrior defeated! Challenge failed!" << endl;
                    return HP;  
                }
            }
        }      
    }
    return HP;  
}

int CalculateTime(int &x, int &y, int map[10][10], int warriorDamage, int &totalTime, int timeIllusionDragonX, int timeIllusionDragonY, int reversingDragonX, int reversingDragonY, int keyX, int keyY, int heritageX, int heritageY){
    int nextCellValue = map[x][y];

    // Normal Ground Cell or Treasure Cell or Key Cell
    if ( (nextCellValue == 0) || (x == keyX && y == keyY) || ( x == heritageX && y == heritageY ) ) {
        totalTime += 2;
    }

    // Dragon Cell
    if (nextCellValue >= 1 && nextCellValue <= 200){
        if ((x == timeIllusionDragonX && y == timeIllusionDragonY) || (x == reversingDragonX && y == reversingDragonY)){
            totalTime += 10;  
        } else {
            totalTime += 5;   
        }
    }
    return totalTime;
}


void ForwardorBackward(int &x, int &y, int &destinationX, int &destinationY){

    // Move clockwise
    if ( x < destinationX || y < destinationY){
        while (x != destinationX){
            if (x % 2 == 0) {
                x++;  
            }
            else{  
                x--;  
            }
        }
        
        while (y != destinationY){
            if (y % 2 == 0){ 
                y++;  
            } 
            else{  
                y--; 
            }
        }
    }

    // Move counterclockwise
    else if (x > destinationX || y > destinationY){
        while (x != destinationX){
            if (x % 2 == 0){
                x--;  
            }
            else{  
                x++;  
            }
        }

        while (y != destinationY){
            if (y % 2 == 0){ 
                y--;  
            } 
            else{  
                y++; 
            }
        }
    }

    else{
        return;
    }
    return;
}


pair <int, int> save[500];
int k=0;

// void totalTime(int map[10][10], int warriorDamage, int HP) {
//     // TODO: Implement this function
//     int keyX, keyY;
//     int heritageX, heritageY;
//     int timeIllusionDragonX, timeIllusionDragonY;
//     int reversingDragonX, reversingDragonY;

//     int total_Time = 0;
//     int StartX = 0, StartY = 0;

//     bool defeated[10][10] = {false};
//     bool hasKey = false;

//     findHeritageLocation (map, heritageX, heritageY);
//     findKeyLocation (map, keyX, keyY);
//     findTimeIllusionDragon (map, timeIllusionDragonX, timeIllusionDragonY);
//     findChaosReversingDragon (map, reversingDragonX, reversingDragonY);
//     if (!hasKey){
//         for (int i = 0; i < 10; i++){
//             for (int j = 0; j < 10; j++){
//                 int CheckDragon = map [i][j]; 
//                 ForwardorBackward(StartX, StartY, keyX, keyY);
//                 total_Time += CalculateTime(StartX, StartY, map, warriorDamage, total_Time, timeIllusionDragonX, timeIllusionDragonY, reversingDragonX,reversingDragonY, keyX, keyY, heritageX, heritageY);
//                 HP+= CalculateHP(StartX, StartY, map, warriorDamage, total_Time, timeIllusionDragonX, timeIllusionDragonY, reversingDragonY, reversingDragonX,reversingDragonY, keyX, keyY, heritageX, heritageY);
//                 if ((map[StartX][StartY] == 0) || ((StartX == keyX) && (StartY == keyY) || ((StartX == heritageX) && (StartY == heritageY)) ){

//                 }
//                 if ( map[StartX][StartY] >= 1 && map[StartX][StartY] <= 200 ){
//                     if ( StartX == timeIllusionDragonX && StartY == timeIllusionDragonY){
//                         if (!defeated [i][j]) {

//                         }
//                     }
//                     else if ( StartX == reversingDragonX && StartY == reversingDragonY){
//                         if (!defeated [i][j]) {

//                         }
//                         swapPosition(i, j);
//                     }
//                     else{
//                         if (!defeated [i][j]) {

//                         }
//                     }
//                 }
                
//             }
//         }
//     }

//     for (int i=0; i < 10; i++){
//         // Even row: Go from left to right
//         if (i % 2 == 0){
//             for (int j = 0; j < 10; j ++){
//                 save[k++] = {i, j};
//                 int DragonBaby = map[i][j];
//                 if (DragonBaby >= 1 && DragonBaby <= 200 && ( i != keyX && j != keyY) && (i != heritageX && j != heritageY)) {
//                     if (!defeated[i][j]) {
//                         if (warriorDamage < DragonBaby) {
//                             --HP;
//                             if (HP <= 0) {
                                

//                                 for (int idx = 0; idx < k; ++idx) {
                                    
//                                 }

                                
//                                 return;
//                             }
//                         }
//                         defeated[i][j] = true;
//                         total_Time += 5;
//                     } else {
//                         total_Time += 2;
//                     }
//                 } else {
//                     total_Time += 2;
//                 }
//             }
//         } else {
//             // Odd row: Go from right to left
//             for (int j = N-1; j >= 0; --j) {
//                 save[k++] = {i, j};
//                 int DragonBaby = map[i][j];
//                 if (DragonBaby >= 1 && DragonBaby <= 200  && ( i != keyX && j != keyY) && (i != heritageX && j != heritageY)) {
//                     if (!defeated[i][j]) {
//                         if (warriorDamage < DragonBaby) {
//                             --HP;
//                             if (HP <= 0) {
                                
//                                 for (int idx = 0; idx < k; ++idx) {
                                    
//                                 }
                                
//                                 return;
//                             }
//                         }
//                         defeated[i][j] = true;
//                         total_Time += 5;
//                     } else {
//                         total_Time += 2;
//                     }
//                 } else {
//                     total_Time += 2;
//                 }
//             }
//         }
//     }
// }

// // ////////////////////////////////////////////////
// // /// END OF STUDENT'S ANSWER
// // ////////////////////////////////////////////////
