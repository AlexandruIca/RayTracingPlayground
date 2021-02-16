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

    m_w = glm::normalize(parameters.lookfrom - parameters.lookat);
    m_u = glm::normalize(glm::cross(parameters.up, m_w));
    m_v = glm::cross(m_w, m_u);

    m_origin = parameters.lookfrom;
    m_horizontal = parameters.focus_distance * viewport_width * m_u;
    m_vertical = parameters.focus_distance * viewport_height * m_v;
    m_lower_left_corner = m_origin - half * m_horizontal - half * m_vertical - parameters.focus_distance * m_w;
    m_lens_radius = half * parameters.aperture;
}

auto camera::get_ray(double const s, double const t) const noexcept -> ray
{
    vec3 const rd = m_lens_radius * random_in_unit_disk();
    vec3 const offset = m_u * rd.x + m_v * rd.y;

    return ray{ m_origin + offset, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin - offset };
}
