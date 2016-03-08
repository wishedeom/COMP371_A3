// COMP371_A3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ray.h"
#include "Sphere.h"
#include "plane.h"
#include <iostream>
#include <exception>

int main() try
{
	Ray r(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));
	Sphere s(glm::vec3(0.f, 0.f, 0.f), 1., glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), 0.f);
	Plane p(glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), 0.f);
	auto i = s.intersection(r);
	if (i.first)
	{
		std::cout << i.second << std::endl;
	}
	else
	{
		std::cout << "No intersection." << std::endl;
	}
    return 0;
}
catch (std::exception& e)
{
	std::cout << e.what() << std::endl;
}

