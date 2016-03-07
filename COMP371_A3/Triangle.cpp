#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3,
	const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
	: Primitive(ambientColour, diffuseColour, specularColour, shininess)
	, m_vertices(0)
{
	m_vertices.push_back(vertex1);
	m_vertices.push_back(vertex2);
	m_vertices.push_back(vertex3);
}