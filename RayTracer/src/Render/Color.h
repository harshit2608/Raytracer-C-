#pragma once

#include "Math/Vec3.h"
#include "Math/MathUtil.h"
#include "rtpch.h"

namespace RayT
{
	void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
	{
		auto r = pixel_color.x();
		auto g = pixel_color.y();
		auto b = pixel_color.z();

		// Divide the color by the number of samples and gamma-correct for gamma=2.0.
		auto scale = 1.0 / samples_per_pixel;
		r = sqrt(scale * r);
		g = sqrt(scale * g);
		b = sqrt(scale * b);

		// Write the translated [0,255] value of each color component.
		out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';

		// int ir = static_cast<int>(255.999 * pixelColor.GetX());
		// int ig = static_cast<int>(255.999 * pixelColor.GetY());
		// int ib = static_cast<int>(255.999 * pixelColor.GetZ());
	}

	void write_color(uint8_t *pixels, int &index, color pixel_color, int samples_per_pixel)
	{
		auto r = pixel_color.x();
		auto g = pixel_color.y();
		auto b = pixel_color.z();

		// Divide the color by the number of samples and gamma-correct for gamma=2.0.
		auto scale = 1.0 / samples_per_pixel;
		r = sqrt(scale * r);
		g = sqrt(scale * g);
		b = sqrt(scale * b);

		int ir = static_cast<int>(255.999 * r);
		int ig = static_cast<int>(255.999 * g);
		int ib = static_cast<int>(255.999 * b);

		pixels[index++] = ib;
		pixels[index++] = ig;
		pixels[index++] = ir;
	}
}