#include "objturtle.h"
#include "utility.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "glm/glm.hpp"

#include <algorithm>
#include <fstream>

using namespace glm;

OBJTurtle::OBJTurtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy,
	float _angle, float _d)
	: Turtle(width, height, startposx, startposy, _angle, _d) {

}


void OBJTurtle::Clear() {

	mVerts.clear();
	mFaces.clear();
	
}



void OBJTurtle::Save(const char *filename) {

	std::fstream stream(filename, std::ios_base::out);
	if (stream.is_open()) {

		stream << "# saved by OBJTurtle\n";
		stream << "#verts:" << mVerts.size() << '\n';
		for (const auto &v : mVerts) {
			stream << "v " << v.x << " " << v.y << " " << v.z << '\n';
		}

		stream << "#lines:" << mFaces.size() << '\n';
		for (const auto &f : mFaces) {
			stream << "f " << f.a+1 << " " << f.b+1 << " " << f.c + 1 << '\n';
			stream << "f " << f.c + 1 << " " << f.d + 1 << " " << f.a + 1 << '\n';
		}
	}
}

void OBJTurtle::DrawLine(const vec3 &from, const vec3 &to, uint8_t rgb[3]){

	mat4x4 mat = mtx_from_2_vectors(from, to);

	float boxd = -length(to - from);

	const float boxdim = 1.0f;

	vec4 boxverts[] = {
		mat * vec4(-boxdim,-boxdim, boxdim, 1),
		mat * vec4( boxdim,-boxdim, boxdim, 1),
		mat * vec4( boxdim, boxdim, boxdim, 1),
		mat * vec4(-boxdim, boxdim, boxdim, 1),

		mat * vec4(-boxdim,-boxdim, boxd ,1),
		mat * vec4(boxdim,-boxdim, boxd ,1),
		mat * vec4(boxdim, boxdim, boxd ,1),
		mat * vec4(-boxdim, boxdim, boxd ,1),
	};

	uint32_t vertexidx = mVerts.size();
	for (const auto &v : boxverts) {
		mVerts.push_back(vec3(v.x, v.y, v.z));
	}

	mFaces.push_back({ vertexidx+0, vertexidx + 1, vertexidx + 2, vertexidx + 3 });//endcap
	mFaces.push_back({ vertexidx+4, vertexidx + 5, vertexidx + 6, vertexidx + 7 });//endcap

	mFaces.push_back({ vertexidx+0, vertexidx + 4, vertexidx + 5, vertexidx + 1 });//bottom
	mFaces.push_back({ vertexidx + 0, vertexidx + 3, vertexidx + 7, vertexidx + 4 });//left
	mFaces.push_back({ vertexidx + 3, vertexidx + 2, vertexidx + 6, vertexidx + 7 });//top
	mFaces.push_back({ vertexidx + 1, vertexidx + 5, vertexidx + 6, vertexidx + 2 });//right
}
