#include <array>
#include <iostream>

#include "camera.hpp"
#include "common.hpp"
#include "dielectric.hpp"
#include "hittable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
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

auto random_scene(hittable_list& world) -> void
{
    auto const mid_color = color{ 0.5, 0.5, 0.5 };
    auto ground_material = std::make_shared<lambertian>(mid_color);

    auto const ground_center = point3{ 0, -1000, 0 };
    constexpr auto ground_radius = 1000.0;
    world.add(std::make_unique<sphere>(ground_center, ground_radius, ground_material));

    constexpr int num_iterations = 11;

    for(int a = -num_iterations; a < num_iterations; ++a) {
        for(int b = -num_iterations; b < num_iterations; ++b) {
            auto const choose_material = random_double();
            auto const center = point3{ a + 0.9 * random_double(), 0.2, b + 0.9 * random_double() };
            auto const random_point = point3{ 4, 0.2, 0 };

            constexpr double sphere_radius = 0.2;
            constexpr double max_length = 0.9;
            constexpr double lambertian_threshold = 0.8;
            constexpr double metal_threshold = 0.95;

            if(glm::length(center - random_point) > max_length) {
                std::shared_ptr<material> sphere_material{ nullptr };

                if(choose_material < lambertian_threshold) {
                    auto const albedo = random_vec3() * random_vec3();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(std::make_unique<sphere>(center, sphere_radius, sphere_material));
                }
                else if(choose_material < metal_threshold) {
                    auto const albedo = random_vec3_between(0.5, 1);
                    auto const fuzz = random_double_between(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_unique<sphere>(center, sphere_radius, sphere_material));
                }
                else {
                    constexpr double refraction_index = 1.5;
                    sphere_material = std::make_shared<dielectric>(refraction_index);
                    world.add(std::make_unique<sphere>(center, sphere_radius, sphere_material));
                }
            }
        }
    }

    constexpr double refraction_index = 1.5;
    auto material1 = std::make_shared<dielectric>(refraction_index);
    world.add(std::make_unique<sphere>(point3{ 0, 1, 0 }, 1.0, material1));

    auto const dark = color{ 0.4, 0.2, 0.1 };
    auto material2 = std::make_shared<lambertian>(dark);
    world.add(std::make_unique<sphere>(point3{ -4, 1, 0 }, 1.0, material2));

    auto const brownish = color{ 0.7, 0.6, 0.5 };
    auto material3 = std::make_shared<metal>(brownish, 0.0);
    world.add(std::make_unique<sphere>(point3{ 4, 1, 0 }, 1.0, material3));
}

auto main() -> int
{
    constexpr double aspect_ratio = 3.0 / 2.0;
    constexpr int image_width = 240;
    constexpr int image_height = static_cast<int>(static_cast<double>(image_width) / aspect_ratio);
    constexpr int samples_per_pixel = 3;
    constexpr int max_depth = 3;
    constexpr int vfov = 20.0;

    camera_parameters params{};
    params.lookfrom = point3{ 13, 2, 3 }; // NOLINT
    params.lookat = point3{ 0, 0, 0 };
    params.up = vec3{ 0, 1, 0 };
    params.vert_fov = vfov;
    params.aperture = 0.1;        // NOLINT
    params.focus_distance = 10.0; // NOLINT

    camera cam{ params };
    hittable_list world{};

    random_scene(world);

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
