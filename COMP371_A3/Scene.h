#pragma once
#include "camera.h"
#include "primitive.h"
#include "Light.h"
#include <vector>
#include "Sphere.h"
#include "plane.h"
#include <string>
#include <fstream>
#include <memory>
#include "Cimg.h"


class Scene
{
	Camera m_camera;
	std::vector<std::unique_ptr<Primitive>> m_primitives;
	std::vector<Light> m_lights;
	std::ifstream m_file;

	Camera readCamera();
	std::unique_ptr<Plane> readPlane();
	std::unique_ptr<Triangle> readTriangle();
	std::unique_ptr<Sphere> readSphere();
	Light readLight();

	void readLine(const std::string& prefix);
	glm::vec3 readVec3(const std::string& prefix);
	float readFloat(const std::string& prefix);

	void read();

	void setCamera(const Camera& camera);
	void addPrimitive(std::unique_ptr<Primitive> primitive);
	void addLight(const Light& light);

	std::tuple<bool, glm::vec3, Primitive*> closestPrimitiveIntersection(const int i, const int j) const;
	bool seesLight(const Primitive& primitive, const glm::vec3& point, const Light& light) const;
	glm::vec3 getPixelColour(const int i, const int j) const;
	void setPixelColour(cimg_library::CImg<float>& image, const int i, const int j, const glm::vec3& colour) const;

public:
	const glm::vec3 skyColour;

	Scene(const std::string& filename);
	~Scene();

	void render() const;
};