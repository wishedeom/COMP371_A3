// primitve.cpp
// Author: Michael Deom
// Date: March 6, 2016

#include "stdafx.h"
#include "primitive.h"
#include <stdexcept>
#include <algorithm>


float clamp(const float x, const float min, const float max);


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


void Primitive::setShininess(const float shininess) { m_shininess = shininess; }


glm::vec3 Primitive::reflect(const glm::vec3 point, const glm::vec3 incident) const
{
	const auto n = normal(point);
	return 2.0f * glm::dot(incident, n) * n - incident;
}


glm::vec3 Primitive::phongIllumination(const glm::vec3 point, const glm::vec3 lightPosition, const glm::vec3 viewerPosition) const
{
	const auto l = glm::normalize(lightPosition - point);
	const auto n = normal(point);
	const auto r = reflect(point, l);
	return m_diffuseColour * clamp(glm::dot(l, n), 0.0f, 1.0f) + m_specularColour * std::pow(clamp(glm::dot(r, viewerPosition), 0.0f, 1.0f), m_shininess);
}


bool isGoodColourComponent(const float component)
{
	return 0.f <= component && component <= 1.f;
}


bool isGoodColour(const glm::vec3 colour)
{
	return isGoodColourComponent(colour.x) && isGoodColourComponent(colour.y) && isGoodColourComponent(colour.z);
}


float clamp(const float x, const float min, const float max)
{
	if (min > max)
	{
		throw std::logic_error("Min must be no larger than max.");
	}
	return std::max(min, std::min(x, max));
}