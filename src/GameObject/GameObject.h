#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "../Components/Collider.h"


class GameObject 
{
	public:
		std::vector<Collider> colliders;
		std::vector<Collider> rotatedColliders;
		SDL_Texture* tex;
		SDL_Rect src;
		SDL_Rect dest;

		SDL_Rect getSource() const { return src; }
		SDL_Texture* getTexture() const { return tex; }

		//POSITION FUNCTIONS
		void SetSource(int x, int y, int w, int h);
		void SetSource(SDL_Rect rec);
		void SetTexture(std::string filename, SDL_Renderer* ren);
		void Draw(SDL_Renderer* ren);
		void Draw(SDL_Renderer* ren, SDL_RendererFlip flip);

		//ANIMATIONS
		int CreateAnimation(int r, int w, int h, int amount, int speed);
		void SetCurrentAnimation(int c) { begin = 0; curAnim = c; }
		int GetCurrentAnimation() { return curAnim; }
		void UpdateCurrentAnimation();

		//COLLIDERS
		void AddCollider(std::string id, float sizeX, float sizeY, float positionX, float positionY, SDL_Color color, bool show, SDL_Renderer* renderer, double degree);
		bool CheckCollision(SDL_Rect &a, SDL_Rect &b);
		SDL_Color colliderColor;


	private:
		struct Cycle {
			int w;
			int h;
			int amount;
			int speed;
			int tick;
			int row;
		};
		std::vector<Cycle> animations;

		//RECTANGLES
		int curAnim;
		int begin;
};

