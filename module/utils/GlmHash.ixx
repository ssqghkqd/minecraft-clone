module;
#include <glm/vec3.hpp>
export module utils.glm_hash;

export namespace std
{
template <>
struct hash<glm::ivec3>
{
    size_t operator()(const glm::ivec3& vec) const noexcept
    {

        return ((hash<int>()(vec.x) ^
                 (hash<int>()(vec.y) << 1)) >>
                1) ^
               (hash<int>()(vec.z) << 1);
    }
};
} // namespace std

export namespace glm
{
bool operator==(const ivec3& a, const ivec3& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
} // namespace glm