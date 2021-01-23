//  SpaceStation.cpp
//  Space Robotics Simulator
//  Bader AlAttar



#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <string>
#include "SpaceStation.h"
#include "Astrobee.h"
using namespace std;

SpaceStation::SpaceStation():w(10),l(60){
    cout << "Welcome to the Space Robotics Simulator!" << endl << endl;;
    
    // Define ASCII representation
    // wall -> |_
    // Bot -> &
    // Open -> space
    // Hazard -> Spill S
    //        -> Crate  *
    //        -> High Voltage ^
    
    this->GenerateMap();
    this->Bot = new Astrobee;
    this->StartBot();
    
    //Inputs: up, down, left, right,quit, place/print hazard, manual control
    command = " ";
    while ("q" != command && "Q" != command) {
        this->Step(command);
    }
    
};

SpaceStation::~SpaceStation() {
    delete (Bot);
    Bot = NULL;
}

int SpaceStation::stepnumber=0;

void SpaceStation::GenerateMap() {
    map.resize(l,vector<string>(l," "));
    
    for (int i=0;i<l;i++) { // i is length
        for (int j=0;j<w;j++) { // j is width/height
            
            if(00 == i || l-1 == i || ((10 == i || 15 == i || 25 == i || 30 == i || 40 == i|| 45 == i ) && (j< 3 || j>w-4))) {
                map[i][j] = "|";
            }
            else if ((j== 0 || j == w-1)  && ((i>0&&i<10)  || (i>15&&i<25) || (i>30&&i<40) || (i>45)))  {
                map[i][j] = "-";
            }
            else if (( (2==j||w-3==j) && ((i>10&&i<15)  || (i>25&&i<30) || (i>40&&i<45))) ) {
                map[i][j] = "-";
            }
            else {
                map[i][j] = " ";
            }
        }
    }
    
    this->DisplayMap();
    
}

bool SpaceStation::InValidPosition(int x, int y) {
    if (0 == stepnumber || command == "z" || command == "Z") {
        if (map[x][y] == "&" ||map[x][y] == "*" ||map[x][y] == "S" ||map[x][y] == "^" || x <1 || x>l-2 || y< 1 || y >w-3 ||
            (( (x>9 && x <16) || (x>24 && x <31) || (x>39 && x <46) ) && ( y <3 || y > 6) ) ) {
            
            //(x>9&&x<16 && (y<3||y>6) ) || (x>24&&x<31 && (y<3||y>6) ) || (x>39&&x<46 && (y<3||y>6) )) {
            return true;
        }
        else { return false;}
    }
    else {
        if (map[x][y] == " " || map[x][y] == "x") {
            return false;
        }
        else {
            return true;
        }
    }
}

void SpaceStation::StartBot() {
    bool invalid = true;
    cout << endl << "To begin, choose a starting position for the Astrobee in the Space Station." << endl;
    cout << "Input an Integer. Decimal values will be truncated." << endl;
    cout << "The Space Station is 10 m wide and 60 m long including the walls." << endl << endl;
    
    while (invalid) {
        cout << "Enter the x position: " << endl;
        string astring = " ";
        getline(cin,astring);
        stringstream(astring) >> this->x0;
        x0 = (x0 >=0) ? x0 : 0;
        x0 = (x0<=l) ? x0 : l-1;
        cout << endl;
        cout << "Enter the y position" << endl;
        getline(cin,astring);
        
        stringstream(astring) >> this->y0;
        y0 = (y0 >=0) ? y0 : 0;
        y0 = (y0<=w) ? y0 : w;
        
        cout << endl;
        
        if (this->InValidPosition(x0, y0)) {
            cout << "Invalid Starting Position." << endl;
            cout << "Input must be an Integer." << endl;
            cout << "Position Must be Inside Space Station." << endl;
            cout << "Walls at front and end are at x = 0 and 59." << endl;
            cout << "Tunnels start and end at x = 10 to 15, 25 to 30, 40 to 45." << endl;
            cout << "Tunnel heights are from y = 0 to 2, and 7 to 9." << endl;
            cout << "Try Again." << endl;
        }
        else {
            
            this->Bot->setxPos(x0);
            this->Bot->setyPos(y0);
            this->map[x0][y0] = "&";
            invalid = false;
            cout << "Starting Position is Valid." << endl << endl;
        }
        
    }
}


void SpaceStation::Step(string command) {
    int xa = this->Bot->getxPos();
    int ya = this->Bot->getyPos();
    bool help = false;
    bool print = false;
    bool canplace = true;
    bool inv = false;
    if (("r" == command || "R" == command) && !InValidPosition(xa+1, ya)) {
        this->UpdateBotLoc(command,xa, ya);
    }
    else if (("l" == command || "L" == command) && !InValidPosition(xa-1, ya)) {
        this->UpdateBotLoc(command,xa, ya);
    }
    
    else if (("u" == command  || "U" == command) && !InValidPosition(xa, ya-1) ) {
        this->UpdateBotLoc(command,xa, ya);
    }
    
    else if (("d" == command || "D" == command) && !InValidPosition(xa, ya+1)) {
        this->UpdateBotLoc(command,xa, ya);
    }
    
    else if("h" == command || "H" == command) {
        help = true;
    }
    
    else if ("z" == command ||  "Z" == command) {
        int xh,yh;
        cout << endl <<  "First, choose the position of the hazard." << endl << endl;
        cout << "X position: ";
        string astring = " ";
        getline(cin,astring);
        stringstream(astring) >> xh;
        xh = (xh >=0) ? xh : 0;
        xh = (xh<=l) ? xh : l-1;
        cout << endl << "Y position: ";
        getline(cin,astring);
        stringstream(astring) >> yh;
        yh = (yh >=0) ? yh : 0;
        yh = (yh<=w) ? yh : w;
        cout << endl;
        canplace = this->PlaceHazard(xh,yh);
    }
    
    else if ("p" == command || "P" == command) {
        print = true;
    }
    
    else if ("m" == command || "M" == command) {
        int xh,yh;
        cout << endl <<  "Input the Goal Position. " << endl << endl;
        cout << "X position: ";
        string astring = " ";
        getline(cin,astring);
        stringstream(astring) >> xh;
        xh = (xh >=0) ? xh : 0;
        xh = (xh<=l) ? xh : l-1;
        cout << endl << "Y position: ";
        getline(cin,astring);
        stringstream(astring) >> yh;
        yh = (yh >=0) ? yh : 0;
        yh = (yh<=w) ? yh : w;
        cout << endl;
        this->Automatic(xh, yh);
    }
    else {
        if (0  != stepnumber) {inv = true;}
    }
    
    cout << endl << endl;
    string c;
    if ("m" != command && "M" != command) {
        this->DisplayMap();
    }
    
    if(help) {
        this->DisplayHelp();
        help = false;
    }
    else if(print) {
        this->PrintHazard();
        print = false;
    }
    else if(!canplace) {
        cout << endl <<  "Unable to Place Hazard Here." << endl << endl;
    }
    else if(inv) {
        cout << endl << "Invalid Input." << endl << endl;
    }
    
    cout << endl <<"Type h at any time to get help on the commands." << endl;
    cout << "Please input Command: ";
    getline(cin,c);
    this->command = c;
    stepnumber++;
    
    
}

void SpaceStation::DisplayMap() const {
    for (int j=0;j<10;j++) {
        for (int i = 0; i < 60; i++) {
            cout << map[i][j];
            if (59 == i) {
                cout << endl;
            }
        }
    }
}

void SpaceStation::DisplayHelp() const {
    cout << endl << "Up: u" << endl << "Down: d" << endl << "Left: l" << endl << "Right: r" << endl <<"Automatic Mode: m" << endl<< "Place Hazard: z" <<  endl << "Print Sensed Hazard Locations: p" << endl << "Quit: q" << endl <<  endl;
}

bool SpaceStation::PlaceHazard(int xh,int yh) {
    if (this->InValidPosition(xh, yh)) {
        return false;
    }
    else {
        cout << "Next, what type of Hazard would you like to place?" << endl;
        cout << endl << "Spill: S" << endl;
        cout << "High Voltage: ^" << endl;
        cout << "Crate: *" << endl;
        cout << endl << "Type: ";
        
        string astring = " ";
        getline(cin,astring);
        if ( "S" == astring || "s" == astring) {
            map[xh][yh] = "S";
        }
        else if ("^" == astring) {
            map[xh][yh] = "^";
        }
        else if ("*" == astring ) {
            map[xh][yh] = "*";
        }
        else {
            cout << "Invalid Hazard Type." << endl;
        }
        
        return true;
    }
}



void SpaceStation::Sense() {
    for (int i=-2; i<3;i++) {
        for (int j=-2;j<3;j++) {
            int xi = this->Bot->getxPos();
            int yi = this->Bot->getyPos();
            
            if (xi+i > 0 && xi + i < l && yi > 0 && yi < w && this->map[xi+i][yi+j] == "S"  ) {
                this->Bot->addHazardLocation(xi+i,yi+j,"S");
            }
            else if (xi+i > 0 && xi + i < l && yi > 0 && yi < w && this->map[xi+i][yi+j] == "*") {
                this->Bot->addHazardLocation(xi+i,yi+j, "*");
            }
            else if(xi+i > 0 && xi + i < l && yi > 0 && yi < w && this->map[xi+i][yi+j] == "^" )  {
                this->Bot->addHazardLocation(xi+i,yi+j,"^");
            }
        }
    }
    
    
}

void SpaceStation::PrintHazard() const {
    cout << endl << "The Following is a List of All Sensed Hazard Locations." <<endl << endl;
    for (int i=1; i<this->Bot->gethazx().size();i++) {
        cout << "[x y] = [" << this->Bot->gethazx()[i] << " " << this->Bot->gethazy()[i] << "] Type: " <<this->Bot->gethazt()[i]  << endl;
    }
}

void SpaceStation::UpdateBotLoc(string move, int xa, int ya) {
    if ("r" == move || "R" == move) {
        map[xa][ya] = " ";
        map[xa+1][ya] = "&";
        this->Bot->moveRight();
        this->Sense();
    }
    else if ("l" == move|| "L" == move ){
        map[xa][ya] = " ";
        map[xa-1][ya] = "&";
        this->Bot->moveLeft();
        this->Sense();
    }
    else if ("u" == move || "U" == move) {
        map[xa][ya] = " ";
        map[xa][ya-1] = "&";
        this->Bot->moveUp();
        this->Sense();
    }
    else if ("d" == move || "D" == move) {
        map[xa][ya] = " ";
        map[xa][ya+1] = "&";
        this->Bot->moveDown();
        this->Sense();
    }
    
}

void SpaceStation::Automatic(int px, int py) {
    if (this->InValidPosition(px, py) || px < 1 || px > 58 || py < 1 || py > 9) {
        cout << "Invalid Cooridnate Waypoint." << endl;
    }
    else {
        this->map[px][py] = "x";
        int xi = this->Bot->getxPos();
        int yi = this->Bot->getyPos();
        int xDist = px - xi;
        int yDist = py - yi;
        while (xDist != 0 ||yDist !=0) {
            
            
            vector<double> P = {0 ,0 ,0 ,0};
            P[0] = (xDist > 0) ? xDist : 0;   // right
            P[1] = (xDist < 0) ? -xDist : 0;   // left
            P[2] = (yDist < 0) ? yDist : 0;   // up
            P[3] = (yDist > 0) ? -yDist : 0;   // down
            
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis1(0, 1.0);
            uniform_real_distribution<> dis2(0, 1.0);
            
            P[0] = P[0] + yDist*dis1(gen);
            P[1] = P[1] + -yDist*dis1(gen);
            
            if ( yi < 4) {
                P[2] = P[2] + 5*xDist*dis2(gen);
                P[3] = P[3] + -5*xDist*dis2(gen);
            }
            
            else if ( yi > 5) {
                P[2] = P[2] + 5*xDist*dis2(gen);
                P[3] = P[3] + -5*xDist*dis2(gen);
            }
            
            
            if (map[xi-1][yi] == "*" ||map[xi-1][yi] == "S" ||map[xi-1][yi] == "^") {
                P[2] = P[2] + 10*xDist*dis1(gen);
                P[3] = P[3] - 10*xDist*dis1(gen);
            }
            else if(map[xi+1][yi] == "*"||map[xi-1][yi] == "S" ||map[xi-1][yi] == "^") {
                P[2] = P[2] + 6*xDist*dis1(gen);
                P[3] = P[3] - 6*xDist*dis1(gen);
            }
            
            
            double sum = P[0] + P[1] + P[2] +P[3];
            for (int i=0;i<P.size();i++) {
                P[i] = P[i]/sum;
            }
            
            for (int i=0; i<4;i++ ) {
                P[i]  = (P[i]>=0 ? P[i] : 0);
                
            }
            
            uniform_real_distribution<> dis3(0.0, 1.0);
            double t = dis3(gen);
            
            if (this->map[xi+1][yi] == "*" && this->map[xi-1][yi] == "*" && this->map[xi][yi+1] == "*" && this->map[xi][yi-1] == "*") {
                cout << "Send Help!" << endl;
                break;
            }
            else {
                if (t < P[0])   {      //   (xDist>0) {
                    if (!this->InValidPosition(xi+1, yi)) {
                        this->UpdateBotLoc("r",xi,yi);
                        this ->DisplayMap();
                    }
                    xi = this->Bot->getxPos();
                    yi = this->Bot->getyPos();
                    xDist = px - xi;
                    yDist = py - yi;
                    
                }
                
                else if(t < P[0] + P[1]) {//(xDist <0) {
                    if (!this->InValidPosition(xi-1, yi)) {
                        this->UpdateBotLoc("l",xi,yi);
                        this->DisplayMap();
                    }
                    xi = this->Bot->getxPos();
                    yi = this->Bot->getyPos();
                    xDist = px - xi;
                    yDist = py - yi;
                }
                else if (t < P[0] +P[1] + P[2]) { //(yDist <0) {
                    if (!this->InValidPosition(xi, yi-1)) {
                        this->UpdateBotLoc("u",xi,yi);
                        this->DisplayMap();
                        
                    }
                    xi = this->Bot->getxPos();
                    yi = this->Bot->getyPos();
                    xDist = px - xi;
                    yDist = py - yi;
                }
                else if (t < P[0] +P[1] + P[2] + P[3]) {
                    if (!this->InValidPosition(xi, yi+1)) {
                        this->UpdateBotLoc("d",xi,yi);
                        this->DisplayMap();
                    }
                    xi = this->Bot->getxPos();
                    yi = this->Bot->getyPos();
                    xDist = px - xi;
                    yDist = py - yi;
                }
                
                else {
                    xDist = 0;
                    yDist = 0;
                }
            }
            
        }
    }
}
