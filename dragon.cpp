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


int typeNameToType(const string typeName){
    if (typeName == "Night Fury" || typeName == "1") return 1;
    if (typeName == "Deadly Nadder" || typeName == "2") return 2;
    if (typeName == "Monstrous Nightmare" || typeName == "3") return 3;
    if (typeName == "Gronckle" || typeName == "4") return 4;
    if (typeName == "Hideous Zippleback" || typeName == "5") return 5;
    return 0;
}

bool hasSpecialChars(const string &s){
    for (char c : s) {
        if (!isalnum(c) && c!=' ' && c!='-' && c!='_')
        return true;
    }
    return false;
}

int countConsecutiveSpaces(const string &s){
    int count = 0;

    for (size_t i = 1; i < s.size(); i++){
        if (s[i] == ' ' && s[i-1] == ' ') count++;
    }
    return count;
}

bool readLine(ifstream &ifs, string &line){
    if (getline(ifs, line))
    return true;
    else
    return false;
}

int readFile(const string filename, Dragon dragons[], int dragonDamages[5], int &N){
    string line;
    string names[MAX_DRAGONS];
    string types[MAX_DRAGONS];
    int temperaments[MAX_DRAGONS];
    int ammoCounts[MAX_DRAGONS];
    string riders[MAX_DRAGONS];

    if (filename.find_last_of('.') == string::npos || filename.substr(filename.find_last_of('.')+1) != "txt") return 2;
    ifstream ifs(filename);
    if (!ifs.is_open()) return 3;

// Read names
    int nameCount = 0;
    size_t pos = 0;

    if (!readLine(ifs, line)) return 4;
    while ((pos = line.find('"', pos)) != string::npos && nameCount < MAX_DRAGONS){
        size_t end = line.find('"', pos+1);
            if (end == string::npos) break;

        names[nameCount++] = line.substr(pos+1, end-pos-1);
        pos = end+1;
}

// Read types
    int typeCount = 0;
    pos = 0;

    if (!readLine(ifs, line)) return 4;
    while ((pos = line.find('"', pos)) != string::npos && typeCount < MAX_DRAGONS){
        size_t end = line.find('"', pos+1);
            if (end == string::npos) break;

        types[typeCount++] = line.substr(pos+1, end-pos-1);
        pos = end+1;
}

// Temperaments
    int tempCount = 0;

    if (!readLine(ifs, line)) return 4;
    size_t start = line.find('['), endb = line.find(']');

    if (start != string::npos && endb != string::npos){
        string vals = line.substr(start+1, endb-start-1);
        stringstream ss(vals);
        string tok;
            while (getline(ss, tok, ';') && tempCount < MAX_DRAGONS) temperaments[tempCount++] = stoi(tok);
}

// Ammo
    int ammoCount = 0;

    if (!readLine(ifs, line)) return 4;
    start = line.find('['); endb = line.find(']');
    if (start != string::npos && endb != string::npos){
        string vals = line.substr(start+1, endb-start-1);
        stringstream ss(vals);
        string tok;
            while (getline(ss, tok, ';') && ammoCount < MAX_DRAGONS) ammoCounts[ammoCount++] = stoi(tok);
}

// Damages
    int dmgCount = 0;

    if (!readLine(ifs, line)) return 4;
    start = line.find('['); endb = line.find(']');
    if (start != string::npos && endb != string::npos){
        string vals = line.substr(start+1, endb-start-1);
        stringstream ss(vals);
        string tok;
            while (getline(ss, tok, ';') && dmgCount < 5) dragonDamages[dmgCount++] = stoi(tok);
}

// Riders
    int riderCount = 0;
    pos = 0;
    if (!readLine(ifs, line)) return 4;
    while ((pos = line.find('"', pos)) != string::npos && riderCount < MAX_DRAGONS){
        size_t end = line.find('"', pos+1);
            if (end == string::npos) break;

        riders[riderCount++] = line.substr(pos+1, end-pos-1);
        pos = end+1;
}

    if (!readLine(ifs, line)) return 4;
        N = stoi(line);
        ifs.close();

// Validate counts
    if (nameCount != N) return 5;
    if (typeCount != N) return 6;
    if (tempCount != N) return 7;
    if (ammoCount != N) return 8;
    if (dmgCount != 5) return 9;
    if (riderCount != N) return 10;

    int totalExtraSpaces = 0;
    int totalTypeSpecials = 0;

    for (int i = 0; i < N; ++i){
        if (hasSpecialChars(names[i])) return 100 + i;
        totalExtraSpaces += countConsecutiveSpaces(names[i]);
        if (hasSpecialChars(types[i])) totalTypeSpecials++;
        if (countConsecutiveSpaces(riders[i]) > 0) return 900 + i;

        dragons[i].dragonNames = names[i];
        dragons[i].dragonTemperament = temperaments[i];
        dragons[i].ammoCounts = ammoCounts[i];
        dragons[i].riderNames = riders[i];
        dragons[i].dragonTypes = typeNameToType(types[i]);
    }
    if (totalTypeSpecials > 0) return 500 + totalTypeSpecials;
    if (totalExtraSpaces > 1) return 1000 + totalExtraSpaces;

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

// WarriorDragon warriorDragonPairs[1000]; 

// Task 3.2

WarriorDragon warriorDragonPairs[1000]; 

void buddyMatching(Dragon dragons[], string warriors[][3]){
    cout << "Warrior      Dragon        Compatibility    Review" << endl;
    bool dragonTaken[200] = {false};  
    float compatibility;      
    int count = 0;
    float maxCompatibility = -1;
    int bestDragonIdx= -1;

    // bool dragonTaken[200] = {false};  
    // float compatibility;      

    for (int i = 0; i < N; i++){
        string WarriorName = warriors[i][0];
        int WarriorSkill = stoi(warriors[i][1]);


        for (int j = 0; j < N; j++){
            if (dragonTaken[j]) continue;
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

    for (int i = 0; i < N; i++){
        if (warriorDragonPairs[i].compatibility >= 4){
            printCompatibilityTable(warriorDragonPairs[i].warriorName, warriorDragonPairs[i].dragonName, warriorDragonPairs[i].compatibility);
        }
    }
    int tempN = min(4, N);
    for (int i = 0; i < tempN; i++) {
        printCompatibilityTable(warriorDragonPairs[i].warriorName, warriorDragonPairs[i].dragonName, warriorDragonPairs[i].compatibility);
    }
}



// Task 4
int IDcell (int x, int y){
    return (x + y) % 5;
}

int timeFromStartToItem (int x, int y){
    return (1 + (x + y*2 ) ) * 5;
}

int timeFromItemToStart (int x, int y){
    return abs (  (x + y * 2) - 1 )* 5;
}

int computeTime(int IDwarriors, int map[10][10]){
    int time = 0;
    int currentX = 0, currentY = 0;
    bool checkStart = false;
    if (map[0][0] == IDwarriors && IDwarriors != IDcell(0, 0)){
        time += timeFromStartToItem(0, 0) + timeFromItemToStart(0, 0);
    } 
    else{
        time += 5;
    }

    // 2) Other cells
    for (currentX = 0; currentX < 10; currentX++){
        if (currentX % 2 == 0){
            int startY = (currentX == 0 ? 1 : 0);
            for (currentY = startY; currentY < 10; currentY++){
                time += 5;
                if (checkStart) {
                    time += timeFromStartToItem(currentX, currentY);
                    checkStart = false;
                }
                if (map[currentX][currentY] == IDwarriors && IDwarriors != IDcell(currentX, currentY) ) {
                    time += timeFromItemToStart(currentX, currentY);
                    checkStart = true;
                }
            }
        } 
        else{
            for (currentY = 9; currentY >= 0; currentY--){
                time += 5;
                if (checkStart) {
                    time += timeFromStartToItem(currentX, currentY);
                    checkStart = false;
                }
                if (map[currentX][currentY] == IDwarriors && IDwarriors != IDcell(currentX, currentY) ) {
                    time += timeFromItemToStart(currentX, currentY);
                    checkStart = true;
                } 
            }
        }
    }

    return time;
}


void computeChallengeTime(string warriors[][3], int map[10][10])
{
    // TODO: Implement this function
    const int K = 4;
    WarriorTime times[100];

    for (int i = 0; i < N; i++){
        times[i].WarriorName = warriors[i][0];
        int IDwarrior = stoi(warriors[i][2]);
        times[i].time = computeTime (IDwarrior, map);
    }

    for (int k = 0; k < N; k++){
        int minIdx = k;
        for (int i = k + 1; i < N; i++) {
            if (times[i].time < times[minIdx].time) {
                minIdx = i;
            }
        }
        swap(times[k], times[minIdx]);
    }
    
    cout << left << setw(15) << "Warrior" << "Total time (secs)" << endl;

    int tempN = min(K, N);
    for (int i = 0; i < tempN; i++){
         cout << left << setw(15) << times[i].WarriorName << times[i].time << endl;
    }
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

pair <int, int> save[500];
int k = 0;
bool hasKey = false;


void findHeritageLocation(int map[10][10], int &heritageX, int &heritageY){
    // TODO: Implement this function
    for (int i = 0; i < 10; i++){
        int minValueRow= map[i][0]; 
        int minCol = 0;

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
    int maxSum = -1;
    int centerX = -1;
    int centerY = -1;

    for (int i = 1; i < 9; i++){
        for (int j = 1; j < 9; j++){
            int sum = 0;
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
    timeIllusionDragonX = 0;
    timeIllusionDragonY = 0;

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
            for (int j = 8; j > 0; j--){  
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


int calculateHP(int &x, int &y, int map[10][10], int warriorDamage, int &HP, const SpecialPoints &sp){
    int CellValue = map[x][y]; 

    // Normal Ground Cell or Heritage Cell or Key Cell
    if (  ( (CellValue == 0) || (x == sp.keyX && y == sp.keyY) || ( x == sp.heritageX && y == sp.heritageY ) ) ){
        return HP;  
    }

    // Dragons Cell
    if (CellValue >= 1 && CellValue <= 200){
        // Time Illusion Dragon
        if ( x == sp.timeIllusionDragonX && y == sp.timeIllusionDragonY){
            if (warriorDamage < CellValue){
                HP -= 2;
                if (x > 0){
                    --x;
                    save[k++] = make_pair(x, y);
                } 
                else{
                    x = 0;
                    y = 0;
                }
            }
        }
        // ChaosReversing Dragon
        else if (x == sp.reversingDragonX && y == sp.reversingDragonY){
            if (warriorDamage < CellValue){
                HP -= 2;
                swap(x, y);

            }
        }
        // Baby Dragon
        else{
            if (warriorDamage < CellValue){
                HP --;
            }
        }      
    }

    return HP;  
}

int calculateTime(int &x, int &y, int map[10][10], int warriorDamage, int totalTime, const SpecialPoints &sp){

    if (map[x][y] == 0) {
        return 2;
    }
    int CellValue = map[x][y];
    if ( (x == sp.keyX && y == sp.keyY) || ( x == sp.heritageX && y == sp.heritageY ) ) {
        return 2;
    }

    // Dragons Cell
    else if (CellValue >= 1 && CellValue <= 200){
        // Special Dragons
        if ((x == sp.timeIllusionDragonX && y == sp.timeIllusionDragonY) || (x == sp.reversingDragonX && y == sp.reversingDragonY)){
            return 10;
        } 
        // Normal Dragon
        else{
            return 5;
        }
    }
    // Normal Cell
    else{
        return 2;
    }
    return totalTime;
}

pair<int, int> ForwardorBackward(int &x, int &y, int destinationX, int destinationY){
    int dir = (x % 2 == 0) ? 1 : -1;
    bool goingForward = (dir == 1)
        ? (x < destinationX || (x == destinationX && y < destinationY))
        : (x < destinationX || (x == destinationX && y > destinationY));
    if (goingForward) {
        if ((dir == 1 && y < 9) || (dir == -1 && y > 0)) y += dir;
        else ++x;
    } else {
        if ((dir == -1 && y < 9) || (dir == 1 && y > 0)) y -= dir;
        else --x;
    }
    
        return pair < int, int>(x, y);
}

bool moveAndCalculate(int &StartX, int &StartY, int destinationX, int destinationY, int map[10][10],
    int warriorDamage, int &HP, int &totalTime, const SpecialPoints &sp){
    
    auto newPos = ForwardorBackward(StartX, StartY, destinationX, destinationY); 
        StartX = newPos.first;
        StartY = newPos.second; 
        int oldStartX = StartX;
        int oldStartY = StartY;
        save[k++] = newPos;
        totalTime += calculateTime(StartX, StartY, map, warriorDamage, totalTime, sp);
        // cout<< "Current Position: (" << StartX << "," << StartY << ")\n";
        // cout << "Total Time: " << totalTime << " (sec)\n";
        HP = calculateHP(StartX, StartY, map, warriorDamage, HP, sp);

        map[oldStartX][oldStartY] = 0;

        if (HP <= 0) {
            return false;  
        }

        if (StartX == sp.keyX && StartY == sp.keyY) {
            hasKey = true;  
        }

        return true;
}


void totalTime(int map[10][10], int warriorDamage, int HP) {
    // TODO: Implement this function
    k = 0;
    SpecialPoints sp;
    int total_Time = 0;
    int StartX = 0, StartY = 0;
    bool defeated = false;

    findHeritageLocation (map, sp.heritageX, sp.heritageY);
    findKeyLocation (map, sp.keyX, sp.keyY);
    findTimeIllusionDragon (map, sp.timeIllusionDragonX, sp.timeIllusionDragonY);
    findChaosReversingDragon (map, sp.reversingDragonX, sp.reversingDragonY);

    // cout << "Heritage Location: (" << sp.heritageX << "," << sp.heritageY << ")\n";
    // cout << "Key Location: (" << sp.keyX << "," << sp.keyY << ")\n";
    // cout << "Time Illusion Dragon Location: (" << sp.timeIllusionDragonX << "," << sp.timeIllusionDragonY << ")\n";
    // cout << "Chaos Reversing Dragon Location: (" << sp.reversingDragonX << "," << sp.reversingDragonY << ")\n";

    while ((StartX != sp.keyX || StartY != sp.keyY)){
        if (!moveAndCalculate(StartX, StartY,sp.keyX, sp.keyY, map, warriorDamage, HP, total_Time, sp)){
            defeated = true;
            break;
        }
    }

    while (StartX != sp.heritageX || StartY != sp.heritageY){
        if (!moveAndCalculate(StartX, StartY, sp.heritageX, sp.heritageY, map, warriorDamage, HP, total_Time, sp)){
            defeated = true;
            break;
        }
    } 

    if (defeated){
        cout << "Warrior defeated! Challenge failed!\n";
    } 
    else{
        // cout << "Challenge succeeded!\n";
    }
        
    cout << "Total time: "   << total_Time + 5 << " (sec)\n";
    cout << "Remaining HP: " << HP        << "\n";
        
    cout << "Path: ";

    for (int i = 0; i < k; i++) {
        cout << "(" << save[i].first << "," << save[i].second << ")";
    }
    cout << endl;
}
                

// // ////////////////////////////////////////////////
// // /// END OF STUDENT'S ANSWER
// // ////////////////////////////////////////////////
