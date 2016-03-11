#include "stdafx.h"
#include "Intersection.h"
#include "Ray.h"
#include "Primitive.h"
#include <tuple>
#include <stdexcept>

// Constructs an intersection between an array and a primitve at a given parameter distance from the ray's origin.
Intersection::Intersection(const Ray& ray, const Primitive& primitive)
{
	bool hits;
	float distance;
	std::tie(hits, distance) = primitive.intersection(ray);
	m_hits = hits;
	m_distance = distance;
}

// Constructs an intersection representing a generic miss
Intersection::Intersection()
	: m_hits(false)
	, m_distance(-1.0f) {}


Intersection::~Intersection() {}


bool Intersection::hits() const { return m_hits; }


bool Intersection::distance() const
{
	if (!m_hits)
	{
		throw std::logic_error("No intersection.");
	}
	return m_distance;
}
