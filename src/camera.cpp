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
    auto const h = glm::tan(half * theta);
    auto const viewport_height = 2.0 * h;
    auto const viewport_width = parameters.aspect_ration * viewport_height;

    auto const w = glm::normalize(parameters.lookfrom - parameters.lookat);
    auto const u = glm::normalize(glm::cross(parameters.up, w));
    auto const v = glm::cross(w, u);

    m_origin = parameters.lookfrom;
    m_horizontal = viewport_width * u;
    m_vertical = viewport_height * v;
    m_lower_left_corner = m_origin - half * m_horizontal - half * m_vertical - w;
}

auto camera::get_ray(double const s, double const t) const noexcept -> ray
{
    return ray{ m_origin, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin };
}
