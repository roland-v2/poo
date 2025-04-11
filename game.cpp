#include "game.h"

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_CreateWindowAndRenderer(Width, Height, 0, &window, &renderer) != 0) {
        std::cerr << "Window and renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_SetWindowTitle(window, "Game Window");
    SDL_ShowWindow(window);
    TTF_Init();
    running = true;
    count = 0;
    font = TTF_OpenFont("res/sans.ttf", 12);
    loadMap("res/2.level");
    Loop();
}

Game::~Game() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Loop() {
    SDL_Event event;
    static int lastTime;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        lastFrame = SDL_GetTicks();
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
    SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = Width;
    rect.h = Height;
    SDL_RenderFillRect(renderer, &rect);

    drawMap();
    //draw(player);

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
        }
        SDL_GetMouseState(&mouse_x, &mouse_y);
    }
}

void Game::Update() {
    //player.updateAnimation();
}

void Game::loadMap(const char *filename) {
    int current, mx, my, mw, mh;
    ifstream in(filename);
    if(!in.is_open()) {
        cout << "Failed to open map file" << endl;
        return;
    }
    in >> mw;
    in >> mh;
    in >> mx;
    in >> my;
    for(int i = 0; i < mh; i++) {
        for(int j = 0; j < mw; j++) {
            if(in.eof()) {
                cout << "Reached end of map file too soon" << endl;
                return;
            }
            in >> current;
            if(current != 0) {
                Object temp;
                temp.setImage("res/Untitled1.png", renderer);
                temp.setSrc((current-1)*Tile_size, 0, Tile_size, Tile_size);
                temp.setDest(j * Tile_size + mx, i * Tile_size + my, Tile_size, Tile_size);                if(current == 2 || current == 4) temp.setSolid(0);
                map.push_back(temp);
            }
        }
    }
    in.close();
}

void Game::drawMap() {
    for (int i = 0; i < map.size(); i++) {
        Draw(map[i]);
    }
}