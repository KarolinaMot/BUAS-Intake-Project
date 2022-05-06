#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include "../GameObject/GameObject.h"
#include "../SceneObjects/Player.h"
#include "../SceneObjects/Map.h"
#include "../SceneObjects/Dispensor.h"
#include "../SceneObjects/DispensorObject.h"
#include "../SceneObjects/Slot.h"
#include "../SceneObjects/CustomerAI.h"
#include "../SceneObjects/Customers.h"


class Engine {

    public:
        Engine(){};
        bool Initialize();
        void Shutdown();
        void Loop();

    private:
        bool isRunning = false;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        int frameCount = 0;
        int timerFPS = 0;
        int lastFrame =0;
        int screenWidth = 1024;
        int screenHeight = 768;

        void Events();
        void Update();
        void Render();

        Player player;
        Map map;
        Dispensor iceCream;
        Dispensor coffeeMachine;
        Dispensor snowConeMachine;
        GameObject UI;
        Customers customers;
        DispensorObject tempObj;

        TTF_Font* font;

        inline void UpdateObjects() {
            iceCream.Update();
            coffeeMachine.Update();
            snowConeMachine.Update();
            customers.Update(renderer, map.layers[0].dest.x, map.layers[0].dest.y);
        }

        inline void InitializeObjects() {

            player.Initialize(renderer);
            customers.Initialize(renderer);
            map.Initialize(renderer, window);
            iceCream.Initialize(renderer, 1015, 185, 150, 50, "Assets/MAPS/UI/BlueCream.png", "Assets/MAPS/UI/PinkCream.png", "Assets/MAPS/UI/BrownCream.png", "BlueCream.png", "PinkCream.png", "BrownCream.png");
            coffeeMachine.Initialize(renderer, 1175, 280, 150, 50, "Assets/MAPS/UI/brownCoffee.png", "Assets/MAPS/UI/caramelCoffee.png", "Assets/MAPS/UI/pinkCoffee.png", "brownCoffee.png", "caramelCoffee.png", "pinkCoffee.png");
            snowConeMachine.Initialize(renderer, 1300, 340, 150, 50, "Assets/MAPS/UI/snow1.png", "Assets/MAPS/UI/snow2.png", "Assets/MAPS/UI/snow3.png", "snow1.png", "snow2.png", "snow3.png");

        }

        inline void RenderObjects() {
            map.Render(renderer, player.slotNum);
            player.Render(renderer);
            customers.Render(renderer);
            iceCream.Render(renderer);
            coffeeMachine.Render(renderer);
            snowConeMachine.Render(renderer);
        }

        inline void CheckForOrderPickup(){

            int x, y;
            float money = 0;
            SDL_GetMouseState(&x, &y);
            std::string pickedObjectName = "null";

            tempObj = coffeeMachine.CheckClick(x, y, player.dest.x, player.dest.y, player.openSlot);
            if (tempObj.name == "null") {
                tempObj = iceCream.CheckClick(x, y, player.dest.x, player.dest.y, player.openSlot);

                if (tempObj.name == "null") {
                    tempObj = snowConeMachine.CheckClick(x, y, player.dest.x, player.dest.y, player.openSlot);

                    if (tempObj.name == "null") {
                        pickedObjectName = customers.CheckForOrderHandout(x, y, player.dest.x, player.dest.y, map.slots, player.openSlot);
                        if (pickedObjectName == "null") {
                            money = customers.CheckForMoneyHandout(x, y, player.dest.x, player.dest.y);
                        }
                    }
                }
            }

            if (tempObj.name != "null") 
                map.FillASlot(player.slotNum, player.openSlot, tempObj);

            if (pickedObjectName != "null") 
                map.UnFillASlot(pickedObjectName, player.slotNum, player.openSlot);

            if (money != 0)
                player.money += money;
        }
};