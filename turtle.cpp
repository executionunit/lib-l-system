#include "turtle.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

#include "glm/glm.hpp"

Turtle::Turtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle,
               float _d)
    : mWidth(width), mHeight(height), mTurnAngle(glm::radians(_angle)), mEdgeLength(_d) {

	ResetStack(startposx, startposy);
}

float Turtle::GetD() const {
    return mEdgeLength;
}

void Turtle::SetD(float newd) {
    mEdgeLength = newd;
}

void Turtle::SetPenPos(int x, int y, int z) {
    mPenStack.back().pos.x = x;
	mPenStack.back().pos.y = y;
	mPenStack.back().pos.z = z;
}

void Turtle::SetAngle(float degrees) {
	mPenStack.back().SetZRot(degrees);
}

void Turtle::MoveForward() {

    auto &pen = mPenStack.back();

    vec3 newpos = pen.pos + pen.angle * vec3(mEdgeLength, 0, 0);

    if (pen.pendown) {
        DrawLine(pen.pos, newpos, pen.rgb);
    }

	pen.pos = newpos;
}

void Turtle::Turn(float rads) {

	mPenStack.back().angle *= quat(vec3(0, 0, rads));
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
	mPenStack.push_back(PenState((float)startposx, (float)startposy, 0, true));
}

void Turtle::Reset(uint32_t startposx, uint32_t startposy) {

	Clear();
	ResetStack(startposx, startposy);

}

void Turtle::PushPen() {
	mPenStack.push_back(mPenStack.back());
}

void Turtle::PopPen() {
	//never pop the original pen off the stack!
	if (mPenStack.size() > 1) {
		mPenStack.pop_back();
		return;
	}
	assert(("pen stack underflow", false));
}
