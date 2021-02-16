#include "dielectric.hpp"

#include "hittable.hpp"

dielectric::dielectric(double const refraction_index) noexcept
    : m_refraction_index{ refraction_index }
{
}

auto dielectric::scatter(ray const& ray_in, hit_record const& record, color& attenuation, ray& scattered) const noexcept
    -> bool
{
    attenuation = color{ 1.0, 1.0, 1.0 };
    double const refraction_ratio = record.front_face ? (1.0 / m_refraction_index) : m_refraction_index;
    auto const unit_direction = glm::normalize(ray_in.direction());

    double const cos_theta = glm::min(glm::dot(-unit_direction, record.normal), 1.0);
    double const sin_theta = glm::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction{};

    auto reflectance = [](double const cosine, double const ref_idx) noexcept -> double {
        constexpr int offset = 5;
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 *= r0;
        return r0 + (1 - r0) * glm::pow((1 - cosine), offset);
    };

    if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
        direction = reflect(unit_direction, record.normal);
    }
    else {
        direction = refract(unit_direction, record.normal, refraction_ratio);
    }

    scattered = ray{ record.point, direction };

    return true;
}
