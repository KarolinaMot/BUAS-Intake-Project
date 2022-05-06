#pragma once
#include "../GameObject/GameObject.h"
#include <SDL2/SDL.h>


	class Player : public GameObject
	{
	public:
		//ANIMATIONS
		int idle = 0;
		int walkFront = 0;
		int walkRight = 0;
		int walkLeft = 0;
		int walkBack = 0;

		//STATS
		float walkingSpeed = 4;
		int slotNum = 4;
		int openSlot = 4;
		float money = 0;

		void Initialize(SDL_Renderer* renderer) {

			SetTexture("Assets/SPRITESETS/McWalk.png", renderer);

			idle = CreateAnimation(2, 180, 180, 1, -1);
			walkFront = CreateAnimation(2, 180, 180, 6, 7);
			walkRight = CreateAnimation(4, 180, 180, 6, 7);
			walkLeft = CreateAnimation(3, 180, 180, 6, 7);
			walkBack = CreateAnimation(1, 180, 180, 6, 7);

			dest.x = 650;
			dest.y = 180;
			dest.h = 120;
			dest.w = 120;

			SetCurrentAnimation(idle);

			colliderColor.r = 52;
			colliderColor.g = 235;
			colliderColor.b = 107;
			colliderColor.a = 255;

		}

		void Render(SDL_Renderer* renderer) {
			UpdateCurrentAnimation();
			Draw(renderer);
		}

		#pragma region MovementAnimations
		void WalkLeft() {
			if (GetCurrentAnimation() != walkLeft)
				SetCurrentAnimation(walkLeft);
		}
		void WalkRight() {
			if (GetCurrentAnimation() != walkRight)
				SetCurrentAnimation(walkRight);
		}
		void WalkUp() {
			if (GetCurrentAnimation() != walkBack)
				SetCurrentAnimation(walkBack);
		}
		void WalkDown() {
			if (GetCurrentAnimation() != walkFront)
				SetCurrentAnimation(walkFront);
		}
		void ReturnToIdle() {
			if (GetCurrentAnimation() != idle)
				SetCurrentAnimation(idle);
		}
#pragma endregion
	};

