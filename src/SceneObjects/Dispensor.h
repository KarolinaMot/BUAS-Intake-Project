#pragma once
#include "../GameObject/GameObject.h"
#include "DispensorObject.h"

#include <cmath>
class Dispensor : public GameObject
{
public:
	float timerS = 1;
	float productionS = 0;
	float timerLimit = 500;

	DispensorObject objects[4];
	
	void Initialize(SDL_Renderer* renderer, float destX, float destY, float destW, float destH, std::string product1Pth, std::string product2Pth, std::string product3Pth, std::string product1Nm, std::string product2Nm, std::string product3Nm) {
		SetTexture("Assets/MAPS/UI/Labels.png", renderer);

		objects[0].SetTexture(product1Pth, renderer);
		objects[1].SetTexture(product2Pth, renderer);
		objects[2].SetTexture(product3Pth, renderer);

		objects[0].name = product1Nm;
		objects[1].name = product2Nm;
		objects[2].name = product3Nm;
		objects[3].name = "null";

		for (int i = 0; i < 3; i++)
		{
			objects[i].src.x = objects[i].src.y = 0;
			objects[i].src.w = objects[i].src.h = 180;
		}

		SetSource(0, 0, 504, 180);
		dest.x = destX;
		dest.y = destY;
		dest.w = destW;
		dest.h = destH;

		objects[0].dest.x = dest.x;
		objects[0].dest.y = dest.y;
		objects[0].dest.w = 50;
		objects[0].dest.h = 50;

		objects[1].dest.x = dest.x + 50;
		objects[1].dest.y = dest.y;
		objects[1].dest.w = 50;
		objects[1].dest.h = 50;

		objects[2].dest.x = dest.x + 100;
		objects[2].dest.y = dest.y;
		objects[2].dest.w = 50;
		objects[2].dest.h = 50;
	}

	void Update() {
		Tick();
	}

	DispensorObject CheckClick(float x, float y, float playerX, float playerY, int availableSlots) {
		for (int i = 0; i < 3; i++)
		{
			if (sqrt(pow(objects[i].dest.x - x, 2) + pow(objects[i].dest.y - y, 2)) <= 50 && sqrt(pow(playerX - x, 2) + pow(playerY - y, 2)) <= 200 && availableSlots > 0) {
				objects[i].objectTaken = true;
				return objects[i];
			}
		}

		return objects[3];
	}

	void Render(SDL_Renderer* renderer) {
		Draw(renderer);
		for (int i = 0; i < 3; i++)
		{
			if (!objects[i].objectTaken)
				SDL_RenderCopyEx(renderer, objects[i].tex, &objects[i].src, &objects[i].dest, 0, NULL, SDL_FLIP_NONE);
		}
	}

	void Move(char axis, float speed) {
		if (axis == 'x') {
			dest.x += speed;
			objects[0].dest.x += speed;
			objects[1].dest.x += speed;
			objects[2].dest.x += speed;
		}
		else {
			dest.y += speed;
			objects[0].dest.y += speed;
			objects[1].dest.y += speed;
			objects[2].dest.y += speed;
		}
	}

	void Tick() {
		for (int i = 0; i < 3; i++)
		{
			if (objects[i].objectTaken) {
				objects[i].tick++;
			}
			if (objects[i].tick >= timerLimit) {
				objects[i].objectTaken = false;
				objects[i].tick = 0;
			}
		}		
	}

	void AddToSlot(int &slotsLeft, int& slots, SDL_Texture* tex) {
		
		

	}

};

