#include "lambertian.hpp"
#include "hittable.hpp"
#include "utilities.hpp"

lambertian::lambertian(color const& albedo)
    : m_albedo{ albedo }
{
}

auto lambertian::scatter([[maybe_unused]] ray const& r_in,
                         hit_record const& record,
                         color& attenuation,
                         ray& scattered) const noexcept -> bool
{
    auto scatter_direction = record.normal + random_unit_vector();

    if(near_zero(scatter_direction)) {
        scatter_direction = record.normal;
    }

    scattered = ray{ record.point, scatter_direction };
    attenuation = m_albedo;
    return true;
}
