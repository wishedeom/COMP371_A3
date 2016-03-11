#pragma once
#include "Camera.h"
#include "Primitive.h"
#include "Light.h"
#include <vector>


class Scene
{
	const Camera* const m_camera;
	std::vector<const Primitive*> m_primitives;
	std::vector<const Light*> m_lights;

public:
	Scene(const Camera& camera);
	~Scene();
	void addPrimitive(Primitive* p);
	void addLight(Light* l);
	std::pair<bool, float> closestIntersection(const int i, const int j);
};