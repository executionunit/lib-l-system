#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "lsystem.h"

using namespace exunit::lsystem;

TEST_CASE("DOL System Empty Construction") {

    LSystem s("", LSystem::svector());

    CHECK(strcmp(s.GetState(), "") == 0);
	CHECK(s.GetGeneration() == 0);
}

TEST_CASE("DOL Errorful rule") {

	const char *axiom = "F-F-F-F";
	{
		LSystem s(axiom, {"F->FF"});

		/* the rule should fail to add because the is no '=>' in it.*/
		CHECK(s.GetNumRules() == 0);
	}
}

TEST_CASE("DOL System Basic") {

    const char *axiom = "F-F-F-F";
    {
        LSystem s(axiom, LSystem::svector());
        CHECK(strcmp(s.GetState(), axiom) == 0);
		CHECK(s.GetGeneration() == 0);
    }

    {
        const char *rule = "F=>F-F+F+FF-F-F+F";
        LSystem   s(axiom, {rule});
        CHECK(strcmp(s.GetState(), axiom) == 0);
        CHECK(s.GetNumRules() == 1);
        CHECK(s.GetRules().at('F')[0].to == "F-F+F+FF-F-F+F");
		CHECK(s.GetGeneration() == 0);
    }
}

/* basic DOL from page 4 of Algorithmic beauty of plants */
TEST_CASE("DOL System Iterate") {

	const char *axiom = "b";
	LSystem::svector rules = { "a=>ab", "b=>a" };
	LSystem   s(axiom, rules);

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
	LSystem::svector rules = { "a=>ab", "b=>a" };
	LSystem   s(axiom, rules);

	s.Iterate(5);
	CHECK(s.GetGeneration() == 5);
	CHECK(strcmp(s.GetState(), "abaababa") == 0);
}

TEST_CASE("Stochastic LSystems") {

	const char *axiom = "b";
	LSystem::svector rules = { 
		"a=10>ab", 
		"a=90>abb", 
		
		"b=>a" };

	LSystem   s(axiom, rules);
	CHECK(s.GetRules().at('a')[0].prob == 0.1f);
	CHECK(s.GetRules().at('a')[1].prob == 0.9f);
	CHECK(s.GetRules().at('b')[0].prob == 1.0f);
}

TEST_CASE("Context Sensitive LSystems") {

	const char *axiom = "b";
	LSystem::svector rules = { "a=>ab", "b=>a" };
	const char *ignore = "+-";
	LSystem   s(axiom, rules, ignore);
}
