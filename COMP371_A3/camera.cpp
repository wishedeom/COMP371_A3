// camera.cpp
// Author: Michael Deom
// Date: March 6, 2016


#include "stdafx.h"
#include "Camera.h"
#include <stdexcept>


const int Camera::horPixels = 800;
const int Camera::verPixels = 800;


Camera::Camera(const glm::vec3 position, const float fov, const float aspectRatio)
	: m_position(position)
{
	setFOV(fov);
	setAspectRatio(aspectRatio);
}


void Camera::updateImagePlaneDimensions()
{
	m_height = m_focalLength * std::atan(m_fov / 2);
	m_width = m_height * m_aspectRatio;
}


glm::vec3 Camera::position() const { return m_position; }


float Camera::fov() const { return m_fov; }


float Camera::aspectRatio() const { return m_aspectRatio; }


float Camera::focalLength() const {	return m_focalLength; }


void Camera::setPosition(const glm::vec3 position)
{
	m_position = position;
}


void Camera::setFOV(const float fov)
{
	if (!(0.f < fov && fov < 180.f))
	{
		throw std::logic_error("Field-of-view angle must be between 0 and 180 degrees, exclusive.");
	}
	m_fov = fov;
	updateImagePlaneDimensions();
}


void Camera::setAspectRatio(const float aspectRatio)
{
	if (!(0.f < aspectRatio))
	{
		throw std::logic_error("Aspect ratio must be strictly positive.");
	}
	m_aspectRatio = aspectRatio;
	updateImagePlaneDimensions();
}


void Camera::setFocalLength(const float focalLength)
{
	if (!(0.f < focalLength))
	{
		throw std::logic_error("Focal length must be strictly positive.");
	}
	m_focalLength = focalLength;
	updateImagePlaneDimensions();
}


glm::vec3 Camera::getPixelCoordinates(const int i, const int j) const
{
	const auto imagePlaneCoords = glm::vec3(getPixelImageCoordinates(i, j), -m_focalLength);
	return m_position + imagePlaneCoords;
}


glm::vec2 Camera::getPixelImageCoordinates(const int i, const int j) const
{
	if (!(isGoodVerPixel(i) && isGoodHorPixel(j)))
	{
		throw std::logic_error("Pixel index must be between 0 and number of pixels.");
	}
	const auto x = m_width * ((float)i / horPixels - 0.5f) + 0.5f;
	const auto y = m_height * ((float)i / verPixels - 0.5f) + 0.5f;
	return glm::vec2(x, y);
}


bool Camera::isGoodVerPixel(const int i) const
{
	return (0 <= i && i < verPixels);
}


bool Camera::isGoodHorPixel(const int j) const
{
	return (0 <= j && j < horPixels);
}


Ray Camera::rayThroughPixel(const int i, const int j) const
{
	auto pixel = getPixelCoordinates(i, j);
	auto direction = pixel - m_position;
	return Ray(pixel, direction);
}