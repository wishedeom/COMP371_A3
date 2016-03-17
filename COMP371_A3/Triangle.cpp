// Triangle.cpp
// Author: Michael Deom
// Date: March 7, 2016

#include "stdafx.h"
#include "Triangle.h"
#include "plane.h"
#include <string>

bool isGoodIndex(const int index)
{
	return 0 <= index && index <= 2;
}


int checkIndex(const int index)
{
	if (!isGoodIndex(index))
	{
		throw std::logic_error("Triangle index must be between 0 and 2, inclusive.");
	}
	return index;
}


glm::vec2 projectXY(const glm::vec3& point)
{
	return glm::vec2(point.x, point.y);
}


glm::vec2 projectYZ(const glm::vec3& point)
{
	return glm::vec2(point.y, point.z);
}


glm::vec2 projectZX(const glm::vec3& point)
{
	return glm::vec2(point.z, point.x);
}

float area(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c)
{
	return 0.5f * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}


Triangle::Triangle(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3,
	const glm::vec3 ambientColour, const glm::vec3 diffuseColour, const glm::vec3 specularColour, const float shininess)
	: Primitive(ambientColour, diffuseColour, specularColour, shininess)
	, m_vertices { vertex1, vertex2, vertex3 }
{
	m_plane = std::move(std::unique_ptr<Plane>(&plane()));
}


std::pair<std::vector<glm::vec2>, glm::vec2> Triangle::project(const glm::vec3& intersection)
{
	const auto n = normal(intersection);
	std::vector<glm::vec2> vertexProjection(0);
	glm::vec2 intersectionProjection;
	if (glm::dot(n, glm::vec3(1.f, 0.f, 0.f)) != 0.f)
	{
		for (auto vertex : m_vertices)
		{
			vertexProjection.push_back(projectYZ(vertex));
		}
		intersectionProjection = projectYZ(intersection);
	}
	else if (glm::dot(n, glm::vec3(0.f, 1.f, 0.f)) != 0.f)
	{
		for (auto vertex : m_vertices)
		{
			vertexProjection.push_back(projectZX(vertex));
		}
		intersectionProjection = projectZX(intersection);
	}
	else
	{
		for (auto vertex : m_vertices)
		{
			vertexProjection.push_back(projectXY(vertex));
		}
		intersectionProjection = projectXY(intersection);
	}
	return std::make_pair(vertexProjection, intersectionProjection);
}


Plane& Triangle::plane()
{
	auto u = m_vertices[1] - m_vertices[0];
	auto v = m_vertices[2] - m_vertices[0];
	auto normal = glm::cross(u, v);
	return *(new Plane(normal, m_vertices[0]));

}


std::array<glm::vec3, 3> Triangle::vertices() const { return m_vertices; }


glm::vec3 Triangle::vertex(const int index) const {	return m_vertices[checkIndex(index)]; }


void Triangle::setVertex(const int index, const glm::vec3 vertex) {	m_vertices[checkIndex(index)] = vertex; }


std::pair<bool, float> Triangle::intersection(const Ray ray)
{
	auto planeIntersection = m_plane->intersection(ray);
	auto t = planeIntersection.second;
	auto intersectionPoint = ray.point(t);
	bool intersectsTriangle = true;
	if (planeIntersection.first)
	{
		auto projections = project(intersectionPoint);
		auto vertices = projections.first;
		auto p = projections.second;
		for (int i = 0; i < 3; i++)
		{
			intersectsTriangle = intersectsTriangle && (area(vertices[i], vertices[(i + 1) % 3], p) >= 0.f);
		}
	}
	return std::make_pair(intersectsTriangle, t);
}


glm::vec3 Triangle::normal(const glm::vec3& point) const
{
	return m_plane->normal(point);
}


std::ostream& operator<<(std::ostream& out, const glm::vec3& v)
{
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}


std::ostream& operator<<(std::ostream& out, const Triangle& t)
{
	out << t.m_vertices[0] << " " << t.m_vertices[1] << " " << t.m_vertices[2];
	return out;
}