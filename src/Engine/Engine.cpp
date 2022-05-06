#include "Engine.h"

bool Engine::Initialize()
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    if (TTF_Init() < 0) {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    window = SDL_CreateWindow("A Snowcone during Winter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, 0);

    InitializeObjects();

    // Initialized successfully.
    return true;
}

void Engine::Shutdown()
{
    // Destroy created window.
    if (window != nullptr){
        SDL_DestroyWindow(window);
    }
    if (renderer != nullptr)
        SDL_DestroyRenderer(renderer);

    // De-initialize SDL.
    SDL_Quit();
}

void Engine::Loop()
{
    // We are running!
    isRunning = true;

    while (isRunning)
    {
        lastFrame = SDL_GetTicks();
        static int lastTime;
        if (lastFrame >= (lastTime + 1000)) {
            lastTime = lastFrame;
            frameCount = 0;
        }
        
        Update();
        Render();
        Events();
    }
}

void Engine::Events()
{
    // We'll poll for events here. Catch the quit event.
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type)
    {
        case SDL_QUIT:
        isRunning = false;
        break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    player.WalkUp();
                    map.Move('y', player.walkingSpeed);
                    iceCream.Move('y', player.walkingSpeed);
                    coffeeMachine.Move('y', player.walkingSpeed);
                    snowConeMachine.Move('y', player.walkingSpeed);
                    customers.Move('y', player.walkingSpeed);
                    break;

                case SDLK_a:
                    player.WalkLeft();
                    map.Move('x', player.walkingSpeed);
                    iceCream.Move('x', player.walkingSpeed);
                    coffeeMachine.Move('x', player.walkingSpeed);
                    snowConeMachine.Move('x', player.walkingSpeed);
                    customers.Move('x', player.walkingSpeed);
                    break;

                case SDLK_s:
                    player.WalkDown();
                    map.Move('y', -player.walkingSpeed);
                    iceCream.Move('y', -player.walkingSpeed);
                    coffeeMachine.Move('y', -player.walkingSpeed);
                    snowConeMachine.Move('y', -player.walkingSpeed);
                    customers.Move('y', -player.walkingSpeed);
                    break;

                case SDLK_d:
                    player.WalkRight();
                    map.Move('x', -player.walkingSpeed);
                    iceCream.Move('x', -player.walkingSpeed);
                    coffeeMachine.Move('x', -player.walkingSpeed);
                    snowConeMachine.Move('x', -player.walkingSpeed);
                    customers.Move('x', -player.walkingSpeed);
                    break;
            }
            break;

        case SDL_KEYUP:
            player.ReturnToIdle();
            break; 

        case SDL_MOUSEBUTTONDOWN:
            CheckForOrderPickup();

            break;
    }    
}

void Engine::Update()
{
    UpdateObjects();
}

void Engine::Render()
{
    SDL_RenderClear(renderer);

    RenderObjects();

    SDL_Surface* text;
    // Set color to black
    SDL_Color color = { 0, 0, 0 };

    text = TTF_RenderText_Solid(font, "Hello World!", color);
    if (!text) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }

    SDL_Texture* text_texture;

    text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect dest = { 0, 0, text->w, text->h };

    SDL_RenderCopy(renderer, text_texture, &dest);

    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / 60)) {
        SDL_Delay((1000 / 60) - timerFPS);
    }
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 1);

    SDL_RenderPresent(renderer);

}


