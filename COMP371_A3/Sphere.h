#pragma once
#include "primitive.h"
#include "glm.hpp"

class Sphere :
	public Primitive
{
	glm::vec3 m_centre;
	float m_radius;

public:
	Sphere(const glm::vec3 m_centre, const float radius, glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
	~Sphere();
	glm::vec3 centre() const;
	float radius() const;
	void setCentre(const glm::vec3 centre);
	void setRadius(const float radius);
	virtual std::pair<bool, float> intersection(const Ray ray);
};

