#include "utils.h"
#include "string.h"

bool hoverElement(HoverElement *element, SDL_Renderer *renderer)
{
    if (!element || !renderer || !element->normalTexture || !element->hoverTexture)
        return false;

    // Get current mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Check if mouse is within element bounds
    bool isHovering = (mouseX >= element->destRect.x &&
                       mouseX <= element->destRect.x + element->destRect.w &&
                       mouseY >= element->destRect.y &&
                       mouseY <= element->destRect.y + element->destRect.h);

    element->isHovered = isHovering;

    // Render the appropriate texture based on hover state
    SDL_Texture *textureToRender = isHovering ? element->hoverTexture : element->normalTexture;
    SDL_RenderCopy(renderer, textureToRender, NULL, &element->destRect);

    return isHovering;
}
