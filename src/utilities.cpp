#include "utilities.hpp"

#include <algorithm>
#include <iostream>
#include <random>

#include <glm/gtx/norm.hpp>

auto write_color(std::ostream& os, color const& pixel_color) -> void
{
    constexpr double max_color = 255.999;

    os << static_cast<int>(max_color * pixel_color.r) << ' ';
    os << static_cast<int>(max_color * pixel_color.g) << ' ';
    os << static_cast<int>(max_color * pixel_color.b) << '\n';
}

auto write_color_over_samples(std::ostream& os, color const& pixel_color, int const spp) -> void
{
    constexpr double max_factor = 0.999;
    constexpr double max_color = 256.0;

    auto r = pixel_color.r;
    auto g = pixel_color.g;
    auto b = pixel_color.b;

    auto const scale = 1.0 / double(spp);

    // gamma 2
    r = glm::sqrt(scale * r);
    g = glm::sqrt(scale * g);
    b = glm::sqrt(scale * b);

    os << static_cast<int>(max_color * std::clamp(r, 0.0, max_factor)) << ' '
       << static_cast<int>(max_color * std::clamp(g, 0.0, max_factor)) << ' '
       << static_cast<int>(max_color * std::clamp(b, 0.0, max_factor)) << '\n';
}

auto random_double() -> double
{
    static std::mt19937 rng{ std::random_device{}() };
    static std::uniform_real_distribution<double> dist{ 0.0, 1.0 };
    return dist(rng);
}

auto random_double_between(double const min, double const max) -> double
{
    // developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random#getting_a_random_number_between_two_values
    return min + (max - min) * random_double();
}

auto random_vec3() -> vec3
{
    return vec3{ random_double(), random_double(), random_double() };
}

auto random_vec3_between(double const min, double const max) -> vec3
{
    return vec3{ random_double_between(min, max), random_double_between(min, max), random_double_between(min, max) };
}

auto random_in_unit_sphere() -> vec3
{
    for(;;) {
        auto const point = random_vec3_between(-1.0, 1.0);

        if(glm::length2(point) >= 1) {
            continue;
        }

        return point;
    }
}

auto random_unit_vector() -> vec3
{
    return glm::normalize(random_in_unit_sphere());
}

auto near_zero(vec3 const& vec) -> bool
{
    constexpr double eps = 1e-8;
    return glm::abs(vec.x) < eps && glm::abs(vec.y) < eps && glm::abs(vec.z) < eps;
}

auto reflect(vec3 const& vec, vec3 const& normal) -> vec3
{
    return vec - 2 * glm::dot(vec, normal) * normal;
}

auto refract(vec3 const& uv, vec3 const& normal, double const etai_over_etat) -> vec3
{
    auto const cos_theta = glm::min(glm::dot(-uv, normal), 1.0);
    vec3 const r_out_perp = etai_over_etat * (uv + cos_theta * normal);
    vec3 const r_out_parallel = -glm::sqrt(glm::abs(1.0 - glm::length2(r_out_perp))) * normal;

    return r_out_perp + r_out_parallel;
}

auto random_in_unit_disk() -> vec3
{
    while(true) {
        auto const p = vec3{ random_double_between(-1, 1), random_double_between(-1, 1), 0 };

        if(glm::length2(p) >= 1) {
            continue;
        }

        return p;
    }
}
