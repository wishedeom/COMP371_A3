#pragma once
#include "Ray.h"
#include "Primitive.h"

class Intersection
{
	bool m_hits;
	float m_distance;

public:
	Intersection(const Ray& ray, const Primitive& primitive);
	Intersection();
	~Intersection();
	bool hits() const;
	bool distance() const;
};

