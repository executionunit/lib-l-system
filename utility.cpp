#include "glm/glm.hpp"

using namespace glm;

glm::mat4x4 mtx_from_2_vectors(const vec3 &from, const vec3 &to) {

	vec3 up(0, 1, 0);
	vec3 right(1, 0, 0);

	vec3 axis1 = glm::normalize(from - to);
	//create a matrix, so we need to check for parallel vectors first!
	const auto &test = fabs(glm::dot(axis1, up)) > 0.99 ? right : up;
	vec3 axis2 = glm::cross(test, axis1);

	return glm::mat4x4(glm::vec4(axis2, 0.0f), glm::vec4(test, 0.0f), glm::vec4(axis1, 0.0f), glm::vec4(from, 1.0f));

}