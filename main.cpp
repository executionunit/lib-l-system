
#include "dolsystem.h"
#include "pngturtle.h"
#include "modelturtle.h"
#include "boundsturtle.h"

#include "cxxopts.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

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

    struct System {
        const char *             axiom;
        std::vector<std::string> rules;
        int                      itererations;
        float                    branchangle;
        const char *             filename;

	} basics[] = {
		{
			 "-I", 
			{"F=>FF-I-I+F+F-I-IF+I+FFI-F+I+FF+I-FI-I-F+F+II-", "I=>+FF-I-I+F+FI+F-II-F-I+FII-F-IF+F+I-I-F+F+II"},
			2,
			90.0f,
			"quadratic-gosper.png"
		},
		{
			"F", {"F=>F+I++I-F--FF-I+", "I=>-F+II++I+F--F-I"},
			4,
			60.0f,
			"hexagon-gosper.png"
		},
		{
			"I", {"F=>I+F+I", "I=>F-I-F"},
			6,
			60.0f,
			"sierpinksi-gasket.png"
		},
		{
			"F", {"F=>F+I+", "I=>-F-I"},
			10,
			90.0f,
			"dragoncurve.png"
		},
		{
			"F+F+F+F", {"F=>F+f-FF+F+FF+Ff+FF-f+FF-F-FF-Ff-FFF", "f=>ffffff"},
			3,
			90.0f,
			"koch_islands.png"
		},
		{
			"-F", 
			{"F=>F+F-F-F+F"},
			5,
			90.0f, 
			"quad_snowflake.png"
		},
		{
			"F-F-F-F",
			{"F=>F+FF-FF-F-F+F+FF-F-F+F+FF+FF-F"},
			3,
			90.0f,
			"quad_koch_island.png"
		}
	};

	for (const auto &b : basics) {
		exunit::lsystem::DOLSystem system(b.axiom, b.rules);
		system.Iterate(b.itererations);

		const float branchlength = 10.0f;
		const int startx = 0;
		const int starty = 0;

		BoundsTurtle bounds(startx, starty, b.branchangle, branchlength);
		bounds.Render(system.GetState());

		float syswidth = (bounds.mMax.x - bounds.mMin.x);
		float sysheight = (bounds.mMax.y - bounds.mMin.y);
		
		float scale = std::min(width / syswidth, height / sysheight);
		glm::vec3 center = ((bounds.mMin + (bounds.mMax - bounds.mMin) * 0.5f)) * 0.5f;

		PNGTurtle turtle(width, height, startx, starty, b.branchangle, branchlength);
		turtle.SetPenOffset(-bounds.mMin);
		turtle.SetScale(glm::vec3(scale));
		turtle.SetPenColor(255, 0, 0);
		turtle.Render(system.GetState());
		turtle.Save(b.filename);
	}
}

void DoBranching(int width, int height, int startx, int starty, int iterations) {

    struct System {
        const char *             axiom;
        std::vector<std::string> rules;
        int                      itererations;
        float                    branchangle;
        float                    branchlength;
        const char *             filename;

    } Plants[] = {
        {"F", {"F=>F[+F]F[-F]F"}, 5, 25.7f, 3.0f, "plant1.png"},
        {"F", {"F=>F[+F]F[-F]F"}, 5, 20.0f, 3.0f, "plant2.png"},
        {"F", {"F=>FF-[-F+F+F]+[+F-F-F]"}, 4, 22.5f, 12.0f, "plant3.png"},
        {"X", {"X=>F[+X]F[-X]+X", "F=>FF"}, 7, 20.0f, 3.5f, "plant4.png"},
        {"X", {"X=>F[+X][-X]FX", "F=>FF"}, 7, 25.7f, 3.5f, "plant5.png"},
        {"X", {"X=>F-[[X]+X]+F[+FX]-X", "F=>FF"}, 7, 22.5f, 2.8f, "plant6.png"},
    };

    for (const auto plant : Plants) {

        PNGTurtle turtle(width, height, startx, starty, plant.branchangle, plant.branchlength);
        turtle.SetPenColor(255, 0, 0);

        // plant (1.24a)
        exunit::lsystem::DOLSystem system(plant.axiom, plant.rules);

        system.Iterate(plant.itererations);
        // turtle.Turn(glm::radians(0.0f));
        turtle.SetPenPos(width >> 1, 0, 100);
        turtle.Render(system.GetState());
        turtle.Save(plant.filename);
    }
}

void Do3D(int startx, int starty, int iterations) {
    struct System {
        const char *             axiom;
        std::vector<std::string> rules;
        int                      itererations;
        float                    branchangle;
        float                    branchlength;
        const char *             filename;

    } systems[] = {
        {
			"A",
			 {R"(A=>B-F+CFC+F-D&F^D-F+&&CFC+F+B//)", R"(B=>A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//)",
			  R"(C=>|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//)", R"(D=>|CFB-F+B|FA&F^A&&FB-F+B|FC//)"},
			 3,
			 90,
			 10.0f,
			 "hilbert3d.ply"
		},
		{
			"A",
			{
				"A=>[&FL!A]/////'[&FL!A]///////'[&FL!A]",
				"F=>S ///// F",
				"S=>FL",
				"L=>"
			},
			7,
			22.5f,
			0.5f,
			"bush_1.25.ply"
		}
    };

    for (const auto plant : systems) {

        ModelTurtle turtle(startx, starty, plant.branchangle, plant.branchlength);
        turtle.SetPenColor(244, 173, 11);

        exunit::lsystem::DOLSystem system(plant.axiom, plant.rules);

        system.Iterate(plant.itererations);
        turtle.SetAngle(-90);
        turtle.Render(system.GetState());
        turtle.Save(plant.filename);
    }
}

void DoOBJTurtle() {

    ModelTurtle turtle(0, 0, 90, 10);
    turtle.SetPenColor(255, 0, 0);
    // turtle.Render(R"(^\F^\F-F^//F&F+F//-F)");

    turtle.MoveForward();
    turtle.Turn(glm::radians(90.0f));
    turtle.MoveForward();

    turtle.Save("testturtle.ply");
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

    DoBasicDOL(width, height, startx, starty, iterations);
    DoBranching(width, height, startx, starty, iterations);
    Do3D(startx, starty, iterations);
    DoOBJTurtle();
}
