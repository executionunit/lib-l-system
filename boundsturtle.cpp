#include "boundsturtle.h"
#include <algorithm>

BoundsTurtle::BoundsTurtle(uint32_t startposx, uint32_t startposy, float _angle, float _d)
    : Turtle(startposx, startposy, _angle, _d) {
}

void BoundsTurtle::DrawLine(const vec3 &a, const vec3 &b, uint8_t /*rgb*/[3]) {
    mMin.x = std::min(a.x, mMin.x);
    mMin.y = std::min(a.y, mMin.y);
    mMin.z = std::min(a.z, mMin.z);

    mMax.x = std::max(a.x, mMax.x);
    mMax.y = std::max(a.y, mMax.y);
    mMax.z = std::max(a.z, mMax.z);


	mMin.x = std::min(b.x, mMin.x);
	mMin.y = std::min(b.y, mMin.y);
	mMin.z = std::min(b.z, mMin.z);

	mMax.x = std::max(b.x, mMax.x);
	mMax.y = std::max(b.y, mMax.y);
	mMax.z = std::max(b.z, mMax.z);

}

void BoundsTurtle::Clear() {
	mMin = glm::vec3{ std::numeric_limits<float>::max() };
	mMax = glm::vec3{ std::numeric_limits<float>::lowest()};
}

