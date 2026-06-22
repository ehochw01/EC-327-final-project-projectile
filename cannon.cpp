#include "Cannon.h"
#include "raylib.h"
#include <cmath>   // cosf, sinf

const float AMAX = 90;
const float AMIN = -90;
const float EMAX = 85;
const float EMIN = 0;
const float PMAX = 100;
const float PMIN = 0;

Vector3 Cannon::getPivot() const {
    return pivot;
}

// left/right, degrees, range -90 to 90
void incrAzimuth(float frameTime) {
    float temp = _azimuth;
    temp += 60.0f *frameTime;
    if (temp >= AMIN && temp <= AMAX) {
        _azimuth = temp;
    }
}

// left/right, degrees, range -90 to 90
void decrAzimuth(float frameTime) {
    float temp = _azimuth;
    temp -= 60.0f *frameTime;
    if (temp >= AMIN && temp <= AMAX) {
        _azimuth = temp;
    }
}

// up/down, degrees, range 0 to 85
void incrElevation(float frameTime) {
    float temp = _elevation;
    temp += 60.0f *frameTime;
    if (temp >= EMIN && temp <= EMAX) {
        _elevation = temp;
    }
}

void decrElevation(float frameTime) {
    float temp = _elevation;
    temp -= 60.0f *frameTime;
    if (temp >= EMIN && temp <= EMAX) {
        _elevation = temp;
    }
}

void incrElevation(float frameTime) {
    float temp = _lauchSpeed;
    temp += 60.0f *frameTime;
    if (temp >= EMIN && temp <= EMAX) {
        _lauchSpeed = temp;
    }
}

// launch speed m/s, range 0 to 100 (spacebar hold)
void setPower(float p) {
    if (p < 0 or p > 100) {
        return;
    }
    __lauchSpeed  = p;
}

Vector3 Cannon::AimDirection() const {
    float az = azimuth   * DEG2RAD;
    float el = elevation * DEG2RAD;

    return {
        cosf(el) * cosf(az),   // X: downrange
        sinf(el),              // Y: up
        cosf(el) * sinf(az)    // Z: sideways
    };
}

void Cannon::Draw() const {
    // base mount at the origin
    DrawCube({0.0f, 0.5f, 0.0f}, 1.6f, 1.0f, 1.6f, (Color){ 60, 60, 65, 255 }); //dark color cannon

    // barrel: from pivot, out along the aim direction
    Vector3 dir = AimDirection();
    float barrelLen = 3.0f;
    Vector3 barrelEnd = {
        pivot.x + dir.x * barrelLen,
        pivot.y + dir.y * barrelLen,
        pivot.z + dir.z * barrelLen
    };
    DrawCylinderEx(pivot, barrelEnd, 0.35f, 0.28f, 12, (Color){ 40, 40, 45, 255 }); //use drawcylinder from raylib, connect the 2 points
}

void Cannon::Fire(Projectile& ball) const {
    Vector3 dir = AimDirection();

    ball.position = pivot;
    // aim direction * _lauchSpeed 
    ball.velocity = { dir.x * _lauchSpeed, dir.y * _lauchSpeed, dir.z * _lauchSpeed };   /
}

