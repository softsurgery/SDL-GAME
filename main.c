#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SQUARE_SIZE = 100;

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    printf("SDL Initialized.\n");

    // Create window
    SDL_Window *window = SDL_CreateWindow("Rotating Square",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    // (Use VSYNC to cap framerate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a surface with explicit masks for cross-platform compatibility
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_Surface *surface = SDL_CreateRGBSurface(0, SQUARE_SIZE, SQUARE_SIZE, 32, rmask, gmask, bmask, amask);
    if (!surface)
    {
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Fill it with a color (e.g., Red)
    if (SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0)) != 0)
    {
        printf("FillRect failed! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Convert to texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Don't need the surface anymore

    if (!texture)
    {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop variables
    bool quit = false;
    SDL_Event e;
    double angle = 0.0;
    SDL_Rect destRect = {
        (WINDOW_WIDTH - SQUARE_SIZE) / 2,
        (WINDOW_HEIGHT - SQUARE_SIZE) / 2,
        SQUARE_SIZE,
        SQUARE_SIZE};

    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        angle += 2.0;
        if (angle > 360.0)
            angle -= 360.0;

        SDL_SetRenderDrawColor(renderer, 0x00, 0x40, 0x48, 0xFF);
        SDL_RenderClear(renderer);

        // Render rotating square
        SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
