#pragma once
#include "raylib.h"
#include "Projectile.h"
#include "Constants.h"
#include "Target.h"

using namespace Constants;

// To fire: call cannon.Fire(ball) on spacebar release.
class Cannon {
public:
    Vector3 AimDirection() const; // (azimuth, elevation) -> unit direction vector
    Vector3 getPivot() const; // pivot point of the cannon getter, where the ball is launched from
    float getLaunchSpeed() const; // current launch speed getter, which is incremented while holding spacebar
    void incrAzimuth(float frameTime); // increments azimuth (left/right) by ROTATION_RATE * frameTime, clamped to [-90, 90]
    void decrAzimuth(float frameTime); // decrements azimuth (left/right) by ROTATION_RATE * frameTime, clamped to [-90, 90]
    void incrElevation(float frameTime); // increments elevation (up/down) by ROTATION_RATE * frameTime, clamped to [0, 85]
    void decrElevation(float frameTime); // decrements elevation (up/down) by ROTATION_RATE * frameTime, clamped to [0, 85]
    void incrLaunchSpeed(float frameTime); // increments launch speed by ROTATION_RATE * frameTime, clamped to [PMIN, PMAX]
    void Draw() const;                  // draws base + barrel along current aim
    void Fire(Projectile& ball);  // launches ball along aim at power


private:
    Vector3 pivot   = {0.0f, 1.0f, 0.0f};   // barrel hinge + launch point
    float _azimuth   = 0.0f;        // left/right, degrees, range -90 to 90
    float _elevation = 25.0f;       // up/down, degrees, range 0 to 85
    float _launchSpeed = PMIN;       // launch speed m/s, range 0 to 100 (spacebar hold)
};