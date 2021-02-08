#include "ray.hpp"

ray::ray(glm::dvec3 const& origin, glm::dvec3 const& direction)
    : m_origin{ origin }
    , m_direction{ direction }
{
}

auto ray::origin() const noexcept -> glm::dvec3 const&
{
    return m_origin;
}

auto ray::direction() const noexcept -> glm::dvec3 const&
{
    return m_direction;
}

auto ray::at(double const t) const noexcept -> glm::dvec3
{
    return m_origin + t * m_direction;
}
