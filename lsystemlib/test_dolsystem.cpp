#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "dolsystem.h"

using namespace exunit::lsystem;

TEST_CASE("DOL System Empty Construction") {

    DOLSystem s("", DOLSystem::svector());

    CHECK(strcmp(s.GetState(), "") == 0);
	CHECK(s.GetGeneration() == 0);
}

TEST_CASE("DOL Errorful rule") {

	const char *axiom = "F-F-F-F";
	{
		DOLSystem s(axiom, {"F->FF"});

		/* the rule should fail to add because the is no '=>' in it.*/
		CHECK(s.GetNumRules() == 0);
	}
}

TEST_CASE("DOL System Basic") {

    const char *axiom = "F-F-F-F";
    {
        DOLSystem s(axiom, DOLSystem::svector());
        CHECK(strcmp(s.GetState(), axiom) == 0);
		CHECK(s.GetGeneration() == 0);
    }

    {
        const char *rule = "F=>F-F+F+FF-F-F+F";
        DOLSystem   s(axiom, {rule});
        CHECK(strcmp(s.GetState(), axiom) == 0);
        CHECK(s.GetNumRules() == 1);
        CHECK(s.GetRules()[0].from == "F");
		CHECK(s.GetRules()[0].to == "F-F+F+FF-F-F+F");
		CHECK(s.GetGeneration() == 0);
    }
}

/* basic DOL from page 4 of Algorithmic beauty of plants */
TEST_CASE("DOL System Iterate") {

	const char *axiom = "b";
	DOLSystem::svector rules = { "a=>ab", "b=>a" };
	DOLSystem   s(axiom, rules);

	s.Iterate();
	CHECK(s.GetGeneration() == 1);
	CHECK(strcmp(s.GetState(), "a") == 0);

	s.Iterate();
	CHECK(s.GetGeneration() == 2);
	CHECK(strcmp(s.GetState(), "ab") == 0);

	s.Iterate();
	CHECK(s.GetGeneration() == 3);
	CHECK(strcmp(s.GetState(), "aba") == 0);

	s.Iterate();
	CHECK(s.GetGeneration() == 4);
	CHECK(strcmp(s.GetState(), "abaab") == 0);

	s.Iterate();
	CHECK(s.GetGeneration() == 5);
	CHECK(strcmp(s.GetState(), "abaababa") == 0);
}

/* basic DOL from page 4 of Algorithmic beauty of plants we iterate it
** Multiple times here to see if we get the correct answer.
*/
TEST_CASE("DOL System Multi Iterate") {

	const char *axiom = "b";
	DOLSystem::svector rules = { "a=>ab", "b=>a" };
	DOLSystem   s(axiom, rules);

	s.Iterate(5);
	CHECK(s.GetGeneration() == 5);
	CHECK(strcmp(s.GetState(), "abaababa") == 0);
}

TEST_CASE("Context Sensitive LSystems") {

	const char *axiom = "b";
	DOLSystem::svector rules = { "a=>ab", "b=>a" };
	const char *ignore = "+-";
	DOLSystem   s(axiom, rules, ignore);
}