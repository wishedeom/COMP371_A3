#include "stdafx.h"
#include "plane.h"


Plane::Plane(const glm::vec4& coefficients, const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
	: Primitive(ambientColour, diffuseColour, specularColour, shininess)
	, m_coefficients(coefficients) {}


Plane::Plane(const glm::vec3 normal, const glm::vec3 point, const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
	: Plane(glm::vec4(normal, -glm::dot(normal, point)), ambientColour, diffuseColour, specularColour, shininess) {}


glm::vec4 Plane::coefficients() const { return m_coefficients; }


void Plane::setCoefficients(const glm::vec4& coefficients) { m_coefficients = coefficients; }