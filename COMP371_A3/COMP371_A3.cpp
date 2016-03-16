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
	/*
	cimg_library::CImg<float> image(400, 400, 1, 3, 0);
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 100; j < 300; j++)
		{
			//std::cout << red << "\t";
			image(i, j, 0) = 255 * i / image.width();
			image(i, j, 1) = 127;
			image(i, j, 2) = 0;
		}
	}
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed())
	{
		main_disp.wait();
	}
	*/

	
	Scene scene("scene1.txt");
	scene.render();
	

    return 0;
}
catch (std::exception& e)
{
	std::cout << e.what() << std::endl;
}

