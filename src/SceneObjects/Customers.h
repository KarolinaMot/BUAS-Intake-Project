#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "CustomerAI.h"
#include "CustomerAI.h"
#include "DispensorObject.h"
#include "Slot.h"

class Customers
{
public:
	int spawnTime = 19 * 64;
	int ticking = 30*64;
	std::vector<CustomerAI> allCustomers;
	std::vector<GameObject> allLabels;
	std::vector<DispensorObject> allObjects;

	float chairX1[6] = { 635, 555, 445, 390, 600, 520 };
	float chairY1[6] = { 180, 210, 235, 260, 310, 330 };
	bool taken[6] = { false, false, false, false, false, false };

	DispensorObject tempOrder;
	GameObject tempLabels;

	DispensorObject moneyTex[3];
	std::string textures[9] = { "BlueCream.png", "brownCoffee.png", "BrownCream.png", "caramelCoffee.png", "pinkCoffee.png", "PinkCream.png", "snow1.png", "snow2.png", "snow3.png" };


	void Initialize(SDL_Renderer* renderer) {

		srand(time(0));
		tempOrder.SetTexture("Assets/MAPS/UI/Coin1.png", renderer);
		tempOrder.name = "Coin1";
		moneyTex[0] = tempOrder;

		tempOrder.SetTexture("Assets/MAPS/UI/Coin2.png", renderer);
		tempOrder.name = "Coin2";
		moneyTex[1] = tempOrder;

		tempOrder.SetTexture("Assets/MAPS/UI/Coin3.png", renderer);
		tempOrder.name = "Coin3";
		moneyTex[2] = tempOrder;

	}

	void Update(SDL_Renderer* renderer, float cameraPosX, float cameraPosY) {

		if (spawnTime > ticking) {
			ticking++;
			std::cout << ticking << std::endl;
		}
		else {
			int random2 = rand() % 5;
			float posX, posY;
			if (taken[random2] == false) {
				if (cameraPosX < 0)
					posX = chairX1[random2] + cameraPosX;
				else
					posX =  chairX1[random2] + cameraPosX;

				if (cameraPosY < 0)
					posY = chairY1[random2] + cameraPosY;
				else
					posY = chairY1[random2] + cameraPosY;

				GenerateEnemy(renderer, posX, posY);
				ticking = 0;
				taken[random2] = true;				
			}
		}	

		for (int i = 0; i < allCustomers.size(); i++)
		{
			allCustomers[i].StateManager();
			if (allCustomers[i].currentState == 5) {
				if (allCustomers[i].givenMoney >= 6)
					allObjects[i].tex = moneyTex[2].tex;
				else if(allCustomers[i].givenMoney >= 3)
					allObjects[i].tex = moneyTex[1].tex;
				else
					allObjects[i].tex = moneyTex[1].tex;
			}

			if (allCustomers[i].currentState == 6) {
				allCustomers.erase(allCustomers.begin() + i);
				allLabels.erase(allLabels.begin() + i);
				allObjects.erase(allObjects.begin() + i);
				if(allCustomers[i].chairIndex != -1)
					taken[allCustomers[i].chairIndex] = false;
			}
		}
	}

	void Render(SDL_Renderer* renderer) {
		for (int i = 0; i < allCustomers.size(); i++) {
			allCustomers[i].Render(renderer, SDL_FLIP_HORIZONTAL);
			if (allCustomers[i].currentState == 3 || allCustomers[i].currentState == 5) {
				allLabels[i].Draw(renderer);
				allObjects[i].Draw(renderer);
			}
		}
	}

	void Move(char axis, float speed) {
		if (axis == 'x') {
			for (int i = 0; i < allCustomers.size(); i++) {
				allCustomers[i].dest.x += speed;
				allLabels[i].dest.x += speed;
				allObjects[i].dest.x += speed;
			}
				
		}
		else {
			for (int j = 0; j < allCustomers.size(); j++) {
				allCustomers[j].dest.y += speed;
				allLabels[j].dest.y += speed;
				allObjects[j].dest.y += speed;
			}
		}
	}

	std::string  CheckForOrderHandout(float mouseX, float mouseY, float playerX, float playerY, Slot slots[], int maxNum) {
		for (int i = 0; i < allLabels.size(); i++) {

			if (sqrt(pow(allLabels[i].dest.x - mouseX, 2) + pow(allLabels[i].dest.y - mouseY, 2)) <= 80 && sqrt(pow(playerX - mouseX, 2) + pow(playerY - mouseY, 2)) <= 200) { //check if clicking on order

				for (int j = 0; j < maxNum; j++)
				{

					if (slots[j].objectName == allObjects[i].name) {

						allCustomers[i].currentState++;
						return allObjects[i].name;
					}
				}
				return "null";
			}
			return "null";
		}
	}

	int CheckForMoneyHandout(float mouseX, float mouseY, float playerX, float playerY) {
		for (int i = 0; i < allLabels.size(); i++) {
			if (sqrt(pow(allLabels[i].dest.x - mouseX, 2) + pow(allLabels[i].dest.y - mouseY, 2)) <= 80 && sqrt(pow(playerX - mouseX, 2) + pow(playerY - mouseY, 2)) <= 200) { //check if clicking on order
				if (allCustomers[i].currentState == 5) {
					allCustomers[i].currentState++;
					return allCustomers[i].givenMoney;
				}
				return 0;
			}
			return 0;
		}
	}

	void GenerateEnemy(SDL_Renderer* renderer, float X, float Y) {
		int random = rand() % 9;
		CustomerAI temp(X, Y, 80, 80, random, renderer);
		allCustomers.push_back(temp);

		tempLabels.SetTexture("Assets/MAPS/UI/Label.png", renderer);
		tempLabels.dest.x = X + 15;
		tempLabels.dest.y = Y - 45;
		tempLabels.dest.w = 50;
		tempLabels.dest.h = 50;

		tempLabels.src.x = 0;
		tempLabels.src.y = 0;
		tempLabels.src.w = 164;
		tempLabels.src.h = 136;
		allLabels.push_back(tempLabels);

		tempOrder.SetTexture("Assets/MAPS/UI/" + textures[random], renderer);
		tempOrder.dest.x = X + 15;
		tempOrder.dest.y = Y - 45;
		tempOrder.dest.w = 50;
		tempOrder.dest.h = 50;

		tempOrder.src.x = 0;
		tempOrder.src.y = 0;
		tempOrder.src.w = 180;
		tempOrder.src.h = 180;
		tempOrder.name = textures[random];
		allObjects.push_back(tempOrder);
	}
};

