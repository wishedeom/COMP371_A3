#include "stdafx.h"
#include "Sphere.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

Sphere::Sphere(const glm::vec3 centre, const float radius, glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
	: Primitive(ambientColour, diffuseColour, specularColour, shininess)
	, m_centre(centre)
{
	setRadius(radius);
}


Sphere::~Sphere() {}


glm::vec3 Sphere::centre() const { return m_centre; }


float Sphere::radius() const { return m_radius; }


void Sphere::setCentre(const glm::vec3 centre) { m_centre = centre; }


void Sphere::setRadius(const float radius)
{
	if (radius <= 0.)
	{
		throw std::logic_error("Radius must be positive.");
	}
	m_radius = radius;
}


std::pair<bool, float> Sphere::intersection(const Ray ray)
{
	const auto o = ray.origin();
	const auto l = ray.direction();
	const auto r = m_radius;
	const auto rSq = r * r;
	const auto c = m_centre;
	const auto o_c = o - c;
	const auto o_cNSq = glm::dot(o_c, o_c);
	const auto l_o_c = glm::dot(l, o_c);
	const auto l_o_cSq = l_o_c * l_o_c;
	const auto lSq = glm::dot(l, l);
	const auto discriminant = l_o_cSq - lSq * (o_cNSq - rSq);

	float t;
	if (discriminant < 0.)
	{
		t = -1.; // No intersection
	}
	else if (discriminant == 0.)
	{
		t = -l_o_c / lSq;
	}
	else
	{
		const auto sqrtDis = std::sqrt(discriminant);
		auto t1 = (-l_o_c + sqrtDis) / lSq;
		auto t2 = (-l_o_c - sqrtDis) / lSq;
		if ((t1 < 0. && 0. <= t2) || (t2 < 0. && 0. <= t1))
		{
			t = std::max(t1, t2);
		}
		else if (0. <= t1 && 0. <= t2)
		{
			t = std::min(t1, t2);
		}
		else
		{
			t = -1.;
		}
	}
	bool intersects = t >= 0.;

	return std::make_pair(intersects, t);
}