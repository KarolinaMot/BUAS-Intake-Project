#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "../GameObject/GameObject.h"
#include "MapLayer.h"
#include "Player.h"
#include "../SceneObjects/Slot.h"
#include "DispensorObject.h"

class Map :GameObject
{
    public:
    Map() {};

    Slot slots[8];
    

    std::vector<MapLayer>layers;
    MapLayer UI;

    bool ableWalkUp = true;
    bool ableWalkDown = true;
    bool ableWalkRight = true;
    bool ableWalkLeft = true;

    void FillASlot(int playerSlot, int &openSlot, DispensorObject obj) {
        for (int i = 0; i < playerSlot; i++)
        {
            if (!slots[i].filled) {
                slots[i].tex = obj.getTexture();
                slots[i].filled = true;
                slots[i].objectName = obj.name;
                openSlot--;
                return;
            }
        }

    }

    void UnFillASlot(std::string name, int playerSlot, int& openSlot) {
        for (int i = 0; i < playerSlot; i++) {
            if (slots[i].filled && slots[i].objectName == name) {
                slots[i].filled = false;
                slots[i].objectName = "empty";
                openSlot++;
                return;
            }

        }
    }

    void AddLayer(std::string layerName, float posX, float posY, float sizeX, float sizeY, std::string path, SDL_Renderer* renderer) {
        SDL_Rect tempSrc;
        tempSrc.x = tempSrc.y = 0;
        tempSrc.w = 3312;
        tempSrc.h = 1786;

        MapLayer temp(layerName, posX, posY, sizeX, sizeY, tempSrc, path, renderer);
        layers.push_back(temp);
    }

    void AddUI(std::string layerName, float posX, float posY, float sizeX, float sizeY, std::string path, SDL_Renderer* renderer) {

        SDL_Rect tempSrc;
        tempSrc.x = tempSrc.y = 0;
        tempSrc.w = 1920;
        tempSrc.h = 1080;

        MapLayer temp(layerName, posX, posY, sizeX, sizeY, tempSrc, path, renderer);
        UI = temp;
    }

    void Initialize(SDL_Renderer* renderer, SDL_Window* window) {
        float defaultW = 1800;
        float defaultH = 971;

        colliderColor.r = 54;
        colliderColor.g = 130;
        colliderColor.b = 207;
        colliderColor.a = 255;

        AddLayer("mapBase", 0, 0, defaultW, defaultH, "Assets/MAPS/Layers/Base.png", renderer);
        AddLayer("building", 0, 0, defaultW, defaultH, "Assets/MAPS/Layers/BUILDING.png", renderer);
        AddLayer("building", 0, 0, defaultW, defaultH, "Assets/MAPS/Layers/TablesV1.png", renderer);
        AddLayer("fence", 0, 0, defaultW, defaultH, "Assets/MAPS/Layers/FENCE.png", renderer);
        AddLayer("outsideObj", 0, 0, defaultW, defaultH, "Assets/MAPS/Layers/OutsideObjects.png", renderer);

        UI.SetTexture("Assets/MAPS/Layers/U1v3.png", renderer);
        UI.src.x = 0;
        UI.src.y = 0;
        UI.src.w = 1920;
        UI.src.h = 1080;

        int w;
        int h;
        SDL_GetWindowSize(window, &w, &h);
        UI.dest.x = 0;
        UI.dest.y = 0;
        UI.dest.w = w;
        UI.dest.h = h;
        
        for (int i = 0; i < 8; i++) {
            slots[i].SetTexture("Assets/MAPS/UI/snow1.png", renderer);
            slots[i].src.x = 0;
            slots[i].src.y = 0;
            slots[i].src.w = 180;
            slots[i].src.h = 180;

            slots[i].dest.y = 755;
            slots[i].dest.x = 475 + (i*70);
            slots[i].dest.w = 90;
            slots[i].dest.h = 90;
        }
    }

    void Render(SDL_Renderer* renderer, int &playerSlots) {
        for (MapLayer layer : layers) {
            layer.Draw(renderer);
        }
        UI.Draw(renderer);

        for (int i = 0; i < playerSlots; i++){
            if(slots[i].filled)
              slots[i].Draw(renderer);
        }
    }

    void Move(char axis, float speed) {
        if (axis == 'x') {
            for (int i = 0; i < layers.size(); i++)
                layers[i].dest.x += speed;
            for (int i = 0; i < colliders.size(); i++)
                colliders[i].colDest.x += speed;
        }
        else {
            for (int i = 0; i < layers.size(); i++)
                layers[i].dest.y += speed;
            for (int i = 0; i < colliders.size(); i++)
                colliders[i].colDest.y += speed;
        }
    }

    bool CheckMapCollisions(SDL_Rect  &player) {
        for (int i = 0; i < colliders.size(); i++) {
            if (CheckCollision(player, colliders[i].colDest))
                return true;
        }

        return false;
    }
};
