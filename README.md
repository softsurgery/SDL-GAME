# Rotating Square SDL2 Project

This is a simple SDL2 application written in C. It demonstrates the basics of setting up an SDL2 window, handling events, rendering textures, and using the `SDL2_image` extension library.

## Project Scope

The application creates a window with the following features:

- **Initialization**: Sets up SDL2 video and SDL2_image (JPG support) subsystems.
- **Window & Renderer**: Creates an accelerated 2D rendering context with VSync enabled.
- **Asset Loading**: Loads a background image (`assets/bg.jpg`) using `SDL2_image`.
- **Procedural Texture**: Creates a red square texture programmatically using `SDL_CreateRGBSurface` and `SDL_CreateTextureFromSurface`.
- **Animation**: Rotates the square around its center in the main application loop.
- **Input Handling**: Listens for `SDL_QUIT` events to close the window (e.g., clicking the 'X' button).

## Prerequisites

To build and run this project, you need:

- **GCC** (GNU Compiler Collection)
- **SDL2 development libraries** (`libsdl2-dev`)
- **SDL2_image development libraries** (`libsdl2-image-dev`)
- **pkg-config** or `sdl2-config` utility

### Installing Dependencies (Linux/Debian-based)

```bash
sudo apt-get update
sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev
```

## Compilation

You can compile the project using the command line with `gcc`.

### Using `sdl2-config`

```bash
gcc main.c -o app $(sdl2-config --cflags --libs) -lSDL2_image
```

### Using `pkg-config` (Alternative)

```bash
gcc main.c -o app $(pkg-config --cflags --libs SDL2 SDL2_image)
```

## Running the Application

After compiling, run the executable:

```bash
./app
```

Ensure the `assets/` directory is in the same folder as the executable so the background image can be loaded correctly.
