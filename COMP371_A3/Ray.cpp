#include "stdafx.h"
#include "Ray.h"
#include <stdexcept>


Ray::Ray(const glm::vec3 origin, glm::vec3 direction)
	: m_origin(origin)
{
	setDirection(direction);
}


glm::vec3 Ray::origin() const { return m_origin; }


glm::vec3 Ray::direction() const { return m_direction; }


void Ray::setOrigin(const glm::vec3 origin) { m_origin = origin; }


void Ray::setDirection(const glm::vec3 direction)
{
	if (direction == glm::vec3(0.f, 0.f, 0.f))
	{
		throw std::logic_error("Ray direction must be non-negative.");
	}
	m_direction = direction;
}