// COMP371_A3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ray.h"
#include "Sphere.h"
#include "plane.h"
#include <iostream>
#include <exception>
#include "Scene.h"
#include "CImg.h"

int main() try
{
	Scene scene("scene.txt");
	scene.render();
    return 0;
}
catch (std::exception& e)
{
	std::cout << e.what() << std::endl;
}

