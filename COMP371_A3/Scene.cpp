#include "stdafx.h"
#include "Scene.h"


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


std::pair<bool, float> Scene::closestIntersection(const int i, const int j)
{
	const auto ray = m_camera->rayThroughPixel(i, j);
	bool intersectsAny = false;
	float t;
	for (auto primitive : m_primitives)
	{
		const auto intersection = primitive->intersection(ray);
		if (intersection.first)
		{
			if (!intersectsAny)
			{
				t = intersection.second;
				intersectsAny = true;
			}
			else if (intersection.second < t)
			{
				t = intersection.second;
			}
		}
		if (!intersectsAny)
		{
			t = -1.0f;
		}
	}
	return std::make_pair(intersectsAny, t);
}