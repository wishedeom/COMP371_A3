#pragma once
#include "primitive.h"
#include "glm.hpp"

class Sphere :
	public Primitive
{
	glm::vec3 m_centre;
	double m_radius;

public:
	Sphere(const glm::vec3 m_centre, const double radius, glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
	glm::vec3 centre() const;
	double radius() const;
	void setCentre(const glm::vec3 centre);
	void setRadius(const double radius);
	virtual std::pair<bool, double> intersection(const Ray ray);
};

