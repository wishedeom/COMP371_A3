// primitive.h
// Author: Michael Deom
// Date: March 6, 2016
//
// The Primitive class represents geometric primitives that appear in the scene.


#pragma once

#include "glm.hpp"
#include "Ray.h"
#include <utility>

bool isGoodColourComponent(const float component);
bool isGoodColour(const glm::vec3 colour);

class Primitive
{
protected:
	glm::vec3 m_ambientColour;	// The ambient colour of the primitive.
	glm::vec3 m_diffuseColour;
	glm::vec3 m_specularColour;
	float m_shininess;

public:
	Primitive(const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess);
	Primitive();
	glm::vec3 ambientColour() const;
	glm::vec3 diffuseColour() const;
	glm::vec3 specularColour() const;
	float shininess() const;
	void setAmbientColour(const glm::vec3 ambientColour);
	void setDiffuseColour(const glm::vec3 diffuseColour);
	void setSpecularColour(const glm::vec3 specularColour);
	void setShininess(const float shininess);
	virtual std::pair<bool, double> intersection(const Ray ray) = 0;
};