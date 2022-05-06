#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Collider
{
	public:
		SDL_Rect colDest;
		SDL_Rect colSrc;

		Collider(float destX, float destY, float sizeX, float sizeY, bool visibility, SDL_Color colliderColor, SDL_Renderer* renderer, double degree) {
			
			visible = visibility; 
			rotation = degree;

			colDest.x = destX;
			colDest.y = destY;
			colDest.w = sizeX;
			colDest.h = sizeY;

			colSrc.x = 0;
			colSrc.y = 0;
			colSrc.w = 250;
			colSrc.h = 250;

			tex = SDL_CreateTextureFromSurface(renderer, surf);
		}
		void SetVisibility(bool visibility) { visible = visibility; }

		void DrawCollider(SDL_Color color, SDL_Renderer*  renderer) {
			SDL_RenderCopyEx(renderer, tex, &colSrc, &colDest, rotation, NULL, SDL_FLIP_NONE);
		}

	private:
		std::string ID;
		bool visible = false;
		double rotation;
		SDL_Surface* surf = IMG_Load("Assets/SPRITESETS/collider.png");
		SDL_Texture* tex;
};

