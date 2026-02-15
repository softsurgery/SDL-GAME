# SDL2 Function Explanations

This document explains the SDL2 functions used in `main.c`.

## Initialization & Cleanup

### `SDL_Init(Uint32 flags)`

- **Description**: Initializes the SDL library. This must be called before using most other SDL functions.
- **Arguments Used**:
  - `SDL_INIT_VIDEO`: Initializes the video subsystem (needed for creating windows and rendering).
- **Returns**: 0 on success, or a negative error code on failure.

### `SDL_Quit(void)`

- **Description**: Cleans up all initialized SDL subsystems. This should be called upon exiting the application.
- **Arguments**: None.

### `SDL_GetError(void)`

- **Description**: Returns a message string containing information about the last internal SDL error that occurred.
- **Arguments**: None.
- **Returns**: A C-string (const char\*) describing the error.

## Window Management

### `SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags)`

- **Description**: Creates a window with the specified position, dimensions, and flags.
- **Arguments Used**:
  - `"Rotating Square"`: The title of the window.
  - `SDL_WINDOWPOS_CENTERED`: Centers the window on the screen (used for both x and y).
  - `WINDOW_WIDTH`: The width of the window (800).
  - `WINDOW_HEIGHT`: The height of the window (600).
  - `SDL_WINDOW_SHOWN`: Ensures the window is visible when created.
- **Returns**: A pointer to the created `SDL_Window`, or `NULL` on failure.

### `SDL_DestroyWindow(SDL_Window* window)`

- **Description**: Destroys a window.
- **Arguments Used**:
  - `window`: The window to destroy.

## Rendering

### `SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags)`

- **Description**: Creates a 2D rendering context for a window.
- **Arguments Used**:
  - `window`: The window where rendering is displayed.
  - `-1`: Initializes the first rendering driver supporting the requested flags.
  - `SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC`: Uses hardware acceleration and synchronizes updates with the monitor's refresh rate (VSync).
- **Returns**: A pointer to the created `SDL_Renderer`, or `NULL` on failure.

### `SDL_DestroyRenderer(SDL_Renderer* renderer)`

- **Description**: Destroys a rendering context.
- **Arguments Used**:
  - `renderer`: The renderer to destroy.

### `SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)`

- **Description**: Sets the color used for drawing operations (like clearing the screen).
- **Arguments Used**:
  - `renderer`: The rendering context.
  - `0x00, 0x00, 0x00, 0xFF`: Red, Green, Blue, Alpha values (Black, fully opaque).

### `SDL_RenderClear(SDL_Renderer* renderer)`

- **Description**: Clears the entire rendering target with the drawing color set by `SDL_SetRenderDrawColor`.
- **Arguments Used**:
  - `renderer`: The rendering context to clear.

### `SDL_RenderPresent(SDL_Renderer* renderer)`

- **Description**: Updates the screen with any rendering performed since the previous call. SDL uses double buffering, so this swaps the back buffer (where you draw) to the front buffer (screen).
- **Arguments Used**:
  - `renderer`: The rendering context.

### `SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect)`

- **Description**: Copies a portion of the texture to the current rendering target.
- **Arguments Used**:
  - `renderer`: The rendering context.
  - `bgTexture`: The background texture.
  - `NULL`: The entire texture is used as the source.
  - `NULL`: The texture is stretched to fill the entire rendering target.

### `SDL_RenderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, double angle, const SDL_Point* center, SDL_RendererFlip flip)`

- **Description**: Copies a portion of the texture to the current rendering target, with optional rotation and flipping.
- **Arguments Used**:
  - `renderer`: The rendering context.
  - `texture`: The source texture.
  - `NULL`: The entire texture is used as the source.
  - `&destRect`: Pointer to the destination rectangle defining where and what size to render the texture.
  - `angle`: The angle of rotation in degrees.
  - `NULL`: The center of rotation (NULL implies rotating around the texture's center).
  - `SDL_FLIP_NONE`: No flipping (mirroring) applied.

## Surface & Texture Management

### `SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)`

- **Description**: Allocates a new RGB surface.
- **Arguments Used**:
  - `0`: Reserved flags (unused).
  - `SQUARE_SIZE`: Width and height (100).
  - `32`: Depth of the surface in bits (32-bit color).
  - `rmask, gmask, bmask, amask`: Bitmasks for Red, Green, Blue, and Alpha channels (platform-dependent).

### `SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)`

- **Description**: Creates a texture from an existing surface. Textures are stored in GPU memory for fast rendering.
- **Arguments Used**:
  - `renderer`: The rendering context.
  - `surface`: The source surface containing pixel data.
- **Returns**: A pointer to the created `SDL_Texture`.

### `SDL_FreeSurface(SDL_Surface* surface)`

- **Description**: Frees the memory used by a surface.
- **Arguments Used**:
  - `surface`: The surface to free.

### `SDL_DestroyTexture(SDL_Texture* texture)`

- **Description**: Destroys the specified texture.
- **Arguments Used**:
  - `texture`: The texture to destroy.

### `SDL_MapRGB(const SDL_PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)`

- **Description**: Maps an RGB color value to a pixel format.
- **Arguments Used**:
  - `surface->format`: The pixel format of the surface.
  - `255, 0, 0`: The Red, Green, and Blue values (Red).

### `SDL_FillRect(SDL_Surface* dst, const SDL_Rect* rect, Uint32 color)`

- **Description**: Performs a fast fill of a rectangle with a specific color.
- **Arguments Used**:
  - `surface`: The surface to fill.
  - `NULL`: The rectangle to fill (NULL fills the entire surface).
  - `...`: The mapped color value from `SDL_MapRGB`.

## Event Handling

### `SDL_PollEvent(SDL_Event* event)`

- **Description**: Polls for currently pending events.
- **Arguments Used**:
  - `&e`: Pointer to an `SDL_Event` structure to be filled with the next event from the queue.
- **Returns**: 1 if there is a pending event, or 0 if there are none available.

## SDL2_image Extension

### `IMG_Init(int flags)`

- **Description**: Initializes the SDL_image library with support for specified image formats.
- **Arguments Used**:
  - `IMG_INIT_JPG`: Initializes support for loading JPG images.
- **Returns**: A bitmask of all the successfully initialized loaders.

### `IMG_Quit(void)`

- **Description**: Cleans up the SDL_image library. This should be called to free resources used by SDL_image.
- **Arguments**: None.

### `IMG_GetError(void)`

- **Description**: Returns a message string containing information about the last internal SDL_image error.
- **Arguments**: None.
- **Returns**: A C-string describing the error.

### `IMG_LoadTexture(SDL_Renderer* renderer, const char* file)`

- **Description**: Loads an image from a file directly into a texture. This is a convenience function that combines loading a surface and creating a texture from it.
- **Arguments Used**:
  - `renderer`: The rendering context.
  - `"assets/bg.jpg"`: Relative path to the image file to load.
- **Returns**: A pointer to the created `SDL_Texture`, or `NULL` on failure.
