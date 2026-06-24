#include "Target.h"
#include "raylib.h"
#include <cmath>   // sqrtf

void Target::Draw() {
    // flat vertical disk facing the cannon: the axis runs along the downrange X axis,
    // and the disk is thin (0.2m) so the ball passes through it in a single frame.
    Vector3 faceFront = { position.x - 0.1f, position.y, position.z };
    Vector3 faceBack  = { position.x + 0.1f, position.y, position.z };

    /* bullseye: concentric rings drawn outer-to-inner, alternating the target's
       current color with white so each ring stays visible against the last.
       each smaller ring is nudged slightly toward the camera (-x) so the rings
       aren't perfectly coplanar, which otherwise causes z-fighting/moire flicker. */
    const int kRingCount = 5;
    for (int i = 0; i < kRingCount; i++) {
        float ringRadius = radius * (1.0f - i * 0.2f);
        Color ringColor = (i % 2 == 0) ? color : WHITE;
        float offset = i * 0.15f;
        Vector3 ringFront = { faceFront.x - offset, faceFront.y, faceFront.z };
        Vector3 ringBack  = { faceBack.x - offset, faceBack.y, faceBack.z };
        DrawCylinderEx(ringFront, ringBack, ringRadius, ringRadius, 24, ringColor); //24 sides = smooth disk
    }

    DrawCylinderWiresEx(faceFront, faceBack, radius, radius, 24, BLACK);
};

void Target::Update(float dt) {
    // Targets are static, so no update logic is needed
};

void Target::Shrink() {
    radius -= 1.0f; // shrink the target by 1 meter
    /* bullseye shouldn't shrink below the ball's own radius (0.3m), 
    or the ball would be bigger than the bullseye it's aiming for */
    const float kMinRadius = 1.5f;   // 0.3m ball radius / 0.2 bullseye fraction
    if (radius < kMinRadius) {
        radius = kMinRadius;
    }
}

void Target::ChangeColor() {
    /* standard raylib colors, picked so the target stays visible against the
       grass and sky: no GREEN/LIME/DARKGREEN, no SKYBLUE/BLUE */
    ColorIndex = (ColorIndex + 1) % (sizeof(kPalette));
    color = kPalette[ColorIndex];
}

int Target::CheckHit(Vector3 prevBallPos, Vector3 ballPos, float ballRadius) const {
    // did the ball cross the disk's plane (x = position.x) this frame, moving downrange?
    // checking the sign change between last frame and this one means we only fire once.
    bool crossedPlane = (prevBallPos.x <= position.x && ballPos.x >= position.x);
    if (!crossedPlane) return 0;

    // was the crossing point inside the disk face? measure radial distance in the Y-Z plane.
    float dy = ballPos.y - position.y;
    float dz = ballPos.z - position.z;
    float dist = sqrtf(dy * dy + dz * dz);
    float reach = radius + ballRadius;
    if (dist > reach) return 0; // crossed the plane but missed the disk entirely

    // map the hit onto the same 5 bullseye bands drawn in Draw()
    if (dist > radius * 0.8f) return 1;
    if (dist > radius * 0.6f) return 2;
    if (dist > radius * 0.4f) return 3;
    if (dist > radius * 0.2f) return 4;
    return 5;
};

bool Target::Missed(Vector3 prevBallPos, Vector3 ballPos, float ballVelocityX) const {
    // flew past: crossed the downrange plane this frame (CheckHit covers the on-disk hit case)
    bool crossedPlane = (prevBallPos.x <= position.x && ballPos.x >= position.x);
    if (crossedPlane) return true;

    // fell short: still behind the target and no longer moving toward it. since wind is the
    // only thing accelerating x and it's constant for the whole shot, the ball can never make
    // it to the target's plane from here, so the shot is a guaranteed miss.
    if (ballPos.x < position.x && ballVelocityX <= 0.0f) return true;

    return false;
};