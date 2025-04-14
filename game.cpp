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
    LoadMap("res/1.level");
    speed = 4;
    player.SetDest(Width/2-40, Height/2-48, 250/4, 249/4);
    player.SetImage("res/player.png", renderer);
    idol = player.CreateCycle(1, 250, 249, 1, 20);
    run = player.CreateCycle(1, 250, 249, 4, 6);
    player.SetCurrAnim(idol);
    Loop();
}

Game::~Game() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::Loop() {
    SDL_Event event;
    static int lastTime = 0;
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

    DrawMap();
    Draw(player);

    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS < (1000/60)) {
        SDL_Delay((1000/60) - timerFPS);
    }

    SDL_RenderPresent(renderer);
}

void Game::Draw(Object o) {
    SDL_Rect dest = o.GetDest();
    SDL_Rect src = o.GetSrc();
    SDL_RenderCopyEx(renderer, o.GetTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
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
            if(event.key.keysym.sym == SDLK_a) {l = 1; r = 0;}
            if(event.key.keysym.sym == SDLK_d) {r = 1; l = 0;}
            if(event.key.keysym.sym == SDLK_w) {u = 1; d = 0;}
            if(event.key.keysym.sym == SDLK_s) {d = 1; u = 0;}
        }
        if(event.type == SDL_KEYUP) {
            if(event.key.keysym.sym == SDLK_a) {l = 0; player.SetCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_d) {r = 0; player.SetCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_w) {u = 0; player.SetCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_s) {d = 0; player.SetCurrAnim(idol);}
        }
        SDL_GetMouseState(&mouse_x, &mouse_y);
    }
}

void Game::Update() {
    Object tempPlayer;
    bool canMove;

    if (l) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX() - speed, player.GetDY());
        canMove = true;
        for (auto& tile : map) {
            if (tile.GetID() == 3 && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run) player.SetCurrAnim(run);
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }

    if (r) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX() + speed, player.GetDY());
        canMove = true;
        for (auto& tile : map) {
            if (tile.GetID() == 3 && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run) player.SetCurrAnim(run);
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }

    if (u) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX(), player.GetDY() - speed);
        canMove = true;
        for (auto& tile : map) {
            if (tile.GetID() == 3 && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run) player.SetCurrAnim(run);
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }

    if (d) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX(), player.GetDY() + speed);
        canMove = true;
        for (auto& tile : map) {
            if (tile.GetID() == 3 && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run) player.SetCurrAnim(run);
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }

    SDL_Rect finalDest = player.GetDest();
    if (finalDest.x < 140) { player.SetDest(140, finalDest.y); Scroll(speed, 0); }
    if (finalDest.x > Width - 200) { player.SetDest(Width - 200, finalDest.y); Scroll(-speed, 0); }
    if (finalDest.y < 220) { player.SetDest(finalDest.x, 220); Scroll(0, speed); }
    if (finalDest.y > Height - 260) { player.SetDest(finalDest.x, Height - 260); Scroll(0, -speed); }

    player.UpdateAnimation();
}

void Game::LoadMap(const char *filename) {
    Object temp;
    temp.SetImage("res/colors_25px.png", renderer);
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
                temp.SetSolid(1);
                temp.SetSrc((current-1)*Tile_size, 0, Tile_size, Tile_size);
                temp.SetDest(j * Tile_size + mx, i * Tile_size + my, Tile_size, Tile_size);
                temp.SetID(current);              
                if(current == 3) temp.SetSolid(0);
                map.push_back(temp);
            }
        }
    }
    in.close();
}

void Game::DrawMap() {
    for (int i = 0; i < map.size(); i++) {
        int dx = map[i].GetDX();
        int dy = map[i].GetDY();

        bool visible = dx + Tile_size >= 0 &&
                       dy + Tile_size >= 0 &&
                       dx < Width &&
                       dy < Height;

        if (visible) {
            Draw(map[i]);
        }
    }
}

void Game::Scroll(int x, int y) {
    for (int i = 0; i < map.size(); i++) {
        map[i].SetDest(map[i].GetDX() + x, map[i].GetDY() + y);
    }
}

bool Game::Collision(Object a, Object b) {
    if((a.GetDX() < (b.GetDX() + b.GetDW())) && ((a.GetDX() + a.GetDW()) > b.GetDX()) && (a.GetDY() < (b.GetDY() + b.GetDH())) && ((a.GetDY() + a.GetDH()) > b.GetDY())) {
        return true;
    } else {
        return false;
    }
}