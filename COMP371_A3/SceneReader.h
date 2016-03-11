#pragma once
#include <string>
#include <fstream>
#include "Camera.h"
#include "plane.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Light.h"

class SceneReader
{
	std::ifstream file;

	Camera readCamera();
	Plane readPlane();
	Triangle readTriangle();
	Sphere readSphere();
	Light readLight();
	void SceneReader::readLine(const std::string& prefix);
	glm::vec3 readVec3(const std::string& prefix);
	float readFloat(const std::string& prefix);

public:
	SceneReader(const std::string& filename);
	~SceneReader();
	void read();
};

