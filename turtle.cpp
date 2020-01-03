#include "turtle.h"

#define _USE_MATH_DEFINES
#include <math.h>

constexpr float radians(float deg) { return deg * (float)M_PI / 180.0f; }

Turtle::Turtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle, float _d)
	: mWidth(width), mHeight(height), xpos((float)startposx), ypos((float)startposy), mTurnAngle(radians(_angle)), d(_d) {
}

float Turtle::GetD() const {
	return d;
}
void Turtle::SetD(float newd) {
	d = newd;
}
void Turtle::SetPenPos(int x, int y) {
	xpos = (float)x;
	ypos = (float)y;
}
void Turtle::SetAngle(float a) {
	angle = 0;
}

void Turtle::MoveForward() {
	float newx = xpos + d * cosf(angle);
	float newy = ypos + d * sinf(angle);
	if (pendown) {
		DrawLine((int)xpos, (int)ypos, (int)newx, (int)newy);
	}

	xpos = newx;
	ypos = newy;
}

void Turtle::Turn(float rads) {
	angle += rads;
}

void Turtle::PenUp() {
	pendown = false;
}
void Turtle::PenDown() {
	pendown = true;
}
