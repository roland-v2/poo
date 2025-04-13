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
    speed = 4;
    player.setDest(Width/2-40, Height/2-48, 250/4, 249/4);
    player.setImage("res/animation.png", renderer);
    idol = player.createCycle(1, 250, 249, 1, 20);
    run = player.createCycle(1, 250, 249, 4, 6);
    player.setCurrAnim(idol);
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

    drawMap();
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
            if(event.key.keysym.sym == SDLK_a) {l = 1; r = 0;}
            if(event.key.keysym.sym == SDLK_d) {r = 1; l = 0;}
            if(event.key.keysym.sym == SDLK_w) {u = 1; d = 0;}
            if(event.key.keysym.sym == SDLK_s) {d = 1; u = 0;}
        }
        if(event.type == SDL_KEYUP) {
            if(event.key.keysym.sym == SDLK_a) {l = 0; player.setCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_d) {r = 0; player.setCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_w) {u = 0; player.setCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_s) {d = 0; player.setCurrAnim(idol);}
        }
        SDL_GetMouseState(&mouse_x, &mouse_y);
    }
}

void Game::Update() {
    Object tempPlayer;
    bool canMove;

    if (l) {
        tempPlayer = player;
        tempPlayer.setDest(player.getDX() - speed, player.getDY());
        canMove = true;
        for (auto& tile : map) {
            if (tile.getID() == 3 && collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.getCurrAnim() != run) player.setCurrAnim(run);
            player.setDest(tempPlayer.getDX(), tempPlayer.getDY());
        }
    }

    if (r) {
        tempPlayer = player;
        tempPlayer.setDest(player.getDX() + speed, player.getDY());
        canMove = true;
        for (auto& tile : map) {
            if (tile.getID() == 3 && collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.getCurrAnim() != run) player.setCurrAnim(run);
            player.setDest(tempPlayer.getDX(), tempPlayer.getDY());
        }
    }

    if (u) {
        tempPlayer = player;
        tempPlayer.setDest(player.getDX(), player.getDY() - speed);
        canMove = true;
        for (auto& tile : map) {
            if (tile.getID() == 3 && collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.getCurrAnim() != run) player.setCurrAnim(run);
            player.setDest(tempPlayer.getDX(), tempPlayer.getDY());
        }
    }

    if (d) {
        tempPlayer = player;
        tempPlayer.setDest(player.getDX(), player.getDY() + speed);
        canMove = true;
        for (auto& tile : map) {
            if (tile.getID() == 3 && collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.getCurrAnim() != run) player.setCurrAnim(run);
            player.setDest(tempPlayer.getDX(), tempPlayer.getDY());
        }
    }

    SDL_Rect finalDest = player.getDest();
    if (finalDest.x < 140) { player.setDest(140, finalDest.y); scroll(speed, 0); }
    if (finalDest.x > Width - 200) { player.setDest(Width - 200, finalDest.y); scroll(-speed, 0); }
    if (finalDest.y < 220) { player.setDest(finalDest.x, 220); scroll(0, speed); }
    if (finalDest.y > Height - 260) { player.setDest(finalDest.x, Height - 260); scroll(0, -speed); }

    player.updateAnimation();
}

void Game::loadMap(const char *filename) {
    Object temp;
    temp.setImage("res/colors.png", renderer);
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
                temp.setSolid(1);
                temp.setSrc((current-1)*Tile_size, 0, Tile_size, Tile_size);
                temp.setDest(j * Tile_size + mx, i * Tile_size + my, Tile_size, Tile_size);
                temp.setID(current);              
                if(current == 3) temp.setSolid(0);
                map.push_back(temp);
            }
        }
    }
    in.close();
}

void Game::drawMap() {
    for (int i = 0; i < map.size(); i++) {
        int dx = map[i].getDX();
        int dy = map[i].getDY();

        bool visible = dx + Tile_size >= 0 &&
                       dy + Tile_size >= 0 &&
                       dx < Width &&
                       dy < Height;

        if (visible) {
            Draw(map[i]);
        }
    }
}

void Game::scroll(int x, int y) {
    for (int i = 0; i < map.size(); i++) {
        map[i].setDest(map[i].getDX() + x, map[i].getDY() + y);
    }
}

bool Game::collision(Object a, Object b) {
    if((a.getDX() < (b.getDX() + b.getDW())) && ((a.getDX() + a.getDW()) > b.getDX()) && (a.getDY() < (b.getDY() + b.getDH())) && ((a.getDY() + a.getDH()) > b.getDY())) {
        return true;
    } else {
        return false;
    }
}