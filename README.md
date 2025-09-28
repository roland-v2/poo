#poo
Object Oriented Programming


POO Game Project

A C++ game project built with SDL2 libraries, featuring object-oriented programming principles and a complete game engine with player mechanics, enemies, boss fights, and audio integration.


Overview

This is a 2D game developed in C++ using SDL2 libraries as part of an Object-Oriented Programming (POO) course. The game features a complete game engine with graphics rendering, audio management, collision detection, and entity management systems.


Features

Complete Game Engine: Built from scratch using SDL2. Player System: Health, lives, damage, and movement mechanics. Enemy AI: Regular enemies with attack patterns and boss enemies. Audio System: Sound effects and background music support. Map System: Dynamic map loading and rendering. Object Management: Comprehensive sprite and texture handling. Menu System: Game menus and user interface. Collision Detection: Physics-based collision system

Prerequisites

Operating System: macOS (with Apple Silicon or Intel) or Windows (10 or newer). Compiler: g++ or clang++ with C++17 suppor. SDL2 Libraries: Included locally in the project

Architecture

Core Classes

Entity: Base class for all game objects with health and position. Player: Handles player mechanics, lives, damage, and input. Enemy: AI-controlled enemies with attack patterns. BossEnemy: Special enemies with enhanced abilities. Object: Manages sprites, textures, and rendering. Game: Main game loop, rendering, and state management. Audio: Sound effects and music management

Game Flow

Initialization: SDL2 systems, window, renderer setup.  Game Loop: Input processing, Game state updates, Collision detection, Rendering.  Cleanup: Resource deallocation and SDL2 shutdown.
