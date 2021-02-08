#include <iostream>

#include <glm/glm.hpp>

auto write_color(std::ostream& os, glm::dvec3 const pixel_color) -> void
{
    constexpr double max_color = 255.999;

    os << static_cast<int>(max_color * pixel_color.r) << ' ';
    os << static_cast<int>(max_color * pixel_color.g) << ' ';
    os << static_cast<int>(max_color * pixel_color.b) << '\n';
}

auto main() -> int
{
    constexpr int image_width = 384;
    constexpr int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for(int i = 0; i < image_width; ++i) {
            constexpr double arbitrary = 0.25;
            auto pixel_color = glm::dvec3{ double(i) / (image_width - 1), double(j) / (image_height - 1), arbitrary };
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone!" << std::endl;
}
