#include "metal.hpp"

#include "hittable.hpp"
#include "utilities.hpp"

metal::metal(color const& albedo) noexcept
    : m_albedo{ albedo }
{
}

auto metal::scatter(ray const& ray_in, hit_record const& record, color& attenuation, ray& scattered) const noexcept
    -> bool
{
    auto const reflected = reflect(glm::normalize(ray_in.direction()), record.normal);
    scattered = ray{ record.point, reflected };
    attenuation = m_albedo;

    return glm::dot(scattered.direction(), record.normal) > 0;
}
