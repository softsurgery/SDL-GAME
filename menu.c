#include "menu.h"
#include <stdio.h>

const int SQUARE_SIZE = 100;

Menu *menu_init(SDL_Renderer *renderer)
{
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    if (!menu)
    {
        printf("Failed to allocate memory for Menu struct.\n");
        return NULL;
    }

    // Load background texture
    menu->bgTexture = IMG_LoadTexture(renderer, "assets/images/bg.jpg");
    if (!menu->bgTexture)
    {
        printf("Failed to load background texture! SDL_image Error: %s\n", IMG_GetError());
        free(menu);
        return NULL;
    }

    // Create a square texture
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
        SDL_DestroyTexture(menu->bgTexture);
        free(menu);
        return NULL;
    }

    // Fill it with a color (e.g., Red)
    if (SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0)) != 0)
    {
        printf("FillRect failed! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(menu->bgTexture);
        free(menu);
        return NULL;
    }

    // Convert to texture
    menu->squareTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!menu->squareTexture)
    {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(menu->bgTexture);
        free(menu);
        return NULL;
    }

    // Initialize state
    menu->angle = 0.0;

    // We assume window size 800x600 for centering.
    // Ideally pass window size or query it if needed.
    menu->destRect.w = SQUARE_SIZE;
    menu->destRect.h = SQUARE_SIZE;
    menu->destRect.x = (800 - SQUARE_SIZE) / 2;
    menu->destRect.y = (600 - SQUARE_SIZE) / 2;

    return menu;
}

void menu_update(Menu *menu)
{
    if (!menu)
        return;

    menu->angle += 2.0;
    if (menu->angle > 360.0)
    {
        menu->angle -= 360.0;
    }
}

void menu_render(Menu *menu, SDL_Renderer *renderer)
{
    if (!menu || !renderer)
        return;

    // Render background
    SDL_RenderCopy(renderer, menu->bgTexture, NULL, NULL);

    // Render rotating square
    // Center is NULL (rotates around center), flip is NONE
    SDL_RenderCopyEx(renderer, menu->squareTexture, NULL, &menu->destRect, menu->angle, NULL, SDL_FLIP_NONE);
}

void menu_destroy(Menu *menu)
{
    if (!menu)
        return;

    if (menu->squareTexture)
    {
        SDL_DestroyTexture(menu->squareTexture);
    }
    if (menu->bgTexture)
    {
        SDL_DestroyTexture(menu->bgTexture);
    }
    free(menu);
}
