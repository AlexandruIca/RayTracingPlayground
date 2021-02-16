#ifndef CAMERA_HPP
#define CAMERA_HPP
#pragma once

#include "ray.hpp"
#include "utilities.hpp"

struct camera_parameters
{
    static constexpr double s_default_aspect_ratio = 16.0 / 9.0;
    double aspect_ration = s_default_aspect_ratio;

    static constexpr double s_default_viewport_height = 2.0;
    double viewport_height = s_default_viewport_height;

    static constexpr double s_default_focal_length = 1.0;
    double focal_length = s_default_focal_length;

    static constexpr double s_default_vert_fov = 90.0;
    double vert_fov = s_default_vert_fov;

    static constexpr double s_default_aperture = 1.0;
    double aperture = s_default_aperture;

    static constexpr double s_default_focus_distance = 1.0;
    double focus_distance = s_default_focus_distance;

    point3 lookfrom{ 0, 0, 0 };
    point3 lookat{ 0, 0, -1 };
    vec3 up{ 0, 1, 0 };
};

class camera
{
private:
    point3 m_origin{};
    vec3 m_horizontal{};
    vec3 m_vertical{};
    point3 m_lower_left_corner{};
    vec3 m_u{};
    vec3 m_v{};
    vec3 m_w{};
    double m_lens_radius{};

public:
    camera() noexcept;
    camera(camera const&) noexcept = default;
    camera(camera&&) noexcept = default;
    ~camera() noexcept = default;

    explicit camera(camera_parameters parameters) noexcept;

    auto operator=(camera const&) noexcept -> camera& = default;
    auto operator=(camera&&) noexcept -> camera& = default;

    [[nodiscard]] auto get_ray(double s, double t) const noexcept -> ray;
};

#endif // !CAMERA_HPP
