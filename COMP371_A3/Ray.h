#pragma once

#include "glm.hpp"


// Represents a ray (a half-infinite line) originating from an origin point, and extending without limit in a direction.
class Ray
{
	glm::vec3 m_origin;
	glm::vec3 m_direction;

public:
	Ray(const glm::vec3 origin,	const glm::vec3 direction);
	glm::vec3 origin() const;
	glm::vec3 direction() const;
	void setOrigin(const glm::vec3 origin);
	void setDirection(const glm::vec3 direction);
	glm::vec3 point(const float t) const;
};

