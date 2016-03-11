#pragma once
#include <vector>

class Camera;
class Intersection;
class Primitive;
class Light;

class Scene
{
	const Camera* const m_camera;
	std::vector<Primitive*> m_primitives;
	std::vector<Light*> m_lights;

public:
	Scene(const Camera& camera);
	~Scene();
	void addPrimitive(Primitive* p);
	void addLight(Light* l);
	std::pair<Intersection*, Primitive*> Scene::closestIntersection(const int i, const int j) const;
};