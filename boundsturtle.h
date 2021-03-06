#ifndef EXUNIT_BOUNDSTURTLE_H
#define EXUNIT_BOUNDSTURTLE_H

#include "turtle.h"
#include <memory>

#include "glm/glm.hpp"
#include <numeric>

/**
** Turtle which just records the min and max position of the pen
** so that the bounds of the rendered LSystem can be ascertained.
** Is there a clever mathematical way to do this? I can't think 
** of anything.
*/
class BoundsTurtle : public Turtle {
public:

	BoundsTurtle(uint32_t startposx, uint32_t startposy, float _angle, float _d);

	glm::vec3 mMin{ std::numeric_limits<float>::max() };
	glm::vec3 mMax{ std::numeric_limits<float>::min() };

	virtual void Clear()override;

private:


	virtual void DrawLine(const vec3 &a, const vec3 &b, uint8_t rgb[3])override;

};

#endif