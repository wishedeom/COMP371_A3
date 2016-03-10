// primitve.cpp
// Author: Michael Deom
// Date: March 6, 2016

#include "stdafx.h"
#include "primitive.h"
#include <stdexcept>


Primitive::Primitive(const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
{
	setAmbientColour(ambientColour);
	setDiffuseColour(diffuseColour);
	setSpecularColour(specularColour);
	setShininess(shininess);
}


Primitive::Primitive()
	: m_ambientColour(glm::vec3(0.f, 0.f, 0.f))
	, m_diffuseColour(glm::vec3(0.f, 0.f, 0.f))
	, m_specularColour(glm::vec3(0.f, 0.f, 0.f))
	, m_shininess(0.f) {}


Primitive::~Primitive() {}


glm::vec3 Primitive::ambientColour() const { return m_ambientColour; }


glm::vec3 Primitive::diffuseColour() const { return m_diffuseColour; }


glm::vec3 Primitive::specularColour() const { return m_specularColour; }


float Primitive::shininess() const { return m_shininess; }


void Primitive::setAmbientColour(const glm::vec3 ambientColour)
{
	if (!isGoodColour(ambientColour))
	{
		throw std::logic_error("Ambient colour components must be between 0 and 1, inclusive.");
	}
	m_ambientColour = ambientColour;
}


void Primitive::setDiffuseColour(const glm::vec3 diffuseColour)
{
	if (!isGoodColour(diffuseColour))
	{
		throw std::logic_error("Diffuse colour components must be between 0 and 1, inclusive.");
	}
	m_diffuseColour = diffuseColour;
}


void Primitive::setSpecularColour(const glm::vec3 specularColour)
{
	if (!isGoodColour(specularColour))
	{
		throw std::logic_error("Specular colour components must be between 0 and 1, inclusive.");
	}
	m_specularColour = specularColour;
}


void Primitive::setShininess(const float shininess)
{
	if (!isGoodColourComponent(shininess))
	{
		throw std::logic_error("Shininess must be between 0 and 1, inclusive.");
	}
	m_shininess = shininess;
}


bool isGoodColourComponent(const float component)
{
	return 0.f <= component && component <= 1.f;
}


bool isGoodColour(const glm::vec3 colour)
{
	return isGoodColourComponent(colour.x) && isGoodColourComponent(colour.y) && isGoodColourComponent(colour.z);
}