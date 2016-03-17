// triangle.h
// Author: Michael Deom
// Date: March 7, 2016


#pragma once

#include "primitive.h"
#include "glm.hpp"
#include <vector>
#include <memory>
#include <array>

class Plane;

float area(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);

// The Triangle class represents a single triangle in 3D space.
class Triangle :
	public Primitive
{
	std::array<glm::vec3, 3> m_vertices;
	std::unique_ptr<Plane> m_plane;
	Plane& plane();

public:
	Triangle(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3,
		const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
	std::array<glm::vec3, 3> vertices() const;
	glm::vec3 vertex(const int index) const;
	void setVertex(const int index, const glm::vec3 vertex);
	virtual std::pair<bool, float> intersection(const Ray ray);
	virtual glm::vec3 normal(const glm::vec3& point) const;
	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
	std::pair<std::vector<glm::vec2>, glm::vec2> Triangle::project(const glm::vec3& intersection);
};

