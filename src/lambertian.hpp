#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP
#pragma once

#include "material.hpp"

class lambertian : public material
{
private:
    color m_albedo{};

public:
    lambertian() noexcept = default;
    lambertian(lambertian const&) noexcept = default;
    lambertian(lambertian&&) noexcept = default;
    ~lambertian() noexcept override = default;

    explicit lambertian(color const& albedo);

    auto operator=(lambertian const&) noexcept -> lambertian& = default;
    auto operator=(lambertian&&) noexcept -> lambertian& = default;

    auto scatter(ray const& r_in, hit_record const& record, color& attenuation, ray& scattered) const noexcept
        -> bool override;
};

#endif // !LAMBERTIAN_HPP
