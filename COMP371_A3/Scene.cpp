#include "stdafx.h"
#include "Scene.h"
#include "primitive.h"
#include "plane.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"
#include <string>
#include <memory>
#include <tuple>
#include "Ray.h"
#include <iostream>


Scene::Scene(const std::string& filename)
	: m_file(filename)
	, ambientColour(255.0f)
{
	read();
}


Scene::~Scene() {}


void Scene::setCamera(const Camera& camera)
{
	m_camera = camera;
}


void Scene::addPrimitive(std::unique_ptr<Primitive> primitive)
{
	m_primitives.push_back(std::move(primitive));
}


void Scene::addLight(const Light& light)
{
	m_lights.push_back(light);
}


std::tuple<bool, glm::vec3, Primitive*> Scene::closestPrimitiveIntersection(const int i, const int j) const
{
	const auto ray = m_camera.rayThroughPixel(i, j);
	bool intersectsAny = false;
	float t;
	Primitive* closest;
	for (auto const& primitive : m_primitives)
	{
		const auto intersection = primitive->intersection(ray);
		if (intersection.first)
		{
			if (!intersectsAny)
			{
				t = intersection.second;
				intersectsAny = true;
				closest = primitive.get();
			}
			else if (intersection.second < t)
			{
				t = intersection.second;
				closest = primitive.get();
			}
		}
		if (!intersectsAny)
		{
			t = -1.0f;
		}
	}
	return std::make_tuple(intersectsAny, ray.point(t), closest);
}


void Scene::read()
{
	int numObjects;
	m_file >> numObjects;
	std::cout << numObjects << " objects in scene" << std::endl;
	for (int i = 0; i < numObjects; i++)
	{
		std::string word;
		m_file >> word;
		std::cout << "Reading " << word << std::endl;
		if (word == "camera")
		{
			setCamera(readCamera());
		}
		else if (word == "plane")
		{
			addPrimitive(readPlane());
		}
		else if (word == "triangle")
		{
			addPrimitive(readTriangle());
		}
		else if (word == "sphere")
		{
			addPrimitive(readSphere());
		}
		else if (word == "light")
		{
			addLight(readLight());
		}
		else
		{
			throw std::logic_error("Input file error: Unexpected" + word);
		}
	}
}


Camera Scene::readCamera()
{
	const auto position = readVec3("pos:");
	const auto fov = readFloat("fov:");
	const auto focalLength = readFloat("f:");
	const auto aspectRatio = readFloat("a:");
	return Camera(position, fov, focalLength, aspectRatio);
}


std::unique_ptr<Plane> Scene::readPlane()
{
	const auto nor = readVec3("nor:");
	const auto pos = readVec3("pos:");
	const auto amb = readVec3("amb:");
	const auto dif = readVec3("dif:");
	const auto spe = readVec3("spe:");
	const auto s = readFloat("shi:");
	return std::move(std::unique_ptr<Plane>(new Plane(nor, pos, amb, dif, spe, s)));
}


std::unique_ptr<Triangle> Scene::readTriangle()
{
	const auto v1 = readVec3("v1:");
	const auto v2 = readVec3("v2:");
	const auto v3 = readVec3("v3:");
	const auto amb = readVec3("amb:");
	const auto dif = readVec3("dif:");
	const auto spe = readVec3("spe:");
	const auto s = readFloat("shi:");
	return std::move(std::unique_ptr<Triangle>(new Triangle (v1, v2, v3, amb, dif, spe, s)));
}


std::unique_ptr<Sphere> Scene::readSphere()
{
	const auto pos = readVec3("pos:");
	const auto r = readFloat("rad:");
	const auto amb = readVec3("amb:");
	const auto dif = readVec3("dif:");
	const auto spe = readVec3("spe:");
	const auto s = readFloat("shi:");
	return std::move(std::unique_ptr<Sphere>(new Sphere(pos, r, amb, dif, spe, s)));
}


Light Scene::readLight()
{
	const auto pos = readVec3("pos:");
	const auto col = readVec3("col:");
	return Light(pos, col);
}


void Scene::readLine(const std::string& prefix)
{
	std::string word;
	m_file >> word;
	if (word != prefix)
	{
		throw std::logic_error("Input file error: Unexpected" + word);
	}
}


glm::vec3 Scene::readVec3(const std::string& prefix)
{
	readLine(prefix);
	float x, y, z;
	m_file >> x;
	m_file >> y;
	m_file >> z;
	return glm::vec3(x, y, z);
}


float Scene::readFloat(const std::string& prefix)
{
	readLine(prefix);
	float x;
	m_file >> x;
	return x;
}


bool Scene::seesLight(const Primitive& primitive, const glm::vec3& point, const Light& light) const
{
	const Ray r(point, light.position() - point);
	bool sees = true;
	for (auto& const p : m_primitives)
	{
		if (p.get() != &primitive)
		{
			const auto blocks = p->intersection(r).first;
			if (blocks)
			{
				sees = false;
				break;
			}
		}
	}
	return sees;
}

/*
glm::vec3 Scene::pixelColour(const int i, const int j) const
{
	auto intersection = closestPrimitiveIntersection(i, j);

}*/


void Scene::render() const
{
	std::cout << "Rendering..." << std::endl;
	auto resolution = m_camera.resolution;
	cimg_library::CImg<float> image(resolution, resolution, 1, 3);
	for (int i = 0; i < resolution; i++)
	{
		for (int j = 0; j < resolution; j++)
		{
			auto intersection = closestPrimitiveIntersection(i, j);
			glm::vec3 colour = ambientColour;
			if (std::get<0>(intersection))
			{
				const auto point = std::get<1>(intersection);
				const auto primitive = std::get<2>(intersection);
				for (const auto& light : m_lights)
				{
					if (seesLight(*primitive, point, light))
					{
						const auto lightColour = light.colour();
						const auto phongLight = primitive->phongIllumination(point, light.position(), m_camera.position());
						colour += lightColour * phongLight;
					}
				}
			}
			image(i, j, 0) = colour.x;
			image(i, j, 1) = colour.y;
			image(i, j, 2) = colour.z;
		}
	}
	image.save("render.bmp");
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed())
	{
		main_disp.wait();
	}
}