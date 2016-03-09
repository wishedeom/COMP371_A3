#pragma once
#include "glm.hpp"
#include "primitive.h"

class Light
{
	glm::vec3 m_position;
	glm::vec3 m_colour;

public:
	Light(const glm::vec3& position, const glm::vec3& colour);
	glm::vec3 position() const;
	glm::vec3 colour() const;
	void setPosition(const glm::vec3& position);
	void setColour(const glm::vec3& colour);
};

