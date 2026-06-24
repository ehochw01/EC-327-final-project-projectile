#pragma once 
#include "PhysicsBody.h"

class Debris : public PhysicsBody {
public:
    float radius{0.5f}; //cube length in meters, change based on visuals
    Color color{}; //set per-piece at spawn time (see emitDebris in main.cpp)
    void Draw() override; // handled in physicsbody
};
