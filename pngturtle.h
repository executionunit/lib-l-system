#ifndef EXUNIT_PNGTURTLE_H
#define EXUNIT_PNGTURTLE_H

#include "turtle.h"
#include <memory>



class PNGTurtle : public Turtle {
public:

	static constexpr int numplanes() {
		return 3;
	}

	PNGTurtle(uint32_t numpens, uint32_t width, uint32_t height, uint32_t startposx, uint32_t startposy, float _angle, float _d);
	void Save(const char *filename);

	virtual void Render(const char *s);

	void Clear();
	void Reset();

private:
	std::unique_ptr<uint8_t> mBuffer;

	inline void plot(int x, int y, uint8_t r, uint8_t g, uint8_t b)const {

		if (x >= 0 && x < (int)mWidth && y >= 0 && y < (int)mHeight) {

			uint8_t *buf = mBuffer.get();
			buf += mWidth * y * numplanes() + x * numplanes();

			static_assert(numplanes() == 3, "broken assumption here, inner loop needs changing");
			buf[0] = r;
			buf[1] = g;
			buf[2] = b;
		}
	}

	virtual void DrawLine(int x0, int y0, int x1, int y1, uint8_t rgb[3])const override;

};

#endif