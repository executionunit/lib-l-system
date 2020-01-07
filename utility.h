#ifndef EXUNIT_UTILITY_H
#define EXUNIT_UTILITY_H

#include "glm/glm.hpp"

/* given two points, return a valid matrix as if to-from were the forward axis 
** the orientation around that axis should be thought of as random
*/
glm::mat4x4 mtx_from_2_vectors(const glm::vec3 &from, const glm::vec3 &to);

#endif