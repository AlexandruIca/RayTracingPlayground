#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP
#pragma once

#include <memory>
#include <vector>

#include "hittable.hpp"

class hittable_list : public hittable
{
private:
    std::vector<std::unique_ptr<hittable>> m_objects;

public:
    hittable_list() = default;
    hittable_list(hittable_list const&) = default;
    hittable_list(hittable_list&&) = default;
    ~hittable_list() noexcept override = default;

    auto operator=(hittable_list const&) -> hittable_list& = default;
    // clang-format off
    auto operator=(hittable_list&&) -> hittable_list& = default;
    // clang-format off

    auto clear() -> void;
    auto add(std::unique_ptr<hittable> object) -> void;

    [[nodiscard]] auto hit(ray const& r, double t_min, double t_max, hit_record& record) const noexcept
        -> bool override;
};

#endif // !HITTABLE_LIST_HPP
