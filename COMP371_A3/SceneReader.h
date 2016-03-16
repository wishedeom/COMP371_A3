#pragma once
#include <string>
#include <fstream>
#include "Camera.h"
#include "plane.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"

class SceneReader
{
	Scene* scene;
	

	

public:
	SceneReader(const std::string& filename);
	~SceneReader();
	
};

