#include "pngturtle.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

PNGTurtle::PNGTurtle(uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle, float _d)
    : Turtle(width, height, startposx, startposy, _angle, _d) {

    mBuffer.reset(new uint8_t[width * height * numplanes()]);

    Clear();
}

void PNGTurtle::Render(const char *s) {
    if (s == nullptr) {
        return;
    }

    while (*s != '\0') {
        char c = *s;

        switch (c) {
        case 'F':
            MoveForward();
            break;
        case 'f':
            PenUp();
            MoveForward();
            PenDown();
            break;
        case '+':
            Turn(-mTurnAngle);
            break;
        case '-':
            Turn(mTurnAngle);
            break;
        }

        ++s;
    }
}

void PNGTurtle::Clear() {

    static_assert(numplanes() == 3, "broken assumption here, inner loop needs changing");

    uint8_t *d = mBuffer.get();

    for (uint32_t y = 0; y < mHeight; ++y) {
        for (uint32_t x = 0; x < mWidth; ++x) {
            *d++ = 0;
            *d++ = 0;
            *d++ = 0;
        }
    }
}

void PNGTurtle::Reset() {
    Clear();
    SetPenPos(mWidth >> 1, mHeight >> 1);
    SetAngle(0);
}

void PNGTurtle::Save(const char *filename) {

    int numpl = numplanes();
    int linestride = mWidth * numpl;

    stbi_write_png(filename, mWidth, mHeight, numpl, mBuffer.get(), linestride);
}

void PNGTurtle::DrawLine(int x0, int y0, int x1, int y1) const {

    if (x0 >= 0 && x0 < (int)mWidth && y0 >= 0 && y0 < (int)mHeight ||
        x1 >= 0 && x1 < (int)mWidth && y1 >= 0 && y1 < (int)mHeight) {

        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;

        for (;;) {
            plot(x0, y0, 255, 0, 0);
            if (x0 == x1 && y0 == y1)
                break;
            e2 = err;
            if (e2 > -dx) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dy) {
                err += dx;
                y0 += sy;
            }
        }
    }
}
