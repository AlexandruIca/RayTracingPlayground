#include "hittable_list.hpp"

#include <utility>

auto hittable_list::clear() -> void
{
    m_objects.clear();
}

auto hittable_list::add(std::unique_ptr<hittable> object) -> void
{
    m_objects.push_back(std::move(object));
}

auto hittable_list::hit(ray const& r, double const t_min, double const t_max, hit_record& record) const noexcept -> bool
{
    hit_record temp_record{};
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(auto const& object : m_objects) {
        if(object->hit(r, t_min, closest_so_far, temp_record)) {
            hit_anything = true;
            closest_so_far = temp_record.t;
            record = temp_record;
        }
    }

    return hit_anything;
}
