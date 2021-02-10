#include "hittable.hpp"

#include <glm/glm.hpp>

auto set_face_normal(hit_record& record, ray const& r, vec3 const& outward_normal) noexcept -> void
{
    record.front_face = glm::dot(r.direction(), outward_normal) < 0;
    record.normal = record.front_face ? outward_normal : -outward_normal;
}
