#ifndef EXUNIT_TURTLE_H
#define EXUNIT_TURTLE_H

#include <stdint.h>
#include <vector>

class Turtle {
public:
    Turtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle, float _d);

    virtual void Render(const char *s) = 0;
    virtual void Clear() = 0;
    virtual void DrawLine(int xpos, int ypos, int newx, int newy, uint8_t rgb[3]) const = 0;
	
	
	virtual void Reset(uint32_t startposx, uint32_t startposy);

    float GetD() const;
    void  SetD(float newd);

    void SetAngle(float degrees);
    void SetPenPos(int x, int y);
    void MoveForward();
    void Turn(float rads);
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
        bool    pendown{true};
        float   xpos{0.0f};
        float   ypos{0.0f};
        float   angle{0};
        uint8_t rgb[3]{255, 0, 0};
    };

    std::vector<PenState> mPenStack;
};

#endif // EXUNIT_LSYSTEMLIB_TURTLE_H