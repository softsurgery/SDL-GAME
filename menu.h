#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "utils.h"

typedef struct
{
    SDL_Texture *bgTexture;
    SDL_Texture *squareTexture;
    double angle;
    SDL_Rect destRect;
    HoverElement startButton;
} Menu;

Menu *menu_init(SDL_Renderer *renderer);
void menu_update(Menu *menu);
void menu_render(Menu *menu, SDL_Renderer *renderer);
void menu_render_start_button(Menu *menu, SDL_Renderer *renderer);
void menu_destroy(Menu *menu);

#endif
