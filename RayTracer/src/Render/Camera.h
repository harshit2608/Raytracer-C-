#pragma once

#include "Math/MathUtil.h"

namespace RayT
{
	class Camera
	{
	public:
		Camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist)
		{
			auto theta = degrees_to_radians(vfov);
			auto h = tan(theta / 2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = aspect_ratio * viewport_height;

			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);

			m_Origin = lookfrom;
			m_Horizontal = focus_dist * viewport_width * u;
			m_Vertical = focus_dist * viewport_height * v;
			m_Lower_left_corner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - focus_dist * w;

			lens_radius = aperture / 2;
		}


		Ray GetRay(double s, double t) const {
			vec3 rd = lens_radius * random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();

			return Ray(
				m_Origin + offset,
				m_Lower_left_corner + s * m_Horizontal + t * m_Vertical - m_Origin - offset
			);
		}

	private:
		point3 m_Origin;
		point3 m_Lower_left_corner;
		vec3 m_Horizontal;
		vec3 m_Vertical;
		vec3 u, v, w;
		double lens_radius;
	};
}
