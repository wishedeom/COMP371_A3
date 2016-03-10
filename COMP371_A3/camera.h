// camera.h
// Author: Michael Deom
// Date: March 6, 2016
//
// The Camera class represents the user's point of view in the scene. The camera has a position and orientation in three-dimensional space, and the
// view volume of the camera itself is determined by it's field-of-view (FOV) angle, and the aspect ratio between the width and height of the screen.


#pragma once

#include "glm.hpp"


class Camera
{
	glm::vec3 m_position;		// The camera's position
	glm::vec3 m_orientation;	// The direction the camera is pointing
	float m_fov;				// The angle of the camera's field-of-view, in degrees. Must be between 0 and 180, exclusive.
	float m_aspectRatio;		// The ratio between the width and height of the viewport. Must be greater than 0.
	float m_focalLength;
	float m_width;
	float m_height;

	void updateImagePlaneDimensions();
	glm::vec2 getPixelImageCoordinates(const int i, const int j);

public:
	
	static const int horPixels;
	static const int verPixels;

	// Constructs a camera with a given initial position, orientation, FOV, and aspect ratio.
	// position: The camera's initial position.
	// orientation: The camera's initial orientation.
	// fov: The camera's initial field of view angle, in degrees. Must be between 0 and 180, exclusive.
	// aspectRatio: The camera's initial aspect ratio. Must be greater than 0.
	Camera(const glm::vec3 position, const glm::vec3 orientation, const float fov, const float aspectRatio);
	
	
	// Constructs a camera with a given initial position, FOV, and aspect ratio, and an initial orientation in the negative z-direction.
	// position: The camera's initial position.
	// fov: The camera's initial field of view angle, in degrees. Must be between 0 and 180, exclusive.
	// aspectRatio: The camera's initial aspect ratio. Must be greater than 0.
	Camera(const glm::vec3 position, const float fov, const float aspectRatio);


	// Returns the camera's position.
	glm::vec3 position() const;


	// Returns the camera's orientation.
	glm::vec3 orientation() const;


	// Returns the camera's field-of-view (FOV) angle.
	float fov() const;


	// Returns the camera's aspect ratio.
	float aspectRatio() const;


	float focalLength() const;


	// Moves the camera to a new position.
	// position: The camera's new position.
	void setPosition(const glm::vec3 position);


	// Orients the camera to a new orientation.
	// orientation: The camera's initial orientation.
	void setOrientation(const glm::vec3 orientation);


	// Sets the camera's field of view angle.
	// fov: The camera's new field-of-view angle, in degrees. Must be between 0 and 180, exclusive.
	void setFOV(const float fov);

	// Sets the camera's aspect ratio.
	// fov: The camera's new aspect ratio. Must be greater than 0.
	void setAspectRatio(const float aspectRatio);


	void setFocalLength(const float focalLength);


	glm::vec3 getPixelCoordinates(const int i, const int j);
};