#include "turtle.h"

#define _USE_MATH_DEFINES
#include <math.h>

constexpr float radians(float deg) {
    return deg * (float)M_PI / 180.0f;
}

Turtle::Turtle(uint32_t numpens, uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle,
               float _d)
    : mWidth(width), mHeight(height), mTurnAngle(radians(_angle)), mEdgeLength(_d) {

    mPens.resize(numpens, {true, (float)startposx, (float)startposy, 0, {255, 0, 0}});
}

float Turtle::GetD() const {
    return mEdgeLength;
}

void Turtle::SetD(float newd) {
    mEdgeLength = newd;
}

void Turtle::SetPenPos(uint32_t penidx, int x, int y) {
    if (penidx < mPens.size()) {
        mPens[penidx].xpos = x;
        mPens[penidx].ypos = y;
    }
}

void Turtle::SetAngle(uint32_t penidx, float a) {
    if (penidx < mPens.size()) {
        mPens[penidx].angle = 0;
    }
}

void Turtle::MoveForward(uint32_t penidx) {

    if (penidx < mPens.size()) {
        auto &pen = mPens[penidx];

        float newx = pen.xpos + mEdgeLength * cosf(pen.angle);
        float newy = pen.ypos + mEdgeLength * sinf(pen.angle);

        if (pen.pendown) {
            DrawLine((int)pen.xpos, (int)pen.ypos, (int)newx, (int)newy, pen.rgb);
        }

        pen.xpos = newx;
        pen.ypos = newy;
    }
}

void Turtle::Turn(uint32_t penidx, float rads) {
    if (penidx < mPens.size()) {
        mPens[penidx].angle += rads;
    }
}

void Turtle::PenUp(uint32_t penidx) {
    if (penidx < mPens.size()) {
        mPens[penidx].pendown = false;
    }
}
void Turtle::PenDown(uint32_t penidx) {
    if (penidx < mPens.size()) {
        mPens[penidx].pendown = true;
    }
}

void Turtle::SetPenColor(uint32_t penidx, uint8_t r, uint8_t g, uint8_t b) {
    if (penidx < mPens.size()) {
        mPens[penidx].rgb[0] = r;
        mPens[penidx].rgb[1] = g;
        mPens[penidx].rgb[2] = b;
    }
}

uint32_t Turtle::GetNumPens() const {
    return mPens.size();
}
