// triangle.h
// Author: Michael Deom
// Date: March 7, 2016


#pragma once

#include "primitive.h"
#include "glm.hpp"
#include <vector>

// The Triangle class represents a single triangle in 3D space.
class Triangle :
	public Primitive
{
	std::vector<glm::vec3> m_vertices;

public:
	Triangle(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3,
		const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
};

