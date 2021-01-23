//
//  Astrobee.h
//  Space Robotics Simulator
//  Bader AlAttar

#ifndef Astrobee_h
#define Astrobee_h
#include <vector>
#include <string>
using namespace std;
class Astrobee {
    
public:
    Astrobee();
    
    int getxPos() const;
    int getyPos() const;
    void setxPos(int);
    void setyPos(int);
    
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    //void Sense();
    vector<int> gethazx() const;
    vector<int> gethazy() const;
    vector<string> gethazt() const;
    void addHazardLocation(int,int,string);
    
private:
    int xPos;
    int yPos;
    vector<int> hazx;  // Sensed Hazard x loc
    vector<int> hazy;  // Sensed Hazard y loc
    vector<string> hazt; // Sensed Hazard Type
};
#endif /* Astrobee_h */
