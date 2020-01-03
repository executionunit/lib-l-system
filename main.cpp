
#include "dolsystem.h"
#include "pngturtle.h"

#include "cxxopts.hpp"


#include <memory>
#include <stdarg.h>

std::string StrFormat(const char *fmt, ...) {
	char buffer[4096];

	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, 4095, fmt, arg);
	va_end(arg);
	return buffer;
}


int main(int argc, char **argv) {

	cxxopts::Options options("lsystemexe", "harness for LSystemLib");
	options.add_options()("t,turtle", "turtle type", cxxopts::value<std::string>()->default_value("png"))
		("f,file", "File name", cxxopts::value<std::string>()->default_value("out.png"))
		("w,width", "Image Width", cxxopts::value<int>()->default_value("1024"))
		("h,height", "Image Height", cxxopts::value<int>()->default_value("1024"))
		("i,iterations", "System Iterations", cxxopts::value<int>()->default_value("4"));

	auto result = options.parse(argc, argv);
	std::string fname = result["file"].as<std::string>();
	size_t pos = fname.find_last_of(".");
	if (pos != std::string::npos) {
		fname = fname.substr(0, pos);
	}

	int width = result["width"].as<int>();
	int height = result["height"].as<int>();
	int startx = width >> 1;
	int starty = height >> 1;
	int iterations = result["iterations"].as<int>();

	int numpens = 1;

	PNGTurtle turtle(numpens, width, height, startx, starty, 90.0f, 50);
	turtle.SetPenColor(0, 255, 0, 0);

	//koch island
	//exunit::lsystem::DOLSystem system("F-F-F-F", {"F=>F-F+F+FF-F-F+F"});

	{
		//quadratic koch island (1.3a)
		exunit::lsystem::DOLSystem system("F-F-F-F", { "F=>F+FF-FF-F-F+F+FF-F-F+F+FF+FF-F" });
		iterations = 3;
		system.Iterate(iterations);
		turtle.Reset();
		turtle.SetD(2.2f);
		turtle.SetPenPos(0, 200, 300);
		turtle.Render(system.GetState());
		turtle.Save("quad_koch_island.png");
	}


	{
		//quadratic snowflack curve (1.3b)
		exunit::lsystem::DOLSystem system("-F", { "F=>F+F-F-F+F" });
		iterations = 5;
		system.Iterate(iterations);
		turtle.Reset();
		turtle.SetD(3);
		turtle.SetPenPos(0, 100, 100);
		turtle.Render(system.GetState());
		turtle.Save("quad_snowflake.png");
	}

	{
		//Islands and lakes (1.8)
		exunit::lsystem::DOLSystem system("F+F+F+F", { "F=>F+f-FF+F+FF+Ff+FF-f+FF-F-FF-Ff-FFF", "f=>ffffff" });
		iterations = 3;
		system.Iterate(iterations);
		turtle.Reset();
		turtle.SetD(4);
		turtle.SetPenPos(0, 100, height - 100);
		turtle.Render(system.GetState());
		turtle.Save("koch_islands.png");
	}
}