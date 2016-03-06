// camera.cpp
// Author: Michael Deom
// Date: March 6, 2016


#include "stdafx.h"
#include "camera.h"


Camera::Camera(const glm::vec3 position, const glm::vec3 orientation, const float fov, const float aspectRatio)
	: m_position(position)
	, m_orientation(orientation)
	, m_fov(fov)
	, m_aspectRatio(aspectRatio) {}


Camera::Camera(const glm::vec3 position, const float fov, const float aspectRatio)
	: Camera(position, glm::vec3(0.f, 0.f, -1.f), fov, aspectRatio) {}


glm::vec3 Camera::position() const { return m_position; }


glm::vec3 Camera::orientation() const { return m_orientation; }


float Camera::fov() const { return m_fov; }


float Camera::aspectRatio() const { return m_aspectRatio; }


void Camera::setPosition(const glm::vec3 position)
{
	m_position = position;
}


void Camera::setOrientation(const glm::vec3 orientation)
{
	m_orientation = orientation;
}


void Camera::setFOV(const float fov)
{
	m_fov = fov;
}


void Camera::setAspectRatio(const float aspectRatio)
{
	m_aspectRatio = aspectRatio;
}