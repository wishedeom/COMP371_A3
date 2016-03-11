#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"
#include "Intersection.h"


Scene::Scene(const Camera& camera)
	: m_camera(&camera) {}


Scene::~Scene() {}


void Scene::addPrimitive(Primitive* p)
{
	m_primitives.push_back(p);
}


void Scene::addLight(Light* l)
{
	m_lights.push_back(l);
}


std::pair<Intersection*, Primitive*> Scene::closestIntersection(const int i, const int j) const
{
	const auto ray = m_camera->rayThroughPixel(i, j);
	Intersection* closestIntersection = nullptr;
	Primitive* closestPrimitive = nullptr;
	for (auto primitive : m_primitives)
	{
		Intersection intersection(ray, *primitive);
		if (intersection.hits() && (closestIntersection == nullptr || intersection.distance() < closestIntersection->distance()))
		{
			closestIntersection = &intersection;
			closestPrimitive = primitive;
		}
	}
	if (closestIntersection = nullptr)
	{
		closestIntersection = &Intersection();	// A miss
	}
	return std::make_pair(closestIntersection, closestPrimitive);
}