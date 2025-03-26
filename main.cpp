// Proiect POO - Boldesco Roland

#include "monster.h"
#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_mixer.h>
#include <iostream>

#define width 1280
#define height 720

bool b_running, b_fullscreen;

SDL_Renderer *renderer;
SDL_Window *window;

int i_frame_count, i_timer_fps, i_last_frame, i_fps;

void update() {
    if(b_fullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    if(!b_fullscreen) {
        SDL_SetWindowFullscreen(window, 0);
    }
}

void input() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            b_running = false;
        }
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.scancode == SDL_SCANCODE_F){
                b_fullscreen = !b_fullscreen;
            }
            if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                b_running = false;
            }
        }
    }
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = width;
    rect.h = height;
    SDL_RenderFillRect(renderer, &rect);
    i_frame_count++;
    int i_timer_fps = SDL_GetTicks() - i_last_frame;
    if(i_timer_fps < (1000/60)) {
        SDL_Delay((1000/60) - i_timer_fps);
    }
    SDL_RenderPresent(renderer);
}

int main() {
    b_running = true;
    b_fullscreen = false;
    static int i_last_time = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Failed SDL_Init()" << std::endl;
    }
    if(SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
        std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    }
    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    while(b_running) {
        i_last_frame = SDL_GetTicks();
        if(i_last_frame >= (i_last_time + 1000)) {
            i_last_time = i_last_frame;
            i_fps = i_frame_count;
            i_frame_count = 0;
        }
        std::cout << i_fps << std::endl;

        update();
        input();
        draw();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}