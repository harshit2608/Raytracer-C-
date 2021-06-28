#include "rtpch.h"

#include "Math/MathUtil.h"
#include "Math/Vec3.h"
#include "Render/Color.h"
#include "Render/Shapes/Sphere.h"
#include "Render/Hittable_list.h"
#include "Render/Camera.h"
#include "Render/Ray.h"
#include "Render/Hittable.h"
#include "Render/Material.h"
#include "Render/Image.h"

using namespace RayT;

color ray_color(const Ray &r, const Hittable &world, int depth)
{
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec))
	{
		Ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}

	vec3 unit_direction = unit_vector(r.GetDirection());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

HittableList random_scene()
{
	HittableList world;

	auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9)
			{
				shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<Lambertian>(albedo);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<Metal>(albedo, fuzz);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = make_shared<Dielectric>(1.5);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5);
	world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}

int main()
{
	// Image

	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 800;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500;
	const int max_depth = 5;

	// World

	auto world = random_scene();

	// Camera

	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	// Render

	//std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	//auto worker = [&](size_t tileX,size_t tile_width,size_t tileY, size_t tile_height)
	//{
	//	for (size_t j = tileY; j <tileY+tile_height; j++)
	//	{
	//		std::cerr << "\rScanlines Done: " << j << " / "<<tileY+tile_height-1 << " --- " << std::flush;
	//		for (size_t i = tileX; i < tileX+tile_width; ++i)
	//		{
	//			color pixel_color(0, 0, 0);
	//			for (size_t s = 0; s < samples_per_pixel; ++s)
	//			{
	//				auto u = (i + random_double()) / (image_width-1);
	//				auto v = (j + random_double()) / (image_height-1);
	//				Ray r = cam.GetRay(u, v);
	//				pixel_color += ray_color(r, world, max_depth);
	//			}
	//			write_color(std::cout, pixel_color, samples_per_pixel);
	//		}
	//	}
	//};
#define CHANNEL_NUM 3

	uint8_t *pixels = new uint8_t[image_width * image_height * CHANNEL_NUM];
	int index = 0;
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " / " <<image_height<<' '<< std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				Ray r = cam.GetRay(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(pixels, index, pixel_color, samples_per_pixel);
		}
	}

	tga_write("test.tga", image_width, image_height, pixels, 3, 3);
	delete[] pixels;
	//worker(0, image_width, 0, image_height);

	//float avg_time = 0.0;
	//for (int i = 0; i < 1; ++i)
	//{
	//	/*auto start = std::chrono::system_clock::now();*/
	//	std::vector<std::thread> threads;
	//
	//	static const size_t horizontal_tiles = 4;
	//	static const size_t vertical_tiles = 2;
	//
	//	const size_t tile_w = image_width / horizontal_tiles;
	//	const size_t tile_h = image_height / vertical_tiles;
	//	for (size_t tx = 0; tx < horizontal_tiles; tx++)
	//	{
	//		for (size_t ty = 0; ty < vertical_tiles; ty++)
	//		{
	//			threads.emplace_back(
	//				[&worker, tx, ty,tile_w,tile_h]()
	//				{
	//					worker(tx * tile_w, tile_w, ty * tile_h, tile_h);
	//				});
	//		}
	//	}
	//	for (auto& t : threads) { t.join(); }
	//
	//worker(0, image_width, 0, image_height);

	/*auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> elasped_seconds = end - start;
		avg_time += elasped_seconds.count();
		std::cout << "Iteration" << i << "time is " << elasped_seconds.count() << " with average time of "<<avg_time <<std::endl;*/
	//}

	/*std::thread t1([&worker]() {worker(0, 200, 0, 200); });
	std::thread t2([&worker]() {worker(200, 200, 0, 200); });
	t1.join(); t2.join();*/

	std::cerr << "\nDone.\n";
}