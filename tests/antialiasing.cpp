#include <iostream>

#include "camera.hpp"
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
    constexpr int image_width = 560;
    constexpr int image_height = static_cast<int>(static_cast<double>(image_width) / aspect_ratio);
    constexpr int samples_per_pixel = 25;

    camera cam{};
    hittable_list world{};

    world.add(std::make_unique<sphere>(point3{ 0, 0, -1.0 }, 0.5));        // NOLINT
    world.add(std::make_unique<sphere>(point3{ 0, -100.5, -1.0 }, 100.0)); // NOLINT

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for(int i = 0; i < image_width; ++i) {
            color pixel_color{ 0, 0, 0 };

            for(int s = 0; s < samples_per_pixel; ++s) {
                auto const u = (i + random_double()) / (image_width - 1);
                auto const v = (j + random_double()) / (image_height - 1);
                ray const r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }

            write_color_over_samples(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone!" << std::endl;
}
