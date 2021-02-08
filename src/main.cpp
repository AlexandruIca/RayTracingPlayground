#include <iostream>

#include <glm/glm.hpp>

#include "ray.hpp"

auto write_color(std::ostream& os, glm::dvec3 const pixel_color) -> void
{
    constexpr double max_color = 255.999;

    os << static_cast<int>(max_color * pixel_color.r) << ' ';
    os << static_cast<int>(max_color * pixel_color.g) << ' ';
    os << static_cast<int>(max_color * pixel_color.b) << '\n';
}

[[nodiscard]] auto get_background(ray const& r)
{
    auto const unit_direction = glm::normalize(r.direction());
    auto const t = 0.5 * (unit_direction.y + 1.0);
    auto const random_color = glm::dvec3{ 0.5, 0.7, 1.0 };
    return (1.0 - t) * glm::dvec3{ 1.0, 1.0, 1.0 } + t * random_color;
}

auto main() -> int
{
    constexpr double aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 500;
    constexpr int image_height = static_cast<int>(static_cast<double>(image_width) / aspect_ratio);

    // camera
    constexpr double viewport_height = 2.0;
    constexpr double viewport_width = aspect_ratio * viewport_height;
    constexpr double focal_length = 1.0;

    auto const origin = glm::dvec3{ 0, 0, 0 };
    auto const horizontal = glm::dvec3{ viewport_width, 0, 0 };
    auto const vertical = glm::dvec3{ 0, viewport_height, 0 };
    auto const lower_left_corner = origin - horizontal * 0.5 - vertical * 0.5 - glm::dvec3{ 0, 0, focal_length };

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for(int i = 0; i < image_width; ++i) {
            auto const u = double(i) / (image_width - 1);
            auto const v = double(j) / (image_height - 1);
            ray const r{ origin, lower_left_corner + u * horizontal + v * vertical - origin };
            glm::dvec3 const pixel_color = get_background(r);

            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone!" << std::endl;
}
