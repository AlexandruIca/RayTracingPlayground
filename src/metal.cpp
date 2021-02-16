#include "metal.hpp"

#include "hittable.hpp"
#include "utilities.hpp"

metal::metal(color const& albedo) noexcept
    : m_albedo{ albedo }
{
}

metal::metal(color const& albedo, double const fuzz_factor) noexcept
    : m_albedo{ albedo }
    , m_fuzz_factor{ fuzz_factor }
{
}

auto metal::scatter(ray const& ray_in, hit_record const& record, color& attenuation, ray& scattered) const noexcept
    -> bool
{
    auto const reflected = reflect(glm::normalize(ray_in.direction()), record.normal);
    scattered = ray{ record.point, reflected + m_fuzz_factor * random_in_unit_sphere() };
    attenuation = m_albedo;

    return glm::dot(scattered.direction(), record.normal) > 0;
}
