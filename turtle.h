#ifndef EXUNIT_TURTLE_H
#define EXUNIT_TURTLE_H

#include <stdint.h>
#include <vector>

#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/ext/vector_float3.hpp"

class Turtle {
public:
	using quat = glm::quat;
	using vec3 = glm::vec3;
	
	Turtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle, float _d);

    virtual void Render(const char *s);
    virtual void Clear() = 0;
    virtual void DrawLine(const vec3 &a, const vec3 &b, uint8_t rgb[3]) = 0;

    virtual void Reset(uint32_t startposx, uint32_t startposy);

    float GetD() const;
    void  SetD(float newd);

    void SetAngle(float degrees);
    void SetPenPos(int x, int y, int z = 0);
    void MoveForward();

	/* imagine the turtle is stnading in the XY plane which is parallel to the screen */
	void TurnX(float rads); /* pitching in/out around the X axis*/
	void TurnY(float rads); /* roll around the Y axis */
    void TurnZ(float rads); /* turn left right around the Z axis (in/out of the screen)*/

    void PenUp();
    void PenDown();
    void SetPenColor(uint8_t r, uint8_t g, uint8_t b);
    void ResetStack(uint32_t startposx, uint32_t startposy);

protected:

    uint32_t mWidth;
    uint32_t mHeight;
    float    mTurnAngle;
    float    mEdgeLength;

    struct PenState {
        vec3    pos{0, 0, 0};
        quat    angle;
        uint8_t rgb[3]{255, 0, 0};
        bool    pendown{true};

        PenState(float x, float y, float angle, bool ipendown)
            : pos(vec3(x, y, 0)), angle(glm::quat(vec3(0, 0, glm::radians(angle)))), rgb{255, 0, 0}, pendown(ipendown) {
        }

        void SetZRot(float deg) {
            angle = glm::quat(vec3(0, 0, glm::radians(deg)));
        }
    };

    std::vector<PenState> mPenStack;

    void PushPen();
    void PopPen();
};

#endif // EXUNIT_LSYSTEMLIB_TURTLE_H