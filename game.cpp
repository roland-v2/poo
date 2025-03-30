#include "game.h"

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_CreateWindowAndRenderer(360, 240, 0, &window, &renderer) != 0) {
        std::cerr << "Window and renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_SetWindowTitle(window, "Game Window");
    SDL_ShowWindow(window);
    TTF_Init();
    running = true;
    count = 0;
    star.setDest(50, 50, 58, 55);
    star.setSrc(0, 0, 580, 550);
    star.setImage("star.png", renderer);
    Loop();
}

Game::~Game() {
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Loop() {
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        lastFrame = SDL_GetTicks();
        static int lastTime;
        if(lastFrame >= (lastTime + 1000)) {
            lastTime = lastFrame;
            frameCount = 0;
            count++;
        }

        Render();
        Input();
        Update();

        if(count > 3) running = false;
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = 360;
    rect.h = 240;
    SDL_RenderFillRect(renderer, &rect);

    Draw(star);
    Draw("Pupicei", 120, 65, 255, 255, 255, 12);

    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS < (1000/60)) {
        SDL_Delay((1000/60) - timerFPS);
    }

    SDL_RenderPresent(renderer);
}

void Game::Draw(Object o) {
    SDL_Rect dest = o.getDest();
    SDL_Rect src = o.getSrc();
    SDL_RenderCopyEx(renderer, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void Game::Draw(const char *msg, int x, int y, int r, int g, int b, int size) {
    SDL_Surface *surf;
    SDL_Texture *tex;
    TTF_Font *font = TTF_OpenFont("sans.ttf", size);
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, msg, color);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    rect.x = x;
    rect.y = y;
    rect.w = surf -> w;
    rect.h = surf -> h;
    SDL_FreeSurface(surf);
    SDL_RenderCopy(renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);

}
