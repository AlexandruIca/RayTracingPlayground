#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#pragma once

#include <glm/glm.hpp>

#include <iosfwd>

using vec3 = glm::dvec3;
using point3 = vec3;
using color = glm::dvec3;

auto write_color(std::ostream& os, color const& pixel_color) -> void;

#endif // !UTILITIES_HPP
