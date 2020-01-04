
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

void DoBasicDOL(int width, int height, int startx, int starty, int iterations) {
	{
		PNGTurtle turtle(width, height, startx, starty, 90.0f, 50);
		turtle.SetPenColor(255, 0, 0);

		// quadratic koch island (1.3a)
		exunit::lsystem::DOLSystem system("F-F-F-F", { "F=>F+FF-FF-F-F+F+FF-F-F+F+FF+FF-F" });
		iterations = 3;
		system.Iterate(iterations);
		turtle.Reset(startx, starty);
		turtle.SetD(2.2f);
		turtle.SetPenPos(200, 300);
		turtle.Render(system.GetState());
		turtle.Save("quad_koch_island.png");
	}

	{
		PNGTurtle turtle(width, height, startx, starty, 90.0f, 50);
		turtle.SetPenColor(255, 0, 0);

		// quadratic snowflack curve (1.3b)
		exunit::lsystem::DOLSystem system("-F", { "F=>F+F-F-F+F" });
		iterations = 5;
		system.Iterate(iterations);
		turtle.Reset(startx, starty);
		turtle.SetD(3);
		turtle.SetPenPos(100, 100);
		turtle.Render(system.GetState());
		turtle.Save("quad_snowflake.png");
	}

	{
		PNGTurtle turtle(width, height, startx, starty, 90.0f, 50);
		turtle.SetPenColor(255, 0, 0);

		// Islands and lakes (1.8)
		exunit::lsystem::DOLSystem system("F+F+F+F", { "F=>F+f-FF+F+FF+Ff+FF-f+FF-F-FF-Ff-FFF", "f=>ffffff" });
		iterations = 3;
		system.Iterate(iterations);
		turtle.Reset(startx, starty);
		turtle.SetD(4);
		turtle.SetPenPos(100, height - 100);
		turtle.Render(system.GetState());
		turtle.Save("koch_islands.png");
	}

	{
		PNGTurtle turtle(width, height, startx, starty, 90.0f, 50);
		turtle.SetPenColor(255, 0, 0);

		// dragon curve (1.10a)
		// F == Fl
		// I == Fr
		exunit::lsystem::DOLSystem system("F", { "F=>F+I+", "I=>-F-I" });
		iterations = 10;
		system.Iterate(iterations);
		turtle.Reset(startx, starty);
		turtle.SetD(15);
		turtle.SetPenPos(600, height - 400);
		turtle.SetAngle(-90.0f);
		turtle.Render(system.GetState());
		turtle.Save("dragoncurve.png");
	}

	{
		PNGTurtle turtle(width, height, startx, starty, 60.0f, 50);
		turtle.SetPenColor(255, 0, 0);

		// dragon curve (1.10b)
		// F == Fl
		// I == Fr
		exunit::lsystem::DOLSystem system("I", { "F=>I+F+I", "I=>F-I-F" });
		iterations = 6;
		system.Iterate(iterations);
		turtle.Reset(startx, starty);
		turtle.SetD(15);
		turtle.SetPenPos(10, height - 100);
		turtle.Render(system.GetState());
		turtle.Save("sierpinksi-gasket.png");
	}

	{
		PNGTurtle turtle(width, height, startx, starty, 60.0f, 50);
		turtle.SetPenColor(255, 0, 0);

		// hexagon-gosper curve (1.11a)
		// F == Fl
		// I == Fr
		exunit::lsystem::DOLSystem system("F", { "F=>F+I++I-F--FF-I+", "I=>-F+II++I+F--F-I" });
		iterations = 4;
		system.Iterate(iterations);
		turtle.Reset(startx, starty);
		turtle.SetD(15);
		turtle.SetPenPos(650, height - 100);
		turtle.Render(system.GetState());
		turtle.Save("hexagon-gosper.png");
	}

	{
		PNGTurtle turtle(width, height, startx, starty, 90.0f, 50);
		turtle.SetPenColor(255, 0, 0);

		// quadratic-gosper curve (1.11b)
		// F == Fl
		// I == Fr
		exunit::lsystem::DOLSystem system("-I", { "F=>FF-I-I+F+F-I-IF+I+FFI-F+I+FF+I-FI-I-F+F+II-", "I=>+FF-I-I+F+FI+F-II-F-I+FII-F-IF+F+I-I-F+F+II" });
		iterations = 2;
		system.Iterate(iterations);
		turtle.Reset(startx, starty);
		turtle.SetD(20);
		turtle.SetPenPos(100, 100);
		turtle.Render(system.GetState());
		turtle.Save("quadratic-gosper.png");
	}

}

void DoBranching(int width, int height, int startx, int starty, int iterations) {

	struct Plant{
		const char *axiom;
		std::vector<std::string> rules;
		int itererations;
		float branchangle;
		float branchlength;
		const char *filename;

	} Plants[] = {
		{"F", {"F=>F[+F]F[-F]F"}, 5, 25.7f, 3.0f, "plant1.png"},
		{"F", {"F=>F[+F]F[-F]F"}, 5, 20.0f, 3.0f, "plant2.png"},
		{"F", {"F=>FF-[-F+F+F]+[+F-F-F]"}, 4, 22.5f, 12.0f, "plant3.png"},
		{"X", {"X=>F[+X]F[-X]+X", "F=>FF"}, 7, 20.0f, 3.5f, "plant4.png"},
		{"X", {"X=>F[+X][-X]FX", "F=>FF"}, 7, 25.7f, 3.5f, "plant5.png"},
		{"X", {"X=>F-[[X]+X]+F[+FX]-X", "F=>FF"}, 7, 22.5f, 2.8f, "plant6.png"},
	};

	for(const auto plant: Plants){
	
		float angle = 25.7f;
		PNGTurtle turtle(width, height, startx, starty, plant.branchangle, plant.branchlength);
		turtle.SetPenColor(255, 0, 0);

		// plant (1.24a)
		exunit::lsystem::DOLSystem system(plant.axiom, plant.rules);

		system.Iterate(plant.itererations);
		turtle.SetAngle(-90);
		turtle.SetPenPos(width >> 1, height-100);
		turtle.Render(system.GetState());
		turtle.Save(plant.filename);
	}
}

int main(int argc, char **argv) {

	cxxopts::Options options("lsystemexe", "harness for LSystemLib");
	options.add_options()("t,turtle", "turtle type", cxxopts::value<std::string>()->default_value("png"))(
		"f,file", "File name", cxxopts::value<std::string>()->default_value("out.png"))(
			"w,width", "Image Width", cxxopts::value<int>()->default_value("1024"))(
				"h,height", "Image Height", cxxopts::value<int>()->default_value("1024"))(
					"i,iterations", "System Iterations", cxxopts::value<int>()->default_value("4"));

	auto        result = options.parse(argc, argv);
	std::string fname = result["file"].as<std::string>();
	size_t      pos = fname.find_last_of(".");
	if (pos != std::string::npos) {
		fname = fname.substr(0, pos);
	}

	int width = result["width"].as<int>();
	int height = result["height"].as<int>();
	int startx = width >> 1;
	int starty = height >> 1;
	int iterations = result["iterations"].as<int>();

	//DoBasicDOL(width, height, startx, starty, iterations);
	DoBranching(width, height, startx, starty, iterations);
}

