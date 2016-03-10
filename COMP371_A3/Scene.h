#pragma once
#include "camera.h"
#include "primitive.h"
#include "Light.h"
#include <vector>


class Scene
{
	Camera* m_camera;
	std::vector<Primitive*> m_primitives;
	std::vector<Light*> m_lights;

public:
	Scene(Camera* camera);
	~Scene();
	void addPrimitive(Primitive* p);
	void addLight(Light* l);
	std::pair<bool, float> closestIntersection(const int i, const int j);
};