#ifndef RAY_HPP
#define RAY_HPP
#pragma once

#include <glm/glm.hpp>

struct ray
{
private:
    glm::dvec3 m_origin;
    glm::dvec3 m_direction;

public:
    ray() noexcept = default;
    ray(ray const&) noexcept = default;
    ray(ray&&) noexcept = default;
    ~ray() noexcept = default;

    ray(glm::dvec3 const& origin, glm::dvec3 const& direction);

    auto operator=(ray const&) noexcept -> ray& = default;
    auto operator=(ray&&) noexcept -> ray& = default;

    [[nodiscard]] auto origin() const noexcept -> glm::dvec3 const&;
    [[nodiscard]] auto direction() const noexcept -> glm::dvec3 const&;
    [[nodiscard]] auto at(double t) const noexcept -> glm::dvec3;
};

#endif // !RAY_HPP
