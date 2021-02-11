#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#pragma once

#include <glm/glm.hpp>

#include <iosfwd>

using vec3 = glm::dvec3;
using point3 = vec3;
using color = glm::dvec3;

auto write_color(std::ostream& os, color const& pixel_color) -> void;
///
/// \param spp How many samples per pixel
///
/// This function will do the same thing as \ref write_color but will divide the color by `spp`.
///
auto write_color_over_samples(std::ostream& os, color const& pixel_color, int spp) -> void;

///
/// \returns A random number between 0.0 and 1.0
///
auto random_double() -> double;
///
/// \returns A random number between min and max
///
auto random_double_between(double min, double max) -> double;

#endif // !UTILITIES_HPP
