#include "SDL2/SDL.h"
#include "Engine/Engine.h"
#undef main

int main(int argc,  char* argv[]){

    // Create the engine.
    Engine engine;
    
    // If init succeeds, we can "run" the engine.
    bool initSucceeded = engine.Initialize();
    if (initSucceeded)
    {
        engine.Loop();
    }
    engine.Shutdown();
    return 0;
}
