#ifndef EXUNIT_TURTLE_H
#define EXUNIT_TURTLE_H

#include <stdint.h>
#include <vector>

#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/ext/vector_float3.hpp"

/**
** Base class for all Turtles.
*/
class Turtle {
public:
    using vec3 = glm::vec3;
    using mat3 = glm::mat3x3;

    Turtle(uint32_t startposx, uint32_t startposy, float _angle, float _d);

    virtual void Render(const char *s);
    virtual void Clear() = 0;
    virtual void DrawLine(const vec3 &a, const vec3 &b, uint8_t rgb[3]) = 0;

    virtual void Reset(uint32_t startposx, uint32_t startposy, float angleradians = 0);

    float GetD() const;
    void  SetD(float newd);

    void SetAngle(float degrees);
    void SetPenPos(int x, int y, int z = 0);
    void MoveForward(uint32_t steps = 1);

    void Roll(float rads);
    void Turn(float rads);
    void Pitch(float rads);

    void PenUp();
    void PenDown();
    void SetPenColor(uint8_t r, uint8_t g, uint8_t b);
    void ResetStack(uint32_t startposx, uint32_t startposy, float angleradians);
    void SetScale(const vec3 &s) {
        mScale = s;
    }
    void SetPenOffset(const vec3 &penoffset) {
        mOffset = penoffset;
    }

protected:
    float mTurnAngle;
    float mEdgeLength;

    vec3 mScale{1.0f, 1.0f, 1.0f};
    vec3 mOffset{0.0f};

    struct PenState {
        vec3    pos{0, 0, 0};
        mat3    angle;
        uint8_t rgb[3]{255, 0, 0};
        bool    pendown{true};

        PenState(float x, float y, bool ipendown) : pos(vec3(x, y, 0)), rgb{255, 0, 0}, pendown(ipendown) {
            angle = glm::identity<mat3>();
        }

        void SetZRot(float deg) {
            float c = glm::cos(glm::radians(deg));
            float s = glm::sin(glm::radians(deg));
            angle = mat3(c, -s, 0, s, c, 0, 0, 0, 1);
        }
    };

    std::vector<PenState> mPenStack;

    void PushPen();
    void PopPen();
};

#endif // EXUNIT_LSYSTEMLIB_TURTLE_H