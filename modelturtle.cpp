#include "modelturtle.h"
#include "utility.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "glm/glm.hpp"

#include <algorithm>
#include <fstream>

using namespace glm;

ModelTurtle::ModelTurtle(uint32_t startposx, uint32_t startposy, float _angle,
                         float _d)
    : Turtle(startposx, startposy, _angle, _d) {
}

void ModelTurtle::Clear() {

    mVerts.clear();
    mFaces.clear();
}

void ModelTurtle::Save(const char *filename) {

    std::fstream stream(filename, std::ios_base::out);
    if (stream.is_open()) {
        stream << "ply\n";
        stream << "format ascii 1.0\n";

        // define the vertex elements
        stream << "element vertex " << mVerts.size() << '\n';
        stream << "property float x\n";
        stream << "property float y\n";
        stream << "property float z\n";
        stream << "property uchar red\n";
        stream << "property uchar green\n";
        stream << "property uchar blue\n";

        // define the face elements
        stream << "element face " << mFaces.size() << '\n';
        stream << "property list uchar int32 vertex_indices\n";
        stream << "end_header\n";

        for (const auto &v : mVerts) {
            stream << v.x << " " << v.y << " " << v.z << " " << (int)v.r << " " << (int)v.g << " " << (int)v.b << '\n';
        }

        for (const auto &f : mFaces) {
            stream << "4 " << f.a << " " << f.b << " " << f.c << " " << f.d << '\n';
        }
    }
}

void ModelTurtle::DrawLine(const vec3 &from, const vec3 &to, uint8_t rgb[3]) {

    mat4x4 mat = mtx_from_2_vectors(from, to);

    float boxd = length(to - from);

    const float boxdim = 1.0f;

    vec4 boxverts[] = {
        mat * vec4(-boxdim, -boxdim, 0, 1),
        mat * vec4(boxdim, -boxdim, 0, 1),
        mat * vec4(boxdim, boxdim, 0, 1),
        mat * vec4(-boxdim, boxdim, 0, 1),

        mat * vec4(-boxdim, -boxdim, -(boxd + boxdim), 1),
        mat * vec4(boxdim, -boxdim, -(boxd + boxdim), 1),
        mat * vec4(boxdim, boxdim, -(boxd + boxdim), 1),
        mat * vec4(-boxdim, boxdim, -(boxd + boxdim), 1),
    };

    uint8_t frontcapcol[3] = {rgb[0], rgb[1], rgb[2]};
    uint8_t endcapcol[3] = {rgb[0], rgb[1], rgb[2]};

    //if (mFaces.size() == 0) {
    //    frontcapcol[0] = 0;
    //    frontcapcol[1] = 255;
    //    frontcapcol[2] = 0;

    //    endcapcol[0] = 0;
    //    endcapcol[1] = 255;
    //    endcapcol[2] = 255;
    //}


	//uint8_t bottomcol[3] = { 255, 0, 0 };
	//uint8_t leftcol[3] = { 0, 255, 0 };
	//uint8_t topcol[3] = { 0, 0, 255 };
	//uint8_t rightcol[3] = { 255, 0, 255 };

	uint8_t bottomcol[3] = { rgb[0], rgb[1], rgb[2] };
	uint8_t leftcol[3] = { rgb[0], rgb[1], rgb[2] };
	uint8_t topcol[3] = { rgb[0], rgb[1], rgb[2] };
	uint8_t rightcol[3] = { rgb[0], rgb[1], rgb[2] };


    const auto &bv = boxverts;
    //front cap
	AddFace({bv[0], frontcapcol}, {bv[1], frontcapcol}, {bv[2], frontcapcol}, {bv[3], frontcapcol});
	//endcap
    AddFace({bv[4], endcapcol}, {bv[5], endcapcol}, {bv[6], endcapcol}, {bv[7], endcapcol});

	//bottom
	AddFace({ bv[0], bottomcol }, { bv[4], bottomcol }, { bv[5], bottomcol }, { bv[1], bottomcol });

	//left
	AddFace({ bv[0], leftcol }, { bv[3], leftcol }, { bv[7], leftcol }, { bv[4], leftcol });

	//top
	AddFace({ bv[3], topcol }, { bv[2], topcol }, { bv[6], topcol }, { bv[7], topcol });

	//right
	AddFace({ bv[1], rightcol }, { bv[5], rightcol }, { bv[6], rightcol }, { bv[2], rightcol });

}

void ModelTurtle::AddFace(const Vertex &a, const Vertex &b, const Vertex &c, const Vertex &d) {

    uint32_t vertexidx = mVerts.size();

    // fuck looking for dups.
    mVerts.push_back(a);
    mVerts.push_back(b);
    mVerts.push_back(c);
    mVerts.push_back(d);

    mFaces.push_back({vertexidx + 0, vertexidx + 1, vertexidx + 2, vertexidx + 3});
}