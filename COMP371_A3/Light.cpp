#include "stdafx.h"
#include "Light.h"
#include <stdexcept>


Light::Light(const glm::vec3& position, const glm::vec3& colour)
	: m_position(position)
{
	setColour(colour);
}


glm::vec3 Light::position() const { return m_position; }


glm::vec3 Light::colour() const { return m_colour; }


void Light::setPosition(const glm::vec3& position) { m_position = position; }


void Light::setColour(const glm::vec3& colour)
{
	if (!isGoodColour(colour))
	{
		throw std::logic_error("Colour components must be between 0 and 1, inclusive.");
	}
	m_colour = colour;
}