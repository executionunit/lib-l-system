#ifndef EXUNIT_OBJTURTLE_H
#define EXUNIT_OBJTURTLE_H

#include "turtle.h"
#include <memory>



class OBJTurtle : public Turtle {
public:

	static constexpr int numplanes() {
		return 3;
	}

	OBJTurtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle, float _d);
	void Save(const char *filename);

	void Clear();

private:

	struct Face {
		uint32_t a, b, c, d;
	};

	std::vector<vec3> mVerts;
	std::vector<Face>mFaces;

	virtual void DrawLine(const vec3 &a, const vec3 &b, uint8_t rgb[3])override;

};

#endif