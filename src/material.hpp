#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#pragma once

#include "ray.hpp"
#include "utilities.hpp"

struct hit_record;

class material
{
public:
    material() noexcept = default;
    material(material const&) noexcept = default;
    material(material&&) noexcept = default;
    virtual ~material() noexcept = default;

    auto operator=(material const&) noexcept -> material& = default;
    auto operator=(material&&) noexcept -> material& = default;

    virtual auto scatter(ray const& r, hit_record const& record, color& attenuation, ray& scattered) const noexcept
        -> bool = 0;
};

#endif // !MATERIAL_HPP
