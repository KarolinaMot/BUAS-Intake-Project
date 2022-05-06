#pragma once
#include "../GameObject/GameObject.h"
#include "../SceneObjects/DispensorObject.h"
#include <SDL2/SDL.h>
#include <vector>

class CustomerAI : public GameObject
{
	public: 
		int timer = 40 * 64;
		int eatingTimer = 30 *64;

		int idle, eat;
		int waitForOrderState = 3;
		int eatState = 4;
		int payState = 5;
		int quit = 6;

		int chairIndex = -1;

		int currentState = 3;

		bool visibleOrder = false;

		float givenMoney = 0;

		CustomerAI(float startPositionX, float startPositionY, float sizeX, float sizeY, int chairNum, SDL_Renderer* renderer) {

			SetTexture("Assets/SPRITESETS/MonsterTurning.png", renderer);
			dest.x = startPositionX;
			dest.y = startPositionY;
			dest.w = sizeX;
			dest.h = sizeY;

			idle = CreateAnimation(2, 180, 180, 1, -1);
			eat = CreateAnimation(1, 180, 180, 19, 6);

			chairIndex = chairNum;

			SetCurrentAnimation(idle);

		}
	
		void StateManager() {
			switch (currentState) {
				case 3:
					GenerateOrder();
					break;
				case 4:
					EatOrder();
					break;
				case 5:
					PayOrder();
					break;
				case 6:
					Leave();
					break;
			}
		}

		void GenerateOrder() {
			visibleOrder = true;
			timer--;
			 
			if (timer <= 0) {
				currentState = 6;
				timer = 60 * 64;
			}
			else {
				givenMoney += 10 / (64 * 60);
			}
		}


		void EatOrder() {
			visibleOrder = false;
			if(GetCurrentAnimation()!=eat)
				SetCurrentAnimation(eat);
			eatingTimer--;

			if (eatingTimer <= 0){
				currentState++;
				eatingTimer = 30 * 64;
			}
		}

		void PayOrder() {
			if (GetCurrentAnimation() != idle)
				SetCurrentAnimation(idle);

			if (timer <= 0) {
				currentState = 6;
				timer = 60 * 64;
			}
		}

		void Render(SDL_Renderer* renderer, SDL_RendererFlip flip) {
			UpdateCurrentAnimation();
			Draw(renderer, flip);
		}

		void Leave() {

		}

};

