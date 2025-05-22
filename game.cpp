#include "game.h"

// Constructor
Game::Game() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Create SDL window and renderer
    if (SDL_CreateWindowAndRenderer(Width, Height, 0, &window, &renderer) != 0) {
        std::cerr << "Window and renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    // Set window title
    SDL_SetWindowTitle(window, "Game Window");
    SDL_ShowWindow(window);

    // Initialize font
    TTF_Init();
    font = TTF_OpenFont("res/sans.ttf", 12);

    // Load map from file (matrix of tiles)
    LoadMap("res/1.level");

    // Entities have predetermined speeds
    playerSpeed = 4;
    enemySpeed = 1.5f;
    bossSpeed = 2.0f;

    // Set player position and texture
    player.SetDest(Width/2-40, Height/2-48, 250/4, 249/4);
    player.SetImage("res/player_r.png", renderer);
    
    // Set up player animations
    idol = player.CreateCycle(1, 250, 249, 1, 20);
    run = player.CreateCycle(1, 250, 249, 4, 6);
    player.SetCurrAnim(idol);

    // Initialize enemies/bosses vectors
    enemies = new vector<Enemy>();
    bossEnemies = new vector<BossEnemy>();

    // Initialize enemies, spawn enemies when game starts
    InitEnemies();

    // Set gameKey position and texture
    gameKey.SetDest(610, 340, 1225/25, 980/25);
    gameKey.SetImage("res/key.png", renderer);
    gameKey.SetSrc(0, 0, 1225, 980);

    // Start the main loop
    Loop();
}

// Destructor
Game::~Game() {
    // Delete the enemies/bosses vector
    delete enemies;
    delete bossEnemies;
    
    // Clean up SDL and TTF
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

// Initialize enemies
void Game::InitEnemies() {
    // Clear existing enemies, if any
    enemies->clear();

    // Add enemies
    // Create enemy objects and set their properties
    Enemy enemy1;
    // Set enemy texture
    enemy1.SetImage("res/enemy.png", renderer);
    // Set enemy position and size
    enemy1.SetDest(Width/2+700, Height/2-100, 900/5, 381/5);
    enemy1.SetSrc(0, 0, 900, 381);
    // Add enemy to the vector
    enemies->push_back(enemy1);
    
    // Repeat for other enemies
    Enemy enemy2;
    enemy2.SetImage("res/enemy.png", renderer);
    enemy2.SetDest(Width/2+500, Height/2+8, 900/5, 381/5);
    enemy2.SetHealth(150);
    enemy2.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy2);

    Enemy enemy3;
    enemy3.SetImage("res/enemy.png", renderer);
    enemy3.SetDest(Width/2+600, Height/2+100, 900/5, 381/5);
    enemy3.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy3);

    Enemy enemy4;
    enemy4.SetImage("res/enemy.png", renderer);
    enemy4.SetDest(Width/2-700, Height/2-100, 900/5, 381/5);
    enemy4.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy4);

    Enemy enemy5;
    enemy5.SetImage("res/enemy.png", renderer);
    enemy5.SetDest(Width/2-600, Height/2+8, 900/5, 381/5);
    enemy5.SetHealth(150);
    enemy5.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy5);

    Enemy enemy6;
    enemy6.SetImage("res/enemy.png", renderer);
    enemy6.SetDest(Width/2-500, Height/2+108, 900/5, 381/5);
    enemy6.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy6);

    Enemy enemy7;
    enemy7.SetImage("res/enemy.png", renderer);
    enemy7.SetDest(Width/2, Height/2+400, 900/5, 381/5);
    enemy7.SetHealth(150);
    enemy7.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy7);

    Enemy enemy8;
    enemy8.SetImage("res/enemy.png", renderer);
    enemy8.SetDest(Width/2-100, Height/2+600, 900/5, 381/5);
    enemy8.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy8);

    Enemy enemy9;
    enemy9.SetImage("res/enemy.png", renderer);
    enemy9.SetDest(Width/2-200, Height/2+700, 900/5, 381/5);
    enemy9.SetSrc(0, 0, 900, 381);
    enemies->push_back(enemy9);
}

// Initialize boss
void Game::InitBoss() {
    // Clear existing bosses
    bossEnemies->clear();

    // Add new boss enemy
    // Create boss object and set its properties
    BossEnemy boss;
    // Set boss texture
    boss.SetImage("res/enemy.png", renderer);
    // Set boss position and size
    boss.SetDest(Width/2, Height/2-800, 900/3, 381/3);
    // Set boss health
    boss.SetHealth(500);
    boss.SetSrc(0, 0, 900, 381);
    // Add boss to the vector
    bossEnemies->push_back(boss);
    // Set boss spawn status
    bossSpawnedInGame = true;
}

// Main game loop
void Game::Loop() {
    static int lastTime = 0;
    // Check if the game is running
    while (menu.GetRunning()) {
        // Check input
        Input();
        // Only update game state if not paused
        if (!menu.GetPaused()) {
            // Update frame count and time
            lastFrame = SDL_GetTicks();
            if(lastFrame >= (lastTime + 1000)) {
                lastTime = lastFrame;
                frameCount = 0;
            }
            // Update game state
            Update();
        }
        // Render the game
        Render();
    }
}

// Render the game
void Game::Render() {
    // Render background
    SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = Width;
    rect.h = Height;
    // Fill the screen with the background color
    SDL_RenderFillRect(renderer, &rect);
    // Draw map and player
    DrawMap();
    Draw(player);
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
    // Draw health text with color
    Draw(healthText, 20, 80, r, g, b);
    // Display pause/unpause message
    char pauseText[50];
    snprintf(pauseText, sizeof(pauseText), "Press P to pause/unpause game");
    Draw(pauseText, 20, 110, 255, 255, 255);
    // Frame rate control
    frameCount++;
    // Calculate frame time
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS < (1000/60)) {
        SDL_Delay((1000/60) - timerFPS);
    }
    // Draw enemies and their health
    if (enemies && !enemies->empty()) {
        for (auto& enemy : *enemies) {
            // Draw the enemy
            Draw(enemy);
            // Create health text
            char healthText[20];
            snprintf(healthText, sizeof(healthText), "HP: %d", enemy.GetHealth());
            // Position text at the upper-right corner of the enemy
            Draw(healthText, enemy.GetDX() + enemy.GetDW() - 50, enemy.GetDY(), 255, 255, 255);
        }
    }
    // Draw bosses and their health
    if (bossEnemies && !bossEnemies->empty()) {
        for (auto& boss : *bossEnemies) {
            // Draw the boss
            Draw(boss);
            // Create health text
            char healthText[20];
            snprintf(healthText, sizeof(healthText), "HP: %d", boss.GetHealth());
            // Position text at the upper-right corner of the boss
            Draw(healthText, boss.GetDX() + boss.GetDW() - 50, boss.GetDY(), 255, 255, 255);
        }
    }
    // Draw the game key, when all enemies are dead and it hasn't been picked up already
    if (gameKey.AllEnemiesDead(*enemies) && !gameKey.GetPickedUp()) {
        Draw(gameKey);
        // Set spawn status to true if the key is spawned
        gameKey.SetSpawn(true);
    }
    // Check for collision between player and game key
    if (gameKey.GetSpawn() && Collision(player, gameKey)) {
        // Initialize boss if the key is picked up
        InitBoss(); 
        // Set the key as picked up and despawn the key
        // Reset spawn status
        gameKey.SetSpawn(false);
        gameKey.SetPickedUp(true);
        gameKey.Despawn();
    }
    SDL_RenderPresent(renderer);
}

// Draw method
void Game::Draw(Object o) {
    // Get the destination and source rectangles
    SDL_Rect dest = o.GetDest();
    SDL_Rect src = o.GetSrc();
    SDL_RenderCopyEx(renderer, o.GetTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

// Draw message method
void Game::Draw(const char *msg, int x, int y, int r, int g, int b) {
    // Create a surface, texture and color for the text
    SDL_Surface *surf;
    SDL_Texture *tex;
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
    // Render the text to a surface
    surf = TTF_RenderText_Solid(font, msg, color);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    // Set the destination rectangle for the text
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    // Render the text to the screen
    SDL_FreeSurface(surf);
    SDL_RenderCopy(renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

// Input method, checks keyboard presses
void Game::Input() {
    // Handle input events
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        // Close window
        if(event.type == SDL_QUIT) { menu.SetRunning(false); }
        if(event.type == SDL_KEYDOWN) {
            // ESC - close window
            if(event.key.keysym.sym == SDLK_ESCAPE) menu.SetRunning(false);
            // Normal movement keyw - W, A, S, D
            // Set flags for movement
            if(event.key.keysym.sym == SDLK_a) {l = 1; r = 0;}
            if(event.key.keysym.sym == SDLK_d) {r = 1; l = 0;}
            if(event.key.keysym.sym == SDLK_w) {u = 1; d = 0;}
            if(event.key.keysym.sym == SDLK_s) {d = 1; u = 0;}
            // Toggle pause when P is pressed
            if(event.key.keysym.sym == SDLK_p) { menu.TogglePause(); }
            // Player attack when SPACE is pressed, attack is invisible
            if(event.key.keysym.sym == SDLK_SPACE) {
                for (auto& enemy : *enemies) {
                    // Check if the player is in range of the enemy
                    if (player.EnemyIsInRange(enemy.GetDX(), enemy.GetDY())) {
                        // Deal damage to enemy, standard player attack is 10
                        player.AttackEnemy(enemy, 10);
                    }
                }
                for (auto& boss : *bossEnemies) {
                    // Check if the player is in range of the boss
                    if (player.EnemyIsInRange(boss.GetDX(), boss.GetDY())) {
                        // Deal damage to boss, standard player attack is 10
                        player.AttackEnemy(boss, 10);
                    }
                }
            }
        }
        if(event.type == SDL_KEYUP) {
            // Reset movement flags and animation when not moving
            if(event.key.keysym.sym == SDLK_a) {l = 0; player.SetCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_d) {r = 0; player.SetCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_w) {u = 0; player.SetCurrAnim(idol);}
            if(event.key.keysym.sym == SDLK_s) {d = 0; player.SetCurrAnim(idol);}
        }
    }
}

// Update method
void Game::Update() {
    // Create temporary player object to detect which tiles player can pass through
    Object tempPlayer;
    bool canMove;
    // Check movement permission for direction LEFT
    if (l) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX() - playerSpeed, player.GetDY());
        canMove = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : map) {
            // Check player and off-limit tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run){
                // File for player facing LEFT
                player.SetImage("res/player_l.png", renderer);
                // Set animation while moving
                player.SetCurrAnim(run);
            } else {
                player.SetImage("res/player_l.png", renderer);
            }
            // Set correct destination
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }
    // Check movement permission for direction RIGHt
    if (r) {
        tempPlayer = player;
        tempPlayer.SetImage("res/player_r.png", renderer);
        tempPlayer.SetDest(player.GetDX() + playerSpeed, player.GetDY());
        canMove = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : map) {
            // Check player and off_limits tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            if (player.GetCurrAnim() != run){
                // File for player facing RIGHT
                player.SetImage("res/player_r.png", renderer);
                // Set animation while moving
                player.SetCurrAnim(run);
            } else {
                player.SetImage("res/player_r.png", renderer);
            }
            // Set correct destination
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }
    // Check movement permission for direction UP
    if (u) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX(), player.GetDY() - playerSpeed);
        canMove = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : map) {
            // Check player and off-limit tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            // Set animation while moving
            if (player.GetCurrAnim() != run) player.SetCurrAnim(run);
            // Set correct destination
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }
    // Check movement permission for direction DOWN
    if (d) {
        tempPlayer = player;
        tempPlayer.SetDest(player.GetDX(), player.GetDY() + playerSpeed);
        canMove = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : map) {
            // Check player and off-limits tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(tempPlayer, tile)) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            // Set animation while moving
            if (player.GetCurrAnim() != run) player.SetCurrAnim(run);
            // Set correct destination
            player.SetDest(tempPlayer.GetDX(), tempPlayer.GetDY());
        }
    }
    // Check if player is out of bounds and scroll the map
    SDL_Rect finalDest = player.GetDest();
    if (finalDest.x < 140) { player.SetDest(140, finalDest.y); Scroll(playerSpeed, 0); }
    if (finalDest.x > Width - 200) { player.SetDest(Width - 200, finalDest.y); Scroll(-playerSpeed, 0); }
    if (finalDest.y < 220) { player.SetDest(finalDest.x, 220); Scroll(0, playerSpeed); }
    if (finalDest.y > Height - 260) { player.SetDest(finalDest.x, Height - 260); Scroll(0, -playerSpeed); }
    // Update player animation
    player.UpdateAnimation();
    // Update enemies, if there are any
    if (enemies && !enemies->empty()) {
        auto it = enemies->begin();
        while (it != enemies->end()) {
            // Calculate distance to player
            float dx = player.GetDX() - it->GetDX();
            float dy = player.GetDY() - it->GetDY();
            float distance = sqrt(dx*dx + dy*dy);
            // Update the attack cooldown
            it->UpdateCooldown();
            // If player is in range, attack
            if (it->IsInRange(player.GetDX(), player.GetDY())) {
                // Try to attack - the Attack method will check cooldown internally
                it->Attack(player, 10);
            } else {
                // Move towards player
                it->MoveTowards(player.GetDX(), player.GetDY(), enemySpeed);
            }
            // Check if enemy's health is equal or less than zero
            if (it->GetHealth() <= 0) {
                // Add score before removing the enemy
                player.AddScore(100);
                // Remove the enemy and update the iterator
                it = enemies->erase(it);
            } else {
                // Only increment the iterator if we didn't remove the current enemy
                ++it;
            }
        }
    }
    // Update boss enemies, if there are any
    if (bossEnemies && !bossEnemies->empty()) {
        auto it = bossEnemies->begin();
        while (it != bossEnemies->end()) {
            // Calculate distance to player
            float dx = player.GetDX() - it->GetDX();
            float dy = player.GetDY() - it->GetDY();
            float distance = sqrt(dx*dx + dy*dy);
            // Update the attack cooldown
            it->UpdateCooldown();
            // If player is in range, attack
            if (it->IsInRange(player.GetDX(), player.GetDY())) {
                // Try to attack - the Attack method will check cooldown internally
                it->Attack(player, 20);
            } else {
                // Move towards player
                it->MoveTowards(player.GetDX(), player.GetDY(), bossSpeed);
            }
            // Check if boss's health is zero or less
            if (it->GetHealth() <= 0) {
                // Add score before removing the boss
                player.AddScore(500);
                // Remove the boss and update the iterator
                it = bossEnemies->erase(it);
                // End game if boss is defeated, play specific audio
                it->EndGame(gameOver);
            } else {
                // Only increment the iterator if we didn't remove the current boss
                ++it;
            }
        }
    }
    // Check if player is dead
    if (!player.IsAlive()) {
        menu.SetRunning(false);
    }
}       

// Load map from file
// The map is a matrix of tiles, each tile has an ID
void Game::LoadMap(const char *filename) {
    // Create a temporary object to load the map
    Object temp;
    // Set image for tile colors
    temp.SetImage("res/colors_25px.png", renderer);
    int current, mw, mh;
    ifstream in(filename);
    // Check if the file opened successfully
    if(!in.is_open()) {
        cout << "Failed to open map file" << endl;
        return;
    }
    // Clear existing map
    map.clear();
    // Read map dimensions and offset
    in >> mw;
    in >> mh;
    in >> mapX;
    in >> mapY;
    // Read tile data
    for(int i = 0; i < mh; i++) {
        for(int j = 0; j < mw; j++) {
            if(in.eof()) {
                cout << "Reached end of map file too soon" << endl;
                return;
            }
            in >> current;
            if(current != 0) {
                // Set tiles to corresponding location
                temp.SetSolid(true);
                temp.SetSrc((current-1)*Tile_size, 0, Tile_size, Tile_size);
                temp.SetDest(j * Tile_size + mapX, i * Tile_size + mapY, Tile_size, Tile_size);
                // Set tile ID
                temp.SetID(current);
                if(current == 3) temp.SetSolid(false);
                // Add tile to the map
                map.push_back(temp);
            }
        }
    }
    // Close the file
    in.close();
}

// Draw the map
// The map is a vector of tiles, each tile has a destination and source rectangle
void Game::DrawMap() {
    for (int i = 0; i < map.size(); i++) {
        int dx = map[i].GetDX();
        int dy = map[i].GetDY();
        // Check if the tile is visible on the screen
        bool visible = dx + Tile_size >= 0 &&
                       dy + Tile_size >= 0 &&
                       dx < Width &&
                       dy < Height;
        // Draw tile only if it is within the screen bounds
        if (visible) {
            Draw(map[i]);
        }
    }
}

// Scroll the map by a given x and y offset
void Game::Scroll(int x, int y) {
    for (int i = 0; i < map.size(); i++) {
        map[i].SetDest(map[i].GetDX() + x, map[i].GetDY() + y);
    }
    // Scroll enemies
    for (auto& enemy : *enemies) {
        enemy.SetDest(enemy.GetDX() + x, enemy.GetDY() + y);
    }
    // Scroll bosses
    for (auto& boss : *bossEnemies) {
        boss.SetDest(boss.GetDX() + x, boss.GetDY() + y);
    }   
    // Scroll gameKey
    gameKey.SetDest(gameKey.GetDX() + x, gameKey.GetDY() + y);
}

// Check for collision between two objects
// Returns true if the objects are colliding, false otherwise
bool Game::Collision(Object a, Object b) {
    if((a.GetDX() < (b.GetDX() + b.GetDW())) && ((a.GetDX() + a.GetDW()) > b.GetDX()) && (a.GetDY() < (b.GetDY() + b.GetDH())) && ((a.GetDY() + a.GetDH()) > b.GetDY())) {
        return true;
    } else {
        return false;
    }
}