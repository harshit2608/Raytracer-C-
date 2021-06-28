#pragma once

#include "Math/MathUtil.h"
#include "Math/Vec3.h"

namespace RayT
{
	struct hit_record;

	class Material
	{
	public:
		virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered
		) const = 0;
	};

	class Lambertian : public Material {
	public:
		Lambertian(const color& a) : m_Albedo(a) {}

		virtual bool scatter(
			const Ray& r_in, const hit_record& record, color& attenuation, Ray& scattered) const override 
		{
			auto scatter_direction = record.normal + random_unit_vector();
			// Catch degenerate scatter direction
			if (scatter_direction.near_zero())
				scatter_direction = record.normal;
			scattered = Ray(record.p, scatter_direction);
			attenuation = m_Albedo;
			return true;
		}

	private:
		color m_Albedo;
	};

	class Metal : public Material {
	public:
		Metal(const color& a, double f) 
			: m_Albedo(a), m_Fuzz(f < 1 ? f : 1)
		{}

		Metal(const color& a) : m_Albedo(a) {}

		virtual bool scatter(
			const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered
		) const override {
			vec3 reflected = reflect(unit_vector(r_in.GetDirection()), rec.normal);
			scattered = Ray(rec.p, reflected);
			attenuation = m_Albedo;
			return (dot(scattered.GetDirection(), rec.normal) > 0);
		}

	private:
		color m_Albedo;
		double m_Fuzz;
	};

	class Dielectric : public Material {
	public:
		Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

		virtual bool scatter(
			const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered
		) const override {
			attenuation = color(1.0, 1.0, 1.0);
			double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

			vec3 unit_direction = unit_vector(r_in.GetDirection());
			double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
			double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

			bool cannot_refract = refraction_ratio * sin_theta > 1.0;
			vec3 direction;

			if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
				direction = reflect(unit_direction, rec.normal);
			else
				direction = refract(unit_direction, rec.normal, refraction_ratio);

			scattered = Ray(rec.p, direction);
			return true;
		}

	public:
		double ir; // Index of Refraction
	private:
		static double reflectance(double cosine, double ref_idx) {
			// Use Schlick's approximation for reflectance.
			auto r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow((1 - cosine), 5);
		}
	};
}

