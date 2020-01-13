#ifndef EXUNIT_OBJTURTLE_H
#define EXUNIT_OBJTURTLE_H

#include "turtle.h"
#include <memory>


/**
** Turtle that knows how to build a 3D model and save it as a PLY file.
*/
class ModelTurtle : public Turtle {
public:

	static constexpr int numplanes() {
		return 3;
	}

	ModelTurtle(uint32_t startposx, uint32_t startposy, float _angle, float _d);
	void Save(const char *filename);

	void Clear();

private:

	struct Face {
		uint32_t a, b, c, d;
	};

	struct Vertex {
		float x, y, z;
		uint8_t r, g, b;

		Vertex(const vec3 &pos, uint8_t rgb[3]) {
			x = pos.x;
			y = pos.y;
			z = pos.z;
			r = rgb[0];
			g = rgb[1];
			b = rgb[2];
		}

		void SetColor(uint8_t _r, uint8_t _g, uint8_t _b) {
			r = _r;
			g = _g;
			b = _b;
		}
	};

	std::vector<Vertex> mVerts;
	std::vector<Face>mFaces;

	virtual void DrawLine(const vec3 &a, const vec3 &b, uint8_t rgb[3])override;

	void AddFace(const Vertex &a, const Vertex &b, const Vertex &c, const Vertex &d);

};

#endif