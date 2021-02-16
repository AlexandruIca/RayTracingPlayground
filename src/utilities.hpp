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
/// \param spp How many samples per pixel.
///
/// This function will do the same thing as \ref write_color but will divide the color by `spp`.
///
auto write_color_over_samples(std::ostream& os, color const& pixel_color, int spp) -> void;

///
/// \returns A random number between 0.0 and 1.0.
///
auto random_double() -> double;
///
/// \returns A random number between min and max.
///
auto random_double_between(double min, double max) -> double;

///
/// \returns A \ref vec3 whose components are all a \ref random_double.
///
auto random_vec3() -> vec3;
///
/// \returns A \ref vec3 whose components are all a \ref random_double_between `min` and `max`.
///
auto random_vec3_between(double min, double max) -> vec3;

///
/// \returns A random point that is inside the unit sphere(the sphere in the cube of volume 1).
///
auto random_in_unit_sphere() -> vec3;
///
/// \returns A random point that is _on_ the unit sphere.
///
auto random_unit_vector() -> vec3;

auto near_zero(vec3 const& vec) -> bool;

auto reflect(vec3 const& vec, vec3 const& normal) -> vec3;
auto refract(vec3 const& uv, vec3 const& normal, double etai_over_etat) -> vec3;

auto random_in_unit_disk() -> vec3;

#endif // !UTILITIES_HPP
