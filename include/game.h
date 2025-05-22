#pragma once

// Include necessary libraries and headers
#include "object.h"
#include "audio.h"
#include "entity.h"
#include "player.h"
#include "menu.h"
#include "enemy.h"
#include "key.h"
#include "boss_enemy.h"
#include "libs/SDL2/include/SDL.h"
#include "libs/SDL2/include/SDL_image.h"
#include "libs/SDL2/include/SDL_ttf.h"
#include "libs/SDL2/include/SDL_mixer.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace OOP_Game {
    // Define constants for the game
    static constexpr int width = 1280;
    static constexpr int height = 720;
    static constexpr int tile_size = 25;

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
        SDL_Renderer *m_renderer;
        SDL_Window *m_window;
        TTF_Font *m_font;

        // Game objects
        int m_frame_count, m_last_frame;

        // Player attributes
        Player m_player;
        int m_player_speed;
        bool m_l=0, m_r=0, m_u=0, m_d=0;
        int m_idle, m_run;

        // Map attributes
        vector<Object> m_map;
        int m_map_x, m_map_y;

        // Menu attributes
        Menu m_menu;

        // Enemy/boss attributes
        std::vector<Enemy>* m_enemies;
        std::vector<BossEnemy>* m_boss_enemies;
        void InitEnemies();
        void InitBoss();
        float m_enemy_speed;
        float m_boss_speed;
        bool m_boss_spawned_in_game = false;

        // Game key attributes
        Key m_game_key;

        // Audio attributes
        Audio m_game_over;
    };
}