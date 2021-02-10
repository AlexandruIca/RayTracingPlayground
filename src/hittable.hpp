#ifndef HITTABLE_HPP
#define HITTABLE_HPP
#pragma once

#include "ray.hpp"
#include "utilities.hpp"

struct hit_record
{
    point3 point{};
    vec3 normal{};
    double t = 0.0;
};

class hittable
{
public:
    hittable() noexcept = default;
    hittable(hittable const&) noexcept = default;
    hittable(hittable&&) noexcept = default;
    virtual ~hittable() noexcept = default;

    auto operator=(hittable const&) noexcept -> hittable& = default;
    auto operator=(hittable&&) noexcept -> hittable& = default;

    [[nodiscard]] virtual auto hit(ray const& r, double t_min, double t_max, hit_record& record) const noexcept
        -> bool = 0;
};

#endif // !HITTABLE_HPP
