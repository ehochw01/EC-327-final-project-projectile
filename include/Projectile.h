#pragma once 
#include "PhysicsBody.h" 

class Projectile : public PhysicsBody { //inherits from physics body which inherits from entity.
//projectile gets position (from entity), velocity + mass + update method from physicsBody

public:
    float radius{0.3f};    // sphere radius in meters
    Color color{DARKGRAY}; // color of the projectile 
    bool active{false}; //is the ball currently flying? makes sure it starts dormant. The logic for this lives in main
    void Draw() override; // implements the last pure virtual, now class is concrete. 
};



