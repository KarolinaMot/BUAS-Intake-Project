#pragma once
#include <SDL2/SDL.h>
#include "../GameObject/GameObject.h"
#include <string>


	class MapLayer : public GameObject
	{
	public:
		MapLayer() { };
		MapLayer(std::string layerName, float posX, float posY, float sizeX, float sizeY, SDL_Rect source, std::string layerPath, SDL_Renderer* renderer) {
			name = layerName;
			dest.x = posX;
			dest.y = posY;
			dest.w = sizeX;
			dest.h = sizeY;
			SetTexture(layerPath, renderer);
			SetSource(source);
		};

	private:
		std::string name;
	};

