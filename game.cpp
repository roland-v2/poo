#include "game.h"

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
    star.setImage("res/star.png", renderer);
    font = TTF_OpenFont("res/sans.ttf", 12);
    effect.Load("res/button.wav");
    effect2.Load("res/ice.wav");
    player.setImage("res/penguin.png", renderer);
    player.setDest(150, 20, 50*3, 65*3);
    idol = player.createCycle(1, 128, 128, 4, 12);
    //shield = player.createCycle(1, 128, 128, 4, 12);
    player.setCurrAnim(idol);
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
        }
        Render();
        Input();
        Update();
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
    Draw("HauBau", 120, 65, 255, 255, 255);
    Draw(player);

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

void Game::Draw(const char *msg, int x, int y, int r, int g, int b) {
    SDL_Surface *surf;
    SDL_Texture *tex;
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

void Game::Input() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = false;
            std::cout << "Quit" << std::endl;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_ESCAPE) running = false;
            if(event.key.keysym.sym == SDLK_w) {
                std::cout << "w down" << std::endl; 
                //player.setCurrAnim(shield);
                //effect.Play();
            }
            if(event.key.keysym.sym == SDLK_a) {
                std::cout << "a down" << std::endl; 
                //effect2.Play();
            }
        }
        if(event.type == SDL_KEYUP) {
            if(event.key.keysym.sym == SDLK_w) {
                std::cout << "w up" << std::endl;
            }
        }
        SDL_GetMouseState(&mouse_x, &mouse_y);
    }
}

void Game::Update() {
    player.updateAnimation();
}