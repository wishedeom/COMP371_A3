#include "stdafx.h"
#include "plane.h"


Plane::Plane(const glm::vec4& coefficients, const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
	: Primitive(ambientColour, diffuseColour, specularColour, shininess)
	, m_coefficients(coefficients) {}


Plane::Plane(const glm::vec3 normal, const glm::vec3 point, const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
	: Plane(glm::vec4(normal, -glm::dot(normal, point)), ambientColour, diffuseColour, specularColour, shininess) {}


glm::vec4 Plane::coefficients() const { return m_coefficients; }


void Plane::setCoefficients(const glm::vec4& coefficients) { m_coefficients = coefficients; }

std::pair<bool, double> Plane::intersection(const Ray ray)
{
	// The intersection point between a plane (n, d) and a ray (r_0, r'), if it exists, is
	//
	//			     n . r_0 + d
	//		t =  -  -------------
	//			        n . r'
	//
	// If the plane and ray are parallel, n . r' = 0, and there is no intersection.

	const auto n = glm::vec3(m_coefficients);
	const auto d = m_coefficients[3];
	const auto nDotRPrime = glm::dot(n, ray.direction());
	
	double t;
	if (nDotRPrime == 0.f)
	{
		t = -1.;
	}
	else
	{
		t = -(glm::dot(n, ray.origin()) + d) / nDotRPrime;
	}
	bool intersects = t >= 0.;

	return std::make_pair(intersects, t);
}