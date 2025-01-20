#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_N 10

// Calculate factorial
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long long fact = 1;
    for(int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Function to draw text
void drawText(SDL_Renderer* renderer, TTF_Font* font, char* text, int x, int y) {
    SDL_Color color = {0, 0, 0};  // Black color
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Factorial Graph",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Load font
    font = TTF_OpenFont("/home/nverma/.fonts/Roboto-Regular.ttf", 16);
    if (!font) {
        printf("Font loading failed: %s\n", TTF_GetError());
        return 1;
    }

    // Calculate factorials
    unsigned long long facts[MAX_N + 1];
    unsigned long long max_fact = 0;

    for (int i = 0; i <= MAX_N; i++) {
        facts[i] = factorial(i);
        if (facts[i] > max_fact) max_fact = facts[i];
    }

    // Main loop
    SDL_bool quit = SDL_FALSE;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw bars
        const int bar_width = 50;
        const int spacing = 10;
        const int max_height = 500;
        const int start_x = 50;
        const int base_y = 550;

        for (int i = 0; i <= MAX_N; i++) {
            int height = (int)((double)facts[i] * max_height / max_fact);
            if (facts[i] > 0 && height < 2) height = 2;  // Minimum visible height

            SDL_Rect bar = {
                start_x + i * (bar_width + spacing),
                base_y - height,
                bar_width,
                height
            };

            // Draw bar
            SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
            SDL_RenderFillRect(renderer, &bar);

            // Draw border
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &bar);

            // Draw number labels
            char label[32];
            sprintf(label, "%d", i);
            drawText(renderer, font, label,
                    start_x + i * (bar_width + spacing) + bar_width/3,
                    base_y + 10);

            // Draw factorial values
            sprintf(label, "%llu", facts[i]);
            drawText(renderer, font, label,
                    start_x + i * (bar_width + spacing) + bar_width/4,
                    base_y - height - 20);
        }

        // Draw title
        drawText(renderer, font, "Factorial Graph (0 to 10)",
                WINDOW_WIDTH/2 - 100, 20);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
