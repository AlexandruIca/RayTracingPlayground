#include <iostream>

#include "camera.hpp"
#include "common.hpp"
#include "hittable_list.hpp"
#include "lambertian.hpp"
#include "sphere.hpp"

[[nodiscard]] auto ray_color(ray const& r, hittable const& world, int const max_depth) -> color
{
    constexpr double half = 0.5;
    constexpr double min_threshold = 0.001;
    auto const blue = color{ 0.5, 0.7, 1.0 };
    auto const white = color{ 1.0, 1.0, 1.0 };
    auto const black = color{ 0, 0, 0 };
    hit_record record{};

    if(max_depth <= 0) {
        return black;
    }

    if(world.hit(r, min_threshold, infinity, record)) {
        ray scattered{};
        color attenuation{};

        if(record.material_ref->scatter(r, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, max_depth - 1);
        }

        return black;
    }

    vec3 const unit_direction = glm::normalize(r.direction());
    auto const t = half * (unit_direction.y + 1.0);
    return (1.0 - t) * white + t * blue;
}

auto main() -> int
{
    constexpr double aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 540;
    constexpr int image_height = static_cast<int>(static_cast<double>(image_width) / aspect_ratio);
    constexpr int samples_per_pixel = 5;
    constexpr int max_depth = 5;

    camera cam{};
    hittable_list world{};

    color const yellowish = color{ 0.8, 0.8, 0.0 };
    color const brownish = color{ 0.7, 0.3, 0.3 };

    auto material_ground = std::make_shared<lambertian>(yellowish);
    auto material_ball = std::make_shared<lambertian>(brownish);

    world.add(std::make_unique<sphere>(point3{ 0, 0, -1.0 }, 0.5, material_ball));          // NOLINT
    world.add(std::make_unique<sphere>(point3{ 0, -100.5, -1.0 }, 100.0, material_ground)); // NOLINT

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for(int i = 0; i < image_width; ++i) {
            color pixel_color{ 0, 0, 0 };

            for(int s = 0; s < samples_per_pixel; ++s) {
                auto const u = (i + random_double()) / (image_width - 1);
                auto const v = (j + random_double()) / (image_height - 1);
                ray const r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color_over_samples(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone!" << std::endl;
}
