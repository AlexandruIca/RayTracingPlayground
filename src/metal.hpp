#ifndef METAL_HPP
#define METAL_HPP
#pragma once

#include "material.hpp"

class metal : public material
{
private:
    color m_albedo{};

public:
    metal() noexcept = default;
    metal(metal const&) noexcept = default;
    metal(metal&&) noexcept = default;
    ~metal() noexcept override = default;

    explicit metal(color const& albedo) noexcept;

    auto operator=(metal const&) noexcept -> metal& = default;
    auto operator=(metal&&) noexcept -> metal& = default;

    auto scatter(ray const& ray_in, hit_record const& record, color& attenuation, ray& scattered) const noexcept
        -> bool override;
};

#endif // !METAL_HPP
