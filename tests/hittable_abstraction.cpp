#include <iostream>
#include <limits>

#include <glm/gtx/norm.hpp>

#include "ray.hpp"
#include "sphere.hpp"
#include "utilities.hpp"

[[nodiscard]] auto get_background(ray const& r) -> color
{
    constexpr double sphere_radius = 0.5;
    constexpr double half = 0.5;

    auto const entity = sphere{ point3{ 0, 0, -1.0 }, sphere_radius };
    hit_record record{};
    bool const hit = entity.hit(r, 0, std::numeric_limits<double>::max(), record);

    if(hit) {
        return half * color{ record.normal.x + 1.0, record.normal.y + 1.0, record.normal.z + 1.0 };
    }

    auto const unit_direction = glm::normalize(r.direction());
    auto const blue = color{ 0.5, 0.7, 1.0 };
    auto const white = color{ 1.0, 1.0, 1.0 };

    auto const t = half * (unit_direction.y + 1.0);
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
