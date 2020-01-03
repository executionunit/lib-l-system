#ifndef EXUNIT_TURTLE_H
#define EXUNIT_TURTLE_H

#include <stdint.h>

class Turtle {
public:
	Turtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle, float _d);

    virtual void Render(const char *s) = 0;
    virtual void Clear() = 0;
    virtual void DrawLine(int xpos, int ypos, int newx, int newy) const = 0;
    virtual void Reset() = 0;
    

	float GetD() const;
	void SetD(float newd);
	void SetPenPos(int x, int y);
	void SetAngle(float a);

	void MoveForward();

	void Turn(float rads);

	void PenUp();
	void PenDown();

protected:
    uint32_t mWidth;
    uint32_t mHeight;
    float    mTurnAngle;

    bool  pendown{true};
    float xpos;
    float ypos;
	float angle{ 0 };
    float d;
};

#endif // EXUNIT_LSYSTEMLIB_TURTLE_H