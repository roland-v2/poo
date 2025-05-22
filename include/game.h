#pragma once

// Include necessary libraries and headers
#include "object.h"
#include "audio.h"
#include "entity.h"
#include "player.h"
#include "menu.h"
#include "enemy.h"
#include "key.h"
#include "bossEnemy.h"
#include "libs/SDL2/include/SDL.h"
#include "libs/SDL2/include/SDL_image.h"
#include "libs/SDL2/include/SDL_ttf.h"
#include "libs/SDL2/include/SDL_mixer.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace OOPGame {
    // Define constants for the game
    static constexpr int Width = 1280;
    static constexpr int Height = 720;
    static constexpr int Tile_size = 25;

    class Game {
    public:
        // Constructor and destructor
        Game();
        ~Game();

        // Game loop, rendering and input methods
        void Loop();
        void Update();
        void Input();
        void Render();

        // Drawing methods
        void Draw(Object o);
        void Draw(const char *msg, int x, int y, int r, int g, int b);

        // Map loading and drawing methods
        void LoadMap(const char *filename);
        void DrawMap();

        // Scrolling and collision detection methods
        void Scroll(int x, int y);
        bool Collision(Object a, Object b);
    private:
        // Game attributes
        // SDL attributes
        SDL_Renderer *renderer;
        SDL_Window *window;
        TTF_Font *font;
        
        // Game objects
        int frameCount, lastFrame;

        // Player attributes
        Player player;
        int playerSpeed;
        bool l=0, r=0, u=0, d=0;
        int idol, run;

        // Map attributes
        vector<Object> map;
        int mapX, mapY;

        // Menu attributes
        Menu menu;

        // Enemy/boss attributes
        std::vector<Enemy>* enemies;
        std::vector<BossEnemy>* bossEnemies;
        void InitEnemies();
        void InitBoss();
        float enemySpeed;
        float bossSpeed;
        bool bossSpawnedInGame = false;

        // Game key attributes
        Key gameKey;

        // Audio attributes
        Audio gameOver;
    };
}