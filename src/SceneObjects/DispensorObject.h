#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../GameObject/GameObject.h"

class DispensorObject : public GameObject
{
	public:
		std::string name;
		bool objectTaken;
		bool objectGiven;
		float tick;
};

