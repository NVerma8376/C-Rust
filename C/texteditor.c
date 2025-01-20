#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FONT_SIZE 20
#define MAX_TEXT_LENGTH 10000
#define LINE_HEIGHT 24
#define PADDING 10

typedef struct {
    char* text;
    int cursorPos;
    int textLength;
    char filename[256];
    int isModified;
    int scrollOffset;
} Editor;

// Function prototypes
Editor* createEditor();
void destroyEditor(Editor* editor);
void renderText(SDL_Renderer* renderer, TTF_Font* font, Editor* editor);
void handleKeyPress(Editor* editor, SDL_KeyboardEvent* event);
void saveFile(Editor* editor);
void loadFile(Editor* editor, const char* filename);
void insertChar(Editor* editor, char c);
void deleteChar(Editor* editor);

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        printf("TTF initialization failed: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL Text Editor",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("/home/nverma/.fonts/Roboto-Regular.ttf", FONT_SIZE);
    if (!font) {
        printf("Font loading failed: %s\n", TTF_GetError());
        return 1;
    }

    Editor* editor = createEditor();
    if (argc > 1) {
        loadFile(editor, argv[1]);
    }

    SDL_StartTextInput();

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.mod & KMOD_CTRL) {
                        switch (event.key.keysym.sym) {
                            case SDLK_s:
                                saveFile(editor);
                                break;
                            case SDLK_q:
                                running = 0;
                                break;
                        }
                    } else {
                        handleKeyPress(editor, &event.key);
                    }
                    break;

                case SDL_TEXTINPUT:
                    insertChar(editor, event.text.text[0]);
                    break;

                case SDL_MOUSEWHEEL:
                    editor->scrollOffset -= event.wheel.y * LINE_HEIGHT;
                    if (editor->scrollOffset < 0) editor->scrollOffset = 0;
                    break;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_RenderClear(renderer);

        // Draw editor background
        SDL_SetRenderDrawColor(renderer, 42, 42, 42, 255);
        SDL_Rect editorRect = {PADDING, PADDING,
                              WINDOW_WIDTH - 2 * PADDING,
                              WINDOW_HEIGHT - 2 * PADDING};
        SDL_RenderFillRect(renderer, &editorRect);

        // Render text
        renderText(renderer, font, editor);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    destroyEditor(editor);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

Editor* createEditor() {
    Editor* editor = (Editor*)malloc(sizeof(Editor));
    editor->text = (char*)malloc(MAX_TEXT_LENGTH);
    editor->text[0] = '\0';
    editor->cursorPos = 0;
    editor->textLength = 0;
    editor->filename[0] = '\0';
    editor->isModified = 0;
    editor->scrollOffset = 0;
    return editor;
}

void destroyEditor(Editor* editor) {
    free(editor->text);
    free(editor);
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, Editor* editor) {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* surface;
    SDL_Texture* texture;

    // Render text
    if (editor->textLength > 0) {
        surface = TTF_RenderText_Blended_Wrapped(font, editor->text,
                                               textColor, WINDOW_WIDTH - 2 * PADDING);
        if (surface) {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect textRect = {PADDING, PADDING - editor->scrollOffset,
                                surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &textRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }

    // Render cursor
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int cursorX = PADDING;
    int cursorY = PADDING;

    // Calculate cursor position
    char temp = editor->text[editor->cursorPos];
    editor->text[editor->cursorPos] = '\0';
    surface = TTF_RenderText_Blended(font, editor->text, textColor);
    if (surface) {
        cursorX += surface->w;
        SDL_FreeSurface(surface);
    }
    editor->text[editor->cursorPos] = temp;

    SDL_Rect cursor = {cursorX, cursorY - editor->scrollOffset,
                      2, LINE_HEIGHT};
    SDL_RenderFillRect(renderer, &cursor);
}

void handleKeyPress(Editor* editor, SDL_KeyboardEvent* event) {
    switch (event->keysym.sym) {
        case SDLK_BACKSPACE:
            deleteChar(editor);
            break;

        case SDLK_LEFT:
            if (editor->cursorPos > 0) editor->cursorPos--;
            break;

        case SDLK_RIGHT:
            if (editor->cursorPos < editor->textLength) editor->cursorPos++;
            break;

        case SDLK_RETURN:
            insertChar(editor, '\n');
            break;
    }
}

void insertChar(Editor* editor, char c) {
    if (editor->textLength < MAX_TEXT_LENGTH - 1) {
        memmove(&editor->text[editor->cursorPos + 1],
                &editor->text[editor->cursorPos],
                editor->textLength - editor->cursorPos + 1);
        editor->text[editor->cursorPos] = c;
        editor->cursorPos++;
        editor->textLength++;
        editor->isModified = 1;
    }
}

void deleteChar(Editor* editor) {
    if (editor->cursorPos > 0) {
        memmove(&editor->text[editor->cursorPos - 1],
                &editor->text[editor->cursorPos],
                editor->textLength - editor->cursorPos + 1);
        editor->cursorPos--;
        editor->textLength--;
        editor->isModified = 1;
    }
}

void saveFile(Editor* editor) {
    if (editor->filename[0] == '\0') {
        // In a real application, you'd want to show a file dialog here
        strcpy(editor->filename, "untitled.txt");
    }

    FILE* file = fopen(editor->filename, "w");
    if (file) {
        fwrite(editor->text, 1, editor->textLength, file);
        fclose(file);
        editor->isModified = 0;
    }
}

void loadFile(Editor* editor, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        editor->textLength = fread(editor->text, 1, MAX_TEXT_LENGTH - 1, file);
        editor->text[editor->textLength] = '\0';
        editor->cursorPos = editor->textLength;
        strcpy(editor->filename, filename);
        fclose(file);
    }
}
