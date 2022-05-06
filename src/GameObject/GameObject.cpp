#include "GameObject.h"
#include <SDL2/SDL_image.h>
#include <iostream>

void GameObject::SetSource(int x, int y, int w, int h)
{
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}

void GameObject::SetSource(SDL_Rect rec)
{
	src = rec;
}

void GameObject::SetTexture(std::string filename, SDL_Renderer* ren)
{
	SDL_Surface* surf = IMG_Load(filename.c_str());
	tex = SDL_CreateTextureFromSurface(ren, surf);
}

void GameObject::Draw(SDL_Renderer* ren)
{
	if (SDL_RenderCopyEx(ren, tex, &src, &dest, 0, NULL, SDL_FLIP_NONE) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

void GameObject::Draw(SDL_Renderer* ren, SDL_RendererFlip flip)
{
	if (SDL_RenderCopyEx(ren, tex, &src, &dest, 0, NULL, flip) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

int GameObject::CreateAnimation(int r, int w, int h, int amount, int speed)
{
	Cycle tmp;
	tmp.row = r - 1;
	tmp.w = w;
	tmp.h = h;
	tmp.amount = amount;
	tmp.speed = speed;
	tmp.tick = 0;
	animations.push_back(tmp);
	return animations.size() - 1;
}

void GameObject::UpdateCurrentAnimation()
{
	SetSource(animations[curAnim].w * animations[curAnim].tick, animations[curAnim].row * animations[curAnim].h, animations[curAnim].w, animations[curAnim].h);

	if (begin > animations[curAnim].speed) { animations[curAnim].tick++; begin = 0; }
		begin++;

	if (animations[curAnim].tick >= animations[curAnim].amount) { animations[curAnim].tick = 0; }

}

void GameObject::AddCollider(std::string id, float sizeX, float sizeY, float positionX, float positionY, SDL_Color color, bool show, SDL_Renderer* renderer, double degree)
{
	dest.x = positionX;
	dest.y = positionY;
	dest.w = sizeX;
	dest.h = sizeY;

	Collider temp(dest.x, dest.y, dest.w, dest.h, show, colliderColor, renderer, degree);
	colliders.push_back(temp);
}

bool CheckCollision(SDL_Rect &a, SDL_Rect &b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
