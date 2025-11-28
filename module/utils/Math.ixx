module;
#include "glm/vec3.hpp"
export module utils.maths;

export namespace mc::Maths
{
float normalizeAngle(float angle);
glm::vec3 calculateForward(float pitch, float yaw);
}