#include <iostream>

#include <glm/glm.hpp>

auto main() -> int
{
    constexpr int image_width = 384;
    constexpr int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for(int i = 0; i < image_width; ++i) {
            auto const r = double(i) / (image_width - 1);
            auto const g = double(j) / (image_height - 1);
            auto const b = 0.25;

            constexpr double max_color = 255.999;

            std::cout << static_cast<int>(max_color * r) << ' ';
            std::cout << static_cast<int>(max_color * g) << ' ';
            std::cout << static_cast<int>(max_color * b) << '\n';
        }
    }

    std::cerr << "\nDone!" << std::endl;
}
