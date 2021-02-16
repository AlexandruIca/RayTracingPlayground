#include "camera.hpp"

camera::camera() noexcept
    : camera{ camera_parameters{} }
{
}

camera::camera(camera_parameters const parameters) noexcept
    : m_origin{ 0, 0, 0 }
    , m_horizontal{}
    , m_vertical{}
    , m_lower_left_corner{}
{
    constexpr double half = 0.5;
    auto const theta = glm::radians(parameters.vert_fov);
    auto const h = glm::tan(theta * 0.5);
    auto const viewport_height = 2.0 * h;
    auto const viewport_width = parameters.aspect_ration * viewport_height;

    m_horizontal = vec3{ viewport_width, 0.0, 0.0 };
    m_vertical = vec3{ 0.0, viewport_height, 0.0 };
    m_lower_left_corner = m_origin - half * m_horizontal - half * m_vertical - vec3{ 0, 0, parameters.focal_length };
}

auto camera::get_ray(double const u, double const v) const noexcept -> ray
{
    return ray{ m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin };
}
