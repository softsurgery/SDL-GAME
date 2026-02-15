#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include <malloc.h>

const int SQUARE_SIZE = 100;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 100;

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

    // Load start button textures
    menu->startButton.normalTexture = IMG_LoadTexture(renderer, "assets/images/start.png");
    if (!menu->startButton.normalTexture)
    {
        printf("Failed to load start button texture! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyTexture(menu->squareTexture);
        SDL_DestroyTexture(menu->bgTexture);
        free(menu);
        return NULL;
    }

    menu->startButton.hoverTexture = IMG_LoadTexture(renderer, "assets/images/start-hover.png");
    if (!menu->startButton.hoverTexture)
    {
        printf("Failed to load start hover texture! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyTexture(menu->startButton.normalTexture);
        SDL_DestroyTexture(menu->squareTexture);
        SDL_DestroyTexture(menu->bgTexture);
        free(menu);
        return NULL;
    }

    // Initialize start button position and size (centered horizontally, positioned in lower half)
    menu->startButton.destRect.w = BUTTON_WIDTH;
    menu->startButton.destRect.h = BUTTON_HEIGHT;
    menu->startButton.destRect.x = (800 - BUTTON_WIDTH) / 2;
    menu->startButton.destRect.y = 450;
    menu->startButton.isHovered = false;

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

void menu_render_start_button(Menu *menu, SDL_Renderer *renderer)
{
    if (!menu || !renderer)
        return;

    // Use the hoverElement utility to render start button with hover detection
    hoverElement(&menu->startButton, renderer);
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

    // Render start button
    menu_render_start_button(menu, renderer);
}

void menu_destroy(Menu *menu)
{
    if (!menu)
        return;

    if (menu->startButton.normalTexture)
    {
        SDL_DestroyTexture(menu->startButton.normalTexture);
    }
    if (menu->startButton.hoverTexture)
    {
        SDL_DestroyTexture(menu->startButton.hoverTexture);
    }
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
