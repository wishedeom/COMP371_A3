#include "stdafx.h"
#include "Scene.h"


Scene::Scene(const Camera& camera)
	: m_camera(camera)
	, m_primitives(0)
	, m_lights(0)
{
	
}