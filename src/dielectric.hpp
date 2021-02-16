#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP
#pragma once

#include "material.hpp"

class dielectric : public material
{
private:
    double m_refraction_index{ 0 };

public:
    dielectric() noexcept = default;
    dielectric(dielectric const&) noexcept = default;
    dielectric(dielectric&&) noexcept = default;
    ~dielectric() noexcept override = default;

    explicit dielectric(double refraction_index) noexcept;

    auto operator=(dielectric const&) noexcept -> dielectric& = default;
    auto operator=(dielectric&&) noexcept -> dielectric& = default;

    auto scatter(ray const& ray_in, hit_record const& record, color& attenuation, ray& scattered) const noexcept
        -> bool override;
};

#endif // !DIELECTRIC_HPP
