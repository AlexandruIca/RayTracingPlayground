#include <iostream>

#include "common.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

[[nodiscard]] auto ray_color(ray const& r, hittable const& world) -> color
{
    constexpr double half = 0.5;
    auto const blue = color{ 0.5, 0.7, 1.0 };
    auto const white = color{ 1.0, 1.0, 1.0 };
    hit_record record{};

    if(world.hit(r, 0, infinity, record)) {
        return half * (record.normal + color{ 1, 1, 1 });
    }

    vec3 const unit_direction = glm::normalize(r.direction());
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

    hittable_list world{};

    world.add(std::make_unique<sphere>(point3{ 0, 0, -1.0 }, 0.5));        // NOLINT
    world.add(std::make_unique<sphere>(point3{ 0, -100.5, -1.0 }, 100.0)); // NOLINT

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for(int i = 0; i < image_width; ++i) {
            auto const u = double(i) / (image_width - 1);
            auto const v = double(j) / (image_height - 1);
            ray const r{ origin, lower_left_corner + u * horizontal + v * vertical - origin };
            color const pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone!" << std::endl;
}
