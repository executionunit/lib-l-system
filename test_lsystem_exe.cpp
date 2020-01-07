#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "utility.h"

using namespace glm;


TEST_CASE("Stupid Maths Stuff") {

	/* testing we're getting right handed coordinate systems */
	{
		vec3 from(0.0f, 0.0f, 0.0f);
		vec3 to(0.0f, 1.0f, 0.0f);

		auto mat = mtx_from_2_vectors(from, to);
		CHECK(mat[0] == vec4(0, 0, -1, 0) );
		CHECK(mat[1] == vec4(1, 0, 0, 0));
		CHECK(mat[2] == vec4(0, -1, 0, 0));
	}


	{
		vec3 from(0.0f, 0.0f, 0.0f);
		vec3 to(0.0f, 0.0f, -1.0f);

		auto mat = mtx_from_2_vectors(from, to);
		CHECK(mat[0] == vec4(1, 0, 0, 0));
		CHECK(mat[1] == vec4(0, 1, 0, 0));
		CHECK(mat[2] == vec4(0, 0, 1, 0));
	}

}