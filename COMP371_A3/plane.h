// plane.h
// Author: Michael Deom
// Date: March 6, 2016


#pragma once

#include "primitive.h"
#include "glm.hpp"
#include "Triangle.h"


class Plane
	: public Primitive
{
	glm::vec4 m_coefficients;

public:
	Plane(const glm::vec4& coefficients, const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
	Plane(const glm::vec3 normal, const glm::vec3 point, const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
	Plane(const glm::vec3 normal, const glm::vec3 point);
	~Plane();
	glm::vec4 coefficients() const;
	void setCoefficients(const glm::vec4& coefficients);
	virtual std::pair<bool, float> intersection(const Ray ray);
};