#include "stdafx.h"
#include "SceneReader.h"
#include <tuple>


SceneReader::SceneReader(const std::string& filename)
	: file(filename) {}


SceneReader::~SceneReader() {}


void SceneReader::read()
{
	std::string word;
	while (file >> word)
	{
		if (word == "camera")
		{
			// readCamera();
		}
		else if (word == "plane")
		{
			// readPlane();
		}
		else if (word == "triangle")
		{
			// readTraingle();
		}
		else if (word == "sphere")
		{
			// readSphere();
		}
		else if (word == "light")
		{
			// readLight();
		}
		else
		{
			throw std::logic_error("Input file error: Unexpected" + word);
		}
	}
}


Camera SceneReader::readCamera()
{
	auto position = readVec3("pos:");
	auto fov = readFloat("fov:");
	auto focalLength = readFloat("f:");
	auto aspectRatio = readFloat("a:");
	return Camera(position, fov, focalLength, aspectRatio);
}


Plane SceneReader::readPlane()
{
	auto nor = readVec3("nor:");
	auto pos = readVec3("pos:");
	auto amb = readVec3("amb:");
	auto dif = readVec3("dif:");
	auto spe = readVec3("spe:");
	auto s = readFloat("s:");
	return Plane(nor, pos, amb, dif, spe, s);
}


Triangle SceneReader::readTriangle()
{
	auto v1 = readVec3("v1:");
	auto v2 = readVec3("v2:");
	auto v3 = readVec3("v3:");
	auto amb = readVec3("amb:");
	auto dif = readVec3("dif:");
	auto spe = readVec3("spe:");
	auto s = readFloat("s:");
	return Triangle(v1, v2, v3, amb, dif, spe, s);
}


Sphere SceneReader::readSphere()
{
	auto pos = readVec3("pos:");
	auto r = readFloat("r:");
	auto amb = readVec3("amb:");
	auto dif = readVec3("dif:");
	auto spe = readVec3("spe:");
	auto s = readFloat("s:");
	return Sphere(pos, r, amb, dif, spe, s);
}


Light SceneReader::readLight()
{
	auto pos = readVec3("pos:");
	auto col = readVec3("col:");
	return Light(pos, col);
}


void SceneReader::readLine(const std::string& prefix)
{
	std::string word;
	file >> word;
	if (word != prefix)
	{
		throw std::logic_error("Input file error: Unexpected" + word);
	}
}


glm::vec3 SceneReader::readVec3(const std::string& prefix)
{
	readLine(prefix);
	float x, y, z;
	file >> x;
	file >> y;
	file >> z;
	return glm::vec3(x, y, z);
}


float SceneReader::readFloat(const std::string& prefix)
{
	readLine(prefix);
	float x;
	file >> x;
	return x;
}