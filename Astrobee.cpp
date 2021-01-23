//
//  Astrobee.cpp
//  Space Robotics Simulator
//  Bader AlAttar


#include <stdio.h>
#include "Astrobee.h"
#include <vector>
#include <string>
using namespace std;
Astrobee::Astrobee() {
    xPos = 5;
    yPos = 5;
    hazx.push_back(0);
    hazy.push_back(0);
    hazt.push_back(" ");
}

void Astrobee::setxPos(int x) {
    this->xPos = x;
}

void Astrobee::setyPos(int y) {
    this->yPos = y;
}

int Astrobee::getxPos() const {
    return this->xPos;
}

int Astrobee::getyPos() const {
    return this->yPos;
}

void Astrobee::moveUp() {
    this->yPos = this->yPos - 1;
}

void Astrobee::moveDown() {
    this->yPos = this->yPos + 1;
}

void Astrobee::moveLeft() {
    this->xPos = this->xPos - 1;
}

void Astrobee::moveRight() {
    this->xPos = this->xPos + 1;
}

vector<int> Astrobee::gethazx() const {
    return hazx;
}

vector<int> Astrobee::gethazy() const {
    return hazy;
}

vector<string> Astrobee::gethazt() const {
    return hazt;
}

void Astrobee::addHazardLocation(int x, int y, string t) {
    int check= 0;
    for(int i=0;i < this->hazy.size();i++) {
        if (hazx[i] != x || hazy[i] != y) {
            check++;
        }
    }
    if (check == this->hazy.size()) {
        this->hazx.push_back(x);
        this->hazy.push_back(y);
        this->hazt.push_back(t);
    }
}
