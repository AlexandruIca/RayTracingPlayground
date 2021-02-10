#include "sphere.hpp"

#include <glm/gtx/norm.hpp>

sphere::sphere(point3 const center, double const radius)
    : m_center{ center }
    , m_radius{ radius }
{
}

auto sphere::hit(ray const& r, double const t_min, double const t_max, hit_record& record) const noexcept -> bool
{
    auto const oc = r.origin() - m_center;
    auto const a = glm::length2(r.direction());
    auto const half_b = glm::dot(oc, r.direction());
    auto const c = glm::length2(oc) - m_radius * m_radius;
    auto const discriminant = half_b * half_b - a * c;

    if(discriminant < 0) {
        return false;
    }

    auto const sqrtd = glm::sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;

    if(root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;

        if(root < t_min || t_max < root) {
            return false;
        }
    }

    record.t = root;
    record.point = r.at(record.t);
    record.normal = (record.point - m_center) / m_radius;

    return true;
}
