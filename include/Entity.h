#pragma once 
#include "raylib.h" //need this here because we need vector3 class which lives in raylib

class Entity {
    public: 
        Vector3 position{0.0f,0.0f,0.0f}; //every entity has a location in our world

        virtual ~Entity() = default;      //virtual destructor

        virtual void Update(float dt) = 0; //virtual means will be defined in subclasses
        virtual void Draw() = 0;           
        // note: no function bodies in entity itself, so we dont need an entity.cpp entity is purely virtual.


};