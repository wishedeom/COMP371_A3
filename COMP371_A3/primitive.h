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
float clamp(const float x, const float min, const float max);

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
	virtual ~Primitive();
	glm::vec3 ambientColour() const;
	glm::vec3 diffuseColour() const;
	glm::vec3 specularColour() const;
	float shininess() const;
	void setAmbientColour(const glm::vec3 ambientColour);
	void setDiffuseColour(const glm::vec3 diffuseColour);
	void setSpecularColour(const glm::vec3 specularColour);
	void setShininess(const float shininess);
	virtual std::pair<bool, float> intersection(const Ray ray) = 0;
	virtual glm::vec3 normal(const glm::vec3& point) const = 0;
	glm::vec3 reflect(const glm::vec3 point, const glm::vec3 incident) const;
	glm::vec3 phongIllumination(const glm::vec3 point, const glm::vec3 lightPosition, const glm::vec3 viewerPosition) const;
};