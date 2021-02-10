#ifndef COMMON_HPP
#define COMMON_HPP
#pragma once

#include <limits>

#include "ray.hpp"
#include "utilities.hpp"

[[maybe_unused]] constexpr double infinity = std::numeric_limits<double>::infinity();
[[maybe_unused]] constexpr double pi = 3.1415926535897932385;

[[nodiscard]] constexpr auto degrees_to_radians(double const degrees) noexcept -> double
{
    constexpr double half_circle = 180.0;
    return degrees * pi / half_circle;
}

#endif // !COMMON_HPP
