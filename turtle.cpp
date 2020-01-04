#include "turtle.h"

#define _USE_MATH_DEFINES
#include <math.h>

constexpr float radians(float deg) {
    return deg * (float)M_PI / 180.0f;
}

Turtle::Turtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle,
               float _d)
    : mWidth(width), mHeight(height), mTurnAngle(radians(_angle)), mEdgeLength(_d) {

	mPenStack.push_back({ true, (float)startposx, (float)startposy, 0, {255, 0, 0} });
}

float Turtle::GetD() const {
    return mEdgeLength;
}

void Turtle::SetD(float newd) {
    mEdgeLength = newd;
}

void Turtle::SetPenPos(int x, int y) {
    mPenStack.back().xpos = x;
    mPenStack.back().ypos = y;
}

void Turtle::SetAngle(float degrees) {
    mPenStack.back().angle = radians(degrees);
}

void Turtle::MoveForward() {

    auto &pen = mPenStack.back();

    float newx = pen.xpos + mEdgeLength * cosf(pen.angle);
    float newy = pen.ypos + mEdgeLength * sinf(pen.angle);

    if (pen.pendown) {
        DrawLine((int)pen.xpos, (int)pen.ypos, (int)newx, (int)newy, pen.rgb);
    }

    pen.xpos = newx;
    pen.ypos = newy;
}

void Turtle::Turn(float rads) {

    mPenStack.back().angle += rads;
}

void Turtle::PenUp() {
    mPenStack.back().pendown = false;
}
void Turtle::PenDown() {
    mPenStack.back().pendown = true;
}

void Turtle::SetPenColor(uint8_t r, uint8_t g, uint8_t b) {

    mPenStack.back().rgb[0] = r;
    mPenStack.back().rgb[1] = g;
    mPenStack.back().rgb[2] = b;
}

void Turtle::ResetStack(uint32_t startposx, uint32_t startposy) {
	mPenStack.clear();
	mPenStack.push_back({ true, (float)startposx, (float)startposy, 0, {255, 0, 0} });
}

void Turtle::Reset(uint32_t startposx, uint32_t startposy) {

	Clear();
	ResetStack(startposx, startposy);

}