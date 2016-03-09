// triangle.h
// Author: Michael Deom
// Date: March 7, 2016


#pragma once

#include "primitive.h"
#include "glm.hpp"
#include <vector>

class Plane;

// The Triangle class represents a single triangle in 3D space.
class Triangle :
	public Primitive
{
	std::vector<glm::vec3> m_vertices;
	Plane* m_plane;
	Plane* plane();
	std::pair<std::vector<glm::vec2>, glm::vec2> Triangle::project(const glm::vec3& intersection);

public:
	Triangle(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3,
		const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
	~Triangle();
	std::vector<glm::vec3> vertices() const;
	glm::vec3 vertex(const int index) const;
	void setVertex(const int index, const glm::vec3 vertex);
	virtual std::pair<bool, float> intersection(const Ray ray);
};

