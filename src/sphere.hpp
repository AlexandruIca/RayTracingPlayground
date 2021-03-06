#ifndef SPHERE_HPP
#define SPHERE_HPP
#pragma once

#include "hittable.hpp"
#include "material.hpp"

#include <memory>

class sphere : public hittable
{
private:
    point3 m_center{};
    double m_radius{};
    std::shared_ptr<material> m_material{ nullptr };

public:
    sphere() noexcept = default;
    sphere(sphere const&) noexcept = default;
    sphere(sphere&&) noexcept = default;
    ~sphere() noexcept override = default;

    sphere(point3 center, double radius);
    sphere(point3 center, double radius, std::shared_ptr<material> material);

    auto operator=(sphere const&) noexcept -> sphere& = default;
    auto operator=(sphere&&) noexcept -> sphere& = default;

    auto hit(ray const& r, double t_min, double t_max, hit_record& record) const noexcept -> bool override;
};

#endif // !SPHERE_HPP
