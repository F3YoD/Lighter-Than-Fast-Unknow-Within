#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "shared.h"
#include "macros.h"
#include "menu.h"
#include "game.h"
#include "tools.h"

#define FIRAMONO_PATH "../assets/fonts/firamono.ttf"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

int
main(void)
{
    // Prepare PRNG
    srand(time(NULL));

    // Load SDL
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int img_init = IMG_Init(img_flags);
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || img_init != img_flags || TTF_Init() != 0)
    {
        fprintf(stderr, "/!\\ Could not init SDL: %s\nSDL_image flags: %d/%d\n",
                SDL_GetError(), img_init, img_flags);
        return EXIT_FAILURE;
    }

    // Create window
    window = SDL_CreateWindow("Lighter Than Fast: Unknown Within",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    check_SDL(window);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    check_SDL(renderer);

    // Load fonts
    font = TTF_OpenFont(FIRAMONO_PATH, 22);
    check_TTF(font);

    play_game();

    // Clean everything SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
