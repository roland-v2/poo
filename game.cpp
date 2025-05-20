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
    playerSpeed = 4;
    player.SetDest(Width/2-40, Height/2-48, 250/4, 249/4);
    player.SetImage("res/player_r.png", renderer);
    
    idol = player.CreateCycle(1, 250, 249, 1, 20);
    run = player.CreateCycle(1, 250, 249, 4, 6);
    player.SetCurrAnim(idol);

    // Initialize enemies pointer
    enemies = new std::vector<Enemy>();
    
    InitEnemies(); // Initialize enemies here
    
    Loop();
}

Game::~Game() {
    // Delete the enemies vector
    delete enemies;
    
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::InitEnemies() {
    // Clear existing enemies
    enemies->clear();
    
    // Add new enemies
    Enemy enemy1;
    enemy1.SetImage("res/enemy.png", renderer);
    enemy1.SetDest(Width/2+700, Height/2-48, 900/5, 381/5);
    enemy1.SetSrc(0, 0, 900, 381); // Set source rectangle for enemy1
    enemies->push_back(enemy1);
    
    /*
    Enemy enemy2;
    enemy2.SetImage("res/enemy.png", renderer);
    enemy2.SetDest(Width/2+400, Height/2+8, 900/5, 381/5);
    enemy2.SetSrc(0, 0, 900, 381); // Set source rectangle for enemy2
    enemies->push_back(enemy2);

    Enemy enemy3;
    enemy3.SetImage("res/enemy.png", renderer);
    enemy3.SetDest(Width/2+400, Height/2+58, 900/5, 381/5);
    enemy3.SetSrc(0, 0, 900, 381); // Set source rectangle for enemy3
    enemies->push_back(enemy3);
    */
}

void Game::Loop() {
    static int lastTime = 0;
    while (running) {
        Input();
        
        // Only update game state if not paused
        if (!menu.IsPaused()) {
            lastFrame = SDL_GetTicks();
            if(lastFrame >= (lastTime + 1000)) {
                lastTime = lastFrame;
                frameCount = 0;
            }
            Update();
        }
        
        Render();
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
    
    // Draw enemies
    for (auto& enemy : *enemies) {
        Draw(enemy);
    }

    // Display player stats in the top-left corner
    char scoreText[50];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", player.GetScore());
    Draw(scoreText, 20, 20, 255, 255, 255);
    
    char livesText[50];
    snprintf(livesText, sizeof(livesText), "Lives: %d", player.GetLives());
    Draw(livesText, 20, 50, 255, 255, 255);
    
    char healthText[50];
    snprintf(healthText, sizeof(healthText), "Health: %d/%d", player.GetHealth(), player.GetMaxHealth());
    
    // Determine health text color based on health percentage
    int healthPercentage = (player.GetHealth() * 100) / player.GetMaxHealth();
    int r, g, b;

    if (healthPercentage > 70) {
        // Green for high health
        r = 0; g = 255; b = 0;
    } else if (healthPercentage > 30) {
        // Yellow for medium health
        r = 255; g = 255; b = 0;
    } else {
        // Red for low health
        r = 255; g = 0; b = 0;
    }

    Draw(healthText, 20, 80, r, g, b);

        char pauseText[50];
        snprintf(pauseText, sizeof(pauseText), "Press P to pause/unpause game");
        Draw(pauseText, 20, 110, 255, 255, 255);

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
    
    surf = TTF_RenderText_Solid(font, msg, color);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    
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
            
            // Toggle pause when P is pressed
            if(event.key.keysym.sym == SDLK_p) {
                menu.TogglePause();
            }
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
        tempPlayer.SetDest(player.GetDX() - playerSpeed, player.GetDY());
        canMove = true;
        for (auto& tile : map) {
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run){
                player.SetImage("res/player_l.png", renderer);
                player.SetCurrAnim(run);
            } else {
                player.SetImage("res/player_l.png", renderer);
            }
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }

    if (r) {
        tempPlayer = player;
        tempPlayer.SetImage("res/player_r.png", renderer);
        tempPlayer.SetDest(player.GetDX() + playerSpeed, player.GetDY());
        canMove = true;
        for (auto& tile : map) {
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run){
                player.SetImage("res/player_r.png", renderer);
                player.SetCurrAnim(run);
            } else {
                player.SetImage("res/player_r.png", renderer);
            }
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }

    if (u) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX(), player.GetDY() - playerSpeed);
        canMove = true;
        for (auto& tile : map) {
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
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
        tempPlayer.SetDest(player.GetDX(), player.GetDY() + playerSpeed);
        canMove = true;
        for (auto& tile : map) {
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
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
    if (finalDest.x < 140) { player.SetDest(140, finalDest.y); Scroll(playerSpeed, 0); }
    if (finalDest.x > Width - 200) { player.SetDest(Width - 200, finalDest.y); Scroll(-playerSpeed, 0); }
    if (finalDest.y < 220) { player.SetDest(finalDest.x, 220); Scroll(0, playerSpeed); }
    if (finalDest.y > Height - 260) { player.SetDest(finalDest.x, Height - 260); Scroll(0, -playerSpeed); }

    player.UpdateAnimation();
    
    // Update enemies
    if (enemies && !enemies->empty()) {
        for (auto& enemy : *enemies) {
            // Calculate distance to player
            float dx = player.GetDX() - enemy.GetDX();
            float dy = player.GetDY() - enemy.GetDY();
            float distance = sqrt(dx*dx + dy*dy);
            
            // Update the attack cooldown
            enemy.UpdateCooldown();
            
            // If player is in range, attack
            if (enemy.IsInRange(player.GetDX(), player.GetDY())) {
                // Try to attack - the Attack method will check cooldown internally
                enemy.Attack(player, 10);
            } else {
                // Move towards player
                enemy.MoveTowards(player.GetDX(), player.GetDY());
            }
        }
    }
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
    
    // Scroll enemies too
    for (auto& enemy : *enemies) {
        enemy.SetDest(enemy.GetDX() + x, enemy.GetDY() + y);
    }
}

bool Game::Collision(Object a, Object b) {
    if((a.GetDX() < (b.GetDX() + b.GetDW())) && ((a.GetDX() + a.GetDW()) > b.GetDX()) && (a.GetDY() < (b.GetDY() + b.GetDH())) && ((a.GetDY() + a.GetDH()) > b.GetDY())) {
        return true;
    } else {
        return false;
    }
}