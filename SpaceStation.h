//
//  SpaceStation.h
//  Space Station Simulator
//  Bader AlAttar


#ifndef SpaceStation_h
#define SpaceStation_h

#include <vector>
#include <string>
#include "Astrobee.h"
using namespace std;

class SpaceStation {
    
public:
    // Call constructor to run program
    SpaceStation();
    ~SpaceStation();
    void GenerateMap();
    void DisplayMap() const;
    void DisplayHelp() const;
    void StartBot();
    void Step(string);
    bool PlaceHazard(int,int);
    bool InValidPosition(int,int);
    void PrintHazard() const;
    void UpdateBotLoc(string, int, int);
    
    void Sense();
    void Automatic(int,int);
    
    
private:
    Astrobee* Bot; // Pointer to Astrobee Bot
    vector<vector<string>> map; // 2d Vector of strings for map
    int x0,y0;   // starting position
    string command; // current command
    const int w; // ss width
    const int l; // ss length
    static int stepnumber;
    
    
};
#endif /* SpaceStation_h */
