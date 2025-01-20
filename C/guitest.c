#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_SIZE 40
#define ENEMY_SIZE 20
#define BULLET_SIZE 10
#define PLAYER_SPEED 5
#define BULLET_SPEED 10
#define MAX_BULLETS 100
#define MAX_ENEMIES 50

typedef struct {
    float x, y;
    bool active;
} Bullet;

typedef struct {
    float x, y;
    bool active;
} Enemy;

typedef struct {
    float x, y;
} Player;

void DrawScore(SDL_Renderer* renderer, int score) {
    // This is a simple score display using rectangles
    // In a real game, you'd want to use SDL_ttf for text rendering
    for (int i = 0; i < score; i++) {
        SDL_Rect scoreRect = {10 + (i * 20), 10, 15, 15};
        SDL_RenderFillRect(renderer, &scoreRect);
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Shooting Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize game objects
    Player player = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    Bullet bullets[MAX_BULLETS] = {0};
    Enemy enemies[MAX_ENEMIES] = {0};
    int score = 0;

    // Time tracking
    Uint32 lastEnemySpawn = SDL_GetTicks();
    Uint32 enemySpawnInterval = 2000; // 10 seconds

    bool running = true;
    SDL_Event event;

    // Game loop
    while (running) {
        Uint32 currentTime = SDL_GetTicks();

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                // Shoot bullet on spacebar
                if (event.key.keysym.sym == SDLK_SPACE) {
                    for (int i = 0; i < MAX_BULLETS; i++) {
                        if (!bullets[i].active) {
                            bullets[i].x = player.x + PLAYER_SIZE/2 - BULLET_SIZE/2;
                            bullets[i].y = player.y;
                            bullets[i].active = true;
                            break;
                        }
                    }
                }
            }
        }

        // Handle player movement
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_W] && player.y > 0) {
            player.y -= PLAYER_SPEED;
        }
        if (keyState[SDL_SCANCODE_S] && player.y < WINDOW_HEIGHT - PLAYER_SIZE) {
            player.y += PLAYER_SPEED;
        }
        if (keyState[SDL_SCANCODE_A] && player.x > 0) {
            player.x -= PLAYER_SPEED;
        }
        if (keyState[SDL_SCANCODE_D] && player.x < WINDOW_WIDTH - PLAYER_SIZE) {
            player.x += PLAYER_SPEED;
        }

        // Spawn new enemy every 10 seconds
        if (currentTime - lastEnemySpawn >= enemySpawnInterval) {
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (!enemies[i].active) {
                    enemies[i].x = rand() % (WINDOW_WIDTH - ENEMY_SIZE);
                    enemies[i].y = rand() % (WINDOW_HEIGHT - ENEMY_SIZE);
                    enemies[i].active = true;
                    lastEnemySpawn = currentTime;
                    break;
                }
            }
        }

        // Update bullets
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y -= BULLET_SPEED;
                if (bullets[i].y < 0) {
                    bullets[i].active = false;
                }

                // Check collision with enemies
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active) {
                        if (bullets[i].x < enemies[j].x + ENEMY_SIZE &&
                            bullets[i].x + BULLET_SIZE > enemies[j].x &&
                            bullets[i].y < enemies[j].y + ENEMY_SIZE &&
                            bullets[i].y + BULLET_SIZE > enemies[j].y) {

                            bullets[i].active = false;
                            enemies[j].active = false;
                            score++;
                        }
                    }
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw player (white square)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect playerRect = {player.x, player.y, PLAYER_SIZE, PLAYER_SIZE};
        SDL_RenderFillRect(renderer, &playerRect);

        // Draw bullets (red)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                SDL_Rect bulletRect = {bullets[i].x, bullets[i].y, BULLET_SIZE, BULLET_SIZE};
                SDL_RenderFillRect(renderer, &bulletRect);
            }
        }

        // Draw enemies (green)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                SDL_Rect enemyRect = {enemies[i].x, enemies[i].y, ENEMY_SIZE, ENEMY_SIZE};
                SDL_RenderFillRect(renderer, &enemyRect);
            }
        }

        // Draw score (white)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        DrawScore(renderer, score);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Cap at ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
