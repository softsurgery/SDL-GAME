#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <stdbool.h>

typedef struct
{
    SDL_Texture *normalTexture;
    SDL_Texture *hoverTexture;
    SDL_Rect destRect;
    bool isHovered;
} HoverElement;

/**
 * Renders a texture and checks if mouse is hovering over it
 * Shows the hover texture when mouse is over the element, otherwise shows normal texture
 *
 * @param element The HoverElement structure containing textures and position
 * @param renderer SDL_Renderer to render with
 * @return bool True if element is being hovered over, false otherwise
 */
bool hoverElement(HoverElement *element, SDL_Renderer *renderer);

#endif
