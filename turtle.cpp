#include "turtle.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

#include "glm/glm.hpp"

Turtle::Turtle(uint32_t startposx, uint32_t startposy, float _angle,
               float _d)
    : mTurnAngle(glm::radians(_angle)), mEdgeLength(_d) {

	ResetStack(startposx, startposy, 0);
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

void Turtle::MoveForward(uint32_t steps) {

    auto &pen = mPenStack.back();

    vec3 newpos = pen.pos + pen.angle * vec3(0, mEdgeLength * steps, 0);

    if (pen.pendown) {
        DrawLine( (pen.pos + mOffset) * mScale, (newpos + mOffset)* mScale, pen.rgb);
    }

	pen.pos = newpos;
}

void Turtle::Roll(float rads) {
	float c = glm::cos(rads);
	float s = glm::sin(rads);

	//RH
	mPenStack.back().angle = mPenStack.back().angle * mat3(1, 0, 0 ,0, c, s, 0, -s, c);
}

void Turtle::Turn(float rads) {

	float c = glm::cos(rads);
	float s = glm::sin(rads);

	//RU
	mPenStack.back().angle = mPenStack.back().angle * mat3(c, -s, 0, s, c, 0, 0, 0, 1);
}

void Turtle::Pitch(float rads) {

	float c = glm::cos(rads);
	float s = glm::sin(rads);

	//RL
	mPenStack.back().angle = mPenStack.back().angle * mat3(c, 0, s, 0, 1, 0, -s, 0, c);
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

void Turtle::ResetStack(uint32_t startposx, uint32_t startposy, float angleradians) {
	mPenStack.clear();
	mPenStack.push_back(PenState((float)startposx, (float)startposy, true));
	//Turn(angleradians);
}

void Turtle::Reset(uint32_t startposx, uint32_t startposy, float angleradians) {

	Clear();
	ResetStack(startposx, startposy, angleradians);

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

void Turtle::Render(const char *s) {
	if (s == nullptr) {
		return;
	}

	while (*s != '\0') {
		char c = *s++;

		switch (c) {
		case 'I':/* deliberate fallthrough */
		case 'F': {
			int cnt = 1;
			while ( *s == 'F' || *s == 'I' ) {
				++cnt;
				++s;
			}
			MoveForward(cnt);
		}break;
		case 'f':
			PenUp();
			MoveForward();
			PenDown();
			break;
		case '+':
			Turn(mTurnAngle);
			break;
		case '-':
			Turn(-mTurnAngle);
			break;
		case '&':
			Roll(mTurnAngle);
			break;
		case '^':
			Roll(-mTurnAngle);
			break;
		case '\\':
			Pitch(mTurnAngle);
			break;
		case '/':
			Pitch(-mTurnAngle);
			break;
		case '|':
			Turn(glm::radians(180.0f));
			break;
		case '[':
			PushPen();
			break;
		case ']':
			PopPen();
			break;
		}

		
	}
}