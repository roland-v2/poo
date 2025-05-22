#include "include/game.h"
using namespace OOP_Game;

// Constructor
Game::Game() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Create SDL window and renderer
    if (SDL_CreateWindowAndRenderer(width, height, 0, &m_window, &m_renderer) != 0) {
        std::cerr << "Window and renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    // Set window title
    SDL_SetWindowTitle(m_window, "Game Window");
    SDL_ShowWindow(m_window);
    // Initialize font
    TTF_Init();
    m_font = TTF_OpenFont("res/sans.ttf", 12);

    // Load map from file (matrix of tiles)
    LoadMap("res/1.level");

    // Entities have predetermined speeds
    m_player_speed = 4;
    m_enemy_speed = 1.5f;
    m_boss_speed = 2.0f;

    // Set player position and texture
    m_player.SetDest(width/2-40, height/2-48, 250/4, 249/4);
    m_player.SetImage("res/player_r.png", m_renderer);

    // Set up player animations
    m_idle = m_player.CreateCycle(1, 250, 249, 1, 20);
    m_run = m_player.CreateCycle(1, 250, 249, 4, 6);
    m_player.SetCurrAnim(m_idle);

    // Initialize enemies/bosses vectors
    m_enemies = new vector<Enemy>();
    m_boss_enemies = new vector<BossEnemy>();

    // Initialize enemies, spawn enemies when game starts
    InitEnemies();

    // Set gameKey position and texture
    m_game_key.SetDest(610, 340, 1225/25, 980/25);
    m_game_key.SetImage("res/key.png", m_renderer);
    m_game_key.SetSrc(0, 0, 1225, 980);

    // Load audio file for game over sound
    m_game_over.Load("res/game_over.wav");

    // Start the main loop
    Loop();
}

// Destructor
Game::~Game() {
    // Delete the enemies/bosses vector
    delete m_enemies;
    delete m_boss_enemies;
    
    // Clean up SDL and TTF
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

// Initialize enemies
void Game::InitEnemies() {
    // Clear existing enemies, if any
    m_enemies->clear();

    // Add enemies
    // Create enemy objects and set their properties
    Enemy enemy1;
    // Set enemy texture
    enemy1.SetImage("res/enemy.png", m_renderer);
    // Set enemy position and size
    enemy1.SetDest(width/2+700, height/2-100, 900/5, 381/5);
    enemy1.SetSrc(0, 0, 900, 381);
    // Add enemy to the vector
    m_enemies->push_back(enemy1);

    // Repeat for other enemies
    Enemy enemy2;
    enemy2.SetImage("res/enemy.png", m_renderer);
    enemy2.SetDest(width/2+500, height/2+8, 900/5, 381/5);
    enemy2.SetHealth(150);
    enemy2.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy2);

    Enemy enemy3;
    enemy3.SetImage("res/enemy.png", m_renderer);
    enemy3.SetDest(width/2+600, height/2+100, 900/5, 381/5);
    enemy3.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy3);

    Enemy enemy4;
    enemy4.SetImage("res/enemy.png", m_renderer);
    enemy4.SetDest(width/2-700, height/2-100, 900/5, 381/5);
    enemy4.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy4);

    Enemy enemy5;
    enemy5.SetImage("res/enemy.png", m_renderer);
    enemy5.SetDest(width/2-600, height/2+8, 900/5, 381/5);
    enemy5.SetHealth(150);
    enemy5.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy5);

    Enemy enemy6;
    enemy6.SetImage("res/enemy.png", m_renderer);
    enemy6.SetDest(width/2-500, height/2+108, 900/5, 381/5);
    enemy6.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy6);

    Enemy enemy7;
    enemy7.SetImage("res/enemy.png", m_renderer);
    enemy7.SetDest(width/2, height/2+400, 900/5, 381/5);
    enemy7.SetHealth(150);
    enemy7.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy7);

    Enemy enemy8;
    enemy8.SetImage("res/enemy.png", m_renderer);
    enemy8.SetDest(width/2-100, height/2+600, 900/5, 381/5);
    enemy8.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy8);

    Enemy enemy9;
    enemy9.SetImage("res/enemy.png", m_renderer);
    enemy9.SetDest(width/2-200, height/2+700, 900/5, 381/5);
    enemy9.SetSrc(0, 0, 900, 381);
    m_enemies->push_back(enemy9);
}

// Initialize boss
void Game::InitBoss() {
    // Clear existing bosses
    m_boss_enemies->clear();

    // Add new boss enemy
    // Create boss object and set its properties
    BossEnemy boss;
    // Set boss texture
    boss.SetImage("res/enemy.png", m_renderer);
    // Set boss position and size
    boss.SetDest(width/2, height/2-800, 900/3, 381/3);
    // Set boss health
    boss.SetHealth(500);
    boss.SetSrc(0, 0, 900, 381);
    // Add boss to the vector
    m_boss_enemies->push_back(boss);
    // Set boss spawn status
    m_boss_spawned_in_game = true;
}

// Main game loop
void Game::Loop() {
    static int last_time = 0;
    // Check if the game is running
    while (m_menu.GetRunning()) {
        // Check input
        Input();
        // Only update game state if not paused
        if (!m_menu.GetPaused()) {
            // Update frame count and time
            m_last_frame = SDL_GetTicks();
            if(m_last_frame >= (last_time + 1000)) {
                last_time = m_last_frame;
                m_frame_count = 0;
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
    SDL_SetRenderDrawColor(m_renderer, 34, 34, 34, 255);
    static SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = width;
    rect.h = height;
    // Fill the screen with the background color
    SDL_RenderFillRect(m_renderer, &rect);
    // Draw map and player
    DrawMap();
    Draw(m_player);
    // Display player stats in the top-left corner
    static char score_text[50];
    snprintf(score_text, sizeof(score_text), "Score: %d", m_player.GetScore());
    Draw(score_text, 20, 20, 255, 255, 255);
    static char lives_text[50];
    snprintf(lives_text, sizeof(lives_text), "Lives: %d", m_player.GetLives());
    Draw(lives_text, 20, 50, 255, 255, 255);
    static char health_text[50];
    snprintf(health_text, sizeof(health_text), "Health: %d/%d", m_player.GetHealth(), m_player.GetMaxHealth());
    // Determine health text color based on health percentage
    int health_percentage = (m_player.GetHealth() * 100) / m_player.GetMaxHealth();
    int r, g, b;
    if (health_percentage > 70) {
        // Green for high health
        r = 0; g = 255; b = 0;
    } else if (health_percentage > 30) {
        // Yellow for medium health
        r = 255; g = 255; b = 0;
    } else {
        // Red for low health
        r = 255; g = 0; b = 0;
    }
    // Draw health text with color
    Draw(health_text, 20, 80, r, g, b);
    // Display pause/unpause message
    static char pause_text[50];
    snprintf(pause_text, sizeof(pause_text), "Press P to pause/unpause game");
    Draw(pause_text, 20, 110, 255, 255, 255);
    // Frame rate control
    m_frame_count++;
    // Calculate frame time
    int timer_FPS = SDL_GetTicks() - m_last_frame;
    if(timer_FPS < (1000/60)) {
        SDL_Delay((1000/60) - timer_FPS);
    }
    // Draw enemies and their health
    if (m_enemies && !m_enemies->empty()) {
        for (auto& enemy : *m_enemies) {
            // Draw the enemy
            Draw(enemy);
            // Create health text
            char health_text[20];
            snprintf(health_text, sizeof(health_text), "HP: %d", enemy.GetHealth());
            // Position text at the upper-right corner of the enemy
            Draw(health_text, enemy.GetDX() + enemy.GetDW() - 50, enemy.GetDY(), 255, 255, 255);
        }
    }
    // Draw bosses and their health
    if (m_boss_enemies && !m_boss_enemies->empty()) {
        for (auto& boss : *m_boss_enemies) {
            // Draw the boss
            Draw(boss);
            // Create health text
            char health_text[20];
            snprintf(health_text, sizeof(health_text), "HP: %d", boss.GetHealth());
            // Position text at the upper-right corner of the boss
            Draw(health_text, boss.GetDX() + boss.GetDW() - 50, boss.GetDY(), 255, 255, 255);
        }
    }
    // Draw the game key, when all enemies are dead and it hasn't been picked up already
    if (m_game_key.AllEnemiesDead(*m_enemies) && !m_game_key.GetPickedUp()) {
        Draw(m_game_key);
        // Set spawn status to true if the key is spawned
        m_game_key.SetSpawn(true);
    }
    // Check for collision between player and game key
    if (m_game_key.GetSpawn() && Collision(m_player, m_game_key)) {
        // Initialize boss if the key is picked up
        InitBoss(); 
        // Set the key as picked up and despawn the key
        // Reset spawn status
        m_game_key.SetSpawn(false);
        m_game_key.SetPickedUp(true);
        m_game_key.Despawn();
    }
    SDL_RenderPresent(m_renderer);
}

// Draw method
void Game::Draw(Object o) {
    // Get the destination and source rectangles
    SDL_Rect dest = o.GetDest();
    SDL_Rect src = o.GetSrc();
    SDL_RenderCopyEx(m_renderer, o.GetTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
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
    surf = TTF_RenderText_Solid(m_font, msg, color);
    tex = SDL_CreateTextureFromSurface(m_renderer, surf);
    // Set the destination rectangle for the text
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    // Render the text to the screen
    SDL_FreeSurface(surf);
    SDL_RenderCopy(m_renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

// Input method, checks keyboard presses
void Game::Input() {
    // Handle input events
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        // Close window
        if(event.type == SDL_QUIT) { m_menu.SetRunning(false); }
        if(event.type == SDL_KEYDOWN) {
            // ESC - close window
            if(event.key.keysym.sym == SDLK_ESCAPE) m_menu.SetRunning(false);
            // Normal movement keys - W, A, S, D
            // Set flags for movement
            if(event.key.keysym.sym == SDLK_a) { m_l = 1; m_r = 0; }
            if(event.key.keysym.sym == SDLK_d) { m_r = 1; m_l = 0; }
            if(event.key.keysym.sym == SDLK_w) { m_u = 1; m_d = 0; }
            if(event.key.keysym.sym == SDLK_s) { m_d = 1; m_u = 0; }
            // Toggle pause when P is pressed
            if(event.key.keysym.sym == SDLK_p) { m_menu.TogglePause(); }
            // Player status - << overloading
            if(event.key.keysym.sym == SDLK_i) { std::cout << m_player; }
            // Combined enemy health - "+" overloading
            if(event.key.keysym.sym == SDLK_j && m_enemies && m_enemies->size() >= 2) {
                // Get the first two enemies
                const Enemy& first_enemy = (*m_enemies)[0];
                const Enemy& second_enemy = (*m_enemies)[1];
                int combined_health = first_enemy + second_enemy;
                std::cout << "Enemy1 Health (" << first_enemy.GetHealth() << ") + Enemy2 Health (" << second_enemy.GetHealth() << ") = Combined Health: " << combined_health << std::endl;
            }
            // Player attack when SPACE is pressed, attack is invisible
            if(event.key.keysym.sym == SDLK_SPACE) {
                for (auto& enemy : *m_enemies) {
                    // Check if the player is in range of the enemy
                    if (m_player.EnemyIsInRange(enemy.GetDX(), enemy.GetDY())) {
                        // Deal damage to enemy, standard player attack is 10
                        m_player.AttackEnemy(enemy, 10);
                    }
                }
                for (auto& boss : *m_boss_enemies) {
                    // Check if the player is in range of the boss
                    if (m_player.EnemyIsInRange(boss.GetDX(), boss.GetDY())) {
                        // Deal damage to boss, standard player attack is 10
                        m_player.AttackBossEnemy(boss);
                    }
                }
            }
        }
        if(event.type == SDL_KEYUP) {
            // Reset movement flags and animation when not moving
            if(event.key.keysym.sym == SDLK_a) { m_l = 0; m_player.SetCurrAnim(m_idle); }
            if(event.key.keysym.sym == SDLK_d) { m_r = 0; m_player.SetCurrAnim(m_idle); }
            if(event.key.keysym.sym == SDLK_w) { m_u = 0; m_player.SetCurrAnim(m_idle); }
            if(event.key.keysym.sym == SDLK_s) { m_d = 0; m_player.SetCurrAnim(m_idle); }
        }
    }
}

// Update method
void Game::Update() {
    // Create temporary player object to detect which tiles player can pass through
    Object temp_player;
    bool can_move;
    // Check movement permission for direction LEFT
    if (m_l) {
        temp_player = m_player;
        temp_player.SetDest(m_player.GetDX() - m_player_speed, m_player.GetDY());
        can_move = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : m_map) {
            // Check player and off-limit tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(temp_player, tile)) {
                can_move = false;
                break;
            }
        }
        if (can_move) {
            if (m_player.GetCurrAnim() != m_run) {
                // File for player facing LEFT
                m_player.SetImage("res/player_l.png", m_renderer);
                // Set animation while moving
                m_player.SetCurrAnim(m_run);
            } else {
                m_player.SetImage("res/player_l.png", m_renderer);
            }
            // Set correct destination
            m_player.SetDest(temp_player.GetDX(), temp_player.GetDY());
        }
    }
    // Check movement permission for direction RIGHT
    if (m_r) {
        temp_player = m_player;
        temp_player.SetImage("res/player_r.png", m_renderer);
        temp_player.SetDest(m_player.GetDX() + m_player_speed, m_player.GetDY());
        can_move = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : m_map) {
            // Check player and off_limits tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(temp_player, tile)) {
                can_move = false;
                break;
            }
        }
        if (can_move) {
            if (m_player.GetCurrAnim() != m_run) {
                // File for player facing RIGHT
                m_player.SetImage("res/player_r.png", m_renderer);
                // Set animation while moving
                m_player.SetCurrAnim(m_run);
            } else {
                m_player.SetImage("res/player_r.png", m_renderer);
            }
            // Set correct destination
            m_player.SetDest(temp_player.GetDX(), temp_player.GetDY());
        }
    }
    // Check movement permission for direction UP
    if (m_u) {
        temp_player = m_player;
        temp_player.SetDest(m_player.GetDX(), m_player.GetDY() - m_player_speed);
        can_move = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : m_map) {
            // Check player and off-limit tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(temp_player, tile)) {
                can_move = false;
                break;
            }
        }
        if (can_move) {
            // Set animation while moving
            if (m_player.GetCurrAnim() != m_run) m_player.SetCurrAnim(m_run);
            // Set correct destination
            m_player.SetDest(temp_player.GetDX(), temp_player.GetDY());
        }
    }
    // Check movement permission for direction DOWN
    if (m_d) {
        temp_player = m_player;
        temp_player.SetDest(m_player.GetDX(), m_player.GetDY() + m_player_speed);
        can_move = true;
        // Player can't move through tiles with ID 3 or 0
        for (auto& tile : m_map) {
            // Check player and off-limits tiles collision
            if ((tile.GetID() == 3 or tile.GetID() == 0) && Collision(temp_player, tile)) {
                can_move = false;
                break;
            }
        }
        if (can_move) {
            // Set animation while moving
            if (m_player.GetCurrAnim() != m_run) m_player.SetCurrAnim(m_run);
            // Set correct destination
            m_player.SetDest(temp_player.GetDX(), temp_player.GetDY());
        }
    }
    // Check if player is out of bounds and scroll the map
    SDL_Rect finalDest = m_player.GetDest();
    if (finalDest.x < 140) { m_player.SetDest(140, finalDest.y); Scroll(m_player_speed, 0); }
    if (finalDest.x > width - 200) { m_player.SetDest(width - 200, finalDest.y); Scroll(-m_player_speed, 0); }
    if (finalDest.y < 220) { m_player.SetDest(finalDest.x, 220); Scroll(0, m_player_speed); }
    if (finalDest.y > height - 260) { m_player.SetDest(finalDest.x, height - 260); Scroll(0, -m_player_speed); }
    // Update player animation
    m_player.UpdateAnimation();
    // Update enemies, if there are any
    if (m_enemies && !m_enemies->empty()) {
        auto it = m_enemies->begin();
        while (it != m_enemies->end()) {
            // Update the attack cooldown
            it->UpdateCooldown();
            // If player is in range, attack
            if (it->IsInRange(m_player.GetDX(), m_player.GetDY())) {
                // Try to attack - the Attack method will check cooldown internally
                it->Attack(m_player, 10);
            } else {
                // Move towards player
                it->MoveTowards(m_player.GetDX(), m_player.GetDY(), m_enemy_speed);
            }
            // Check if enemy's health is equal or less than zero
            if (it->GetHealth() <= 0) {
                // Add score before removing the enemy
                m_player.AddScore(100);
                // Remove the enemy and update the iterator
                it = m_enemies->erase(it);
            } else {
                // Only increment the iterator if we didn't remove the current enemy
                ++it;
            }
        }
    }
    // Update boss enemies, if there are any
    if (m_boss_enemies && !m_boss_enemies->empty()) {
        auto it = m_boss_enemies->begin();
        while (it != m_boss_enemies->end()) {
            // Update the attack cooldown
            it->UpdateCooldown();
            // If player is in range, attack
            if (it->IsInRange(m_player.GetDX(), m_player.GetDY())) {
                // Try to attack - the Attack method will check cooldown internally
                it->Attack(m_player, 20);
            } else {
                // Move towards player
                it->MoveTowards(m_player.GetDX(), m_player.GetDY(), m_boss_speed);
            }
            // Check if boss's health is zero or less
            if (it->GetHealth() <= 0) {
                // Add score before removing the boss
                m_player.AddScore(500);
                // Remove the boss and update the iterator
                it = m_boss_enemies->erase(it);
                // End game if boss is defeated, play specific audio
                it->EndGame(m_game_over);
            } else {
                // Only increment the iterator if we didn't remove the current boss
                ++it;
            }
        }
    }
    // Check if player is dead
    if (!m_player.IsAlive()) {
        m_menu.SetRunning(false);
    }
}       

// Load map from file
// The map is a matrix of tiles, each tile has an ID
void Game::LoadMap(const char *filename) {
    // Create a temporary object to load the map
    Object temp;
    // Set image for tile colors
    temp.SetImage("res/colors_25px.png", m_renderer);
    int current, mw, mh;
    ifstream in(filename);
    // Check if the file opened successfully
    if(!in.is_open()) {
        cout << "Failed to open map file" << endl;
        return;
    }
    // Clear existing map
    m_map.clear();
    // Read map dimensions and offset
    in >> mw;
    in >> mh;
    in >> m_map_x;
    in >> m_map_y;
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
                temp.SetSrc((current-1)*tile_size, 0, tile_size, tile_size);
                temp.SetDest(j * tile_size + m_map_x, i * tile_size + m_map_y, tile_size, tile_size);
                // Set tile ID
                temp.SetID(current);
                if(current == 3) temp.SetSolid(false);
                // Add tile to the map
                m_map.push_back(temp);
            }
        }
    }
    // Close the file
    in.close();
}

// Draw the map
// The map is a vector of tiles, each tile has a destination and source rectangle
void Game::DrawMap() {
    for (int i = 0; i < m_map.size(); i++) {
        int dx = m_map[i].GetDX();
        int dy = m_map[i].GetDY();
        // Check if the tile is visible on the screen
        bool visible = dx + tile_size >= 0 &&
                       dy + tile_size >= 0 &&
                       dx < width &&
                       dy < height;
        // Draw tile only if it is within the screen bounds
        if (visible) {
            Draw(m_map[i]);
        }
    }
}

// Scroll the map by a given x and y offset
void Game::Scroll(int x, int y) {
    for (int i = 0; i < m_map.size(); i++) {
        m_map[i].SetDest(m_map[i].GetDX() + x, m_map[i].GetDY() + y);
    }
    // Scroll enemies
    for (auto& enemy : *m_enemies) {
        enemy.SetDest(enemy.GetDX() + x, enemy.GetDY() + y);
    }
    // Scroll bosses
    for (auto& boss : *m_boss_enemies) {
        boss.SetDest(boss.GetDX() + x, boss.GetDY() + y);
    }   
    // Scroll gameKey
    m_game_key.SetDest(m_game_key.GetDX() + x, m_game_key.GetDY() + y);
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