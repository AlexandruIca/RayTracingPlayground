#include <iostream>

#include <glm/gtx/norm.hpp>

#include "ray.hpp"
#include "utilities.hpp"

// We return:
// $ \frac{-b \pm \sqrt{b^2 - 4 a c}}{2a}$
// where $b = 2h$ so we can simplify to:
// $ \frac{-2h \pm 2 \sqrt{(2h)^2 - 4 a c}}{2a} = \frac{-h \pm \sqrt{h^2 - ac}}{a} $
[[nodiscard]] auto hit_sphere(point3 const& center, double const radius, ray const& r) -> double
{
    vec3 const oc = r.origin() - center;
    auto const a = glm::length2(r.direction());
    auto const half_b = glm::dot(oc, r.direction());
    auto const c = glm::length2(oc) - radius * radius;
    auto const discriminant = half_b * half_b - a * c;

    if(discriminant < 0) {
        return -1.0;
    }

    return (-half_b - std::sqrt(discriminant)) / a;
}

[[nodiscard]] auto get_background(ray const& r) -> color
{
    constexpr double sphere_radius = 0.5;
    constexpr double half = 0.5;

    auto t = hit_sphere(point3{ 0, 0, -1.0 }, sphere_radius, r);
    if(t > 0) {
        auto const normal = glm::normalize(r.at(t) - vec3{ 0, 0, -1.0 });
        return half * color{ normal.x + 1.0, normal.y + 1.0, normal.z + 1.0 };
    }

    auto const unit_direction = glm::normalize(r.direction());
    auto const blue = color{ 0.5, 0.7, 1.0 };
    auto const white = color{ 1.0, 1.0, 1.0 };

    t = half * (unit_direction.y + 1.0);
    return (1.0 - t) * white + t * blue;
}

auto main() -> int
{
    constexpr double aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 1400;
    constexpr int image_height = static_cast<int>(static_cast<double>(image_width) / aspect_ratio);

    // camera
    constexpr double viewport_height = 2.0;
    constexpr double viewport_width = aspect_ratio * viewport_height;
    constexpr double focal_length = 1.0;

    auto const origin = point3{ 0, 0, 0 };
    auto const horizontal = vec3{ viewport_width, 0, 0 };
    auto const vertical = vec3{ 0, viewport_height, 0 };
    auto const lower_left_corner = origin - horizontal * 0.5 - vertical * 0.5 - vec3{ 0, 0, focal_length };

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for(int i = 0; i < image_width; ++i) {
            auto const u = double(i) / (image_width - 1);
            auto const v = double(j) / (image_height - 1);
            ray const r{ origin, lower_left_corner + u * horizontal + v * vertical - origin };
            color const pixel_color = get_background(r);

            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone!" << std::endl;
}
