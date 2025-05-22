#!/bin/bash

# Script to build and run the Game

# --- Configuration ---
EXECUTABLE_NAME="game"
CXX="g++" # Compiler
CXX_FLAGS="-std=c++17 -Wall"

# Project structure and paths from your working command
SRC_FILES_PATTERN="src/*.cpp" # Source files pattern
PROJECT_INCLUDE_PATH="." # For -I.
SDL_INCLUDE_PATH="./libs/SDL2/include" # For -I./libs/SDL2/include
SDL_LIB_DIR="./libs/SDL2/lib" # Base directory for SDL .dylib files

# SDL Libraries to link directly (paths relative to project root)
SDL_DYLIBS=(
    "${SDL_LIB_DIR}/libSDL2.dylib"
    "${SDL_LIB_DIR}/libSDL2_image.dylib"
    "${SDL_LIB_DIR}/libSDL2_ttf.dylib"
    "${SDL_LIB_DIR}/libSDL2_mixer.dylib"
)

# Linker flag for runtime path
RPATH_FLAG="-Wl,-rpath,${SDL_LIB_DIR}"

# --- Build ---
echo "Building ${EXECUTABLE_NAME}..."

${CXX} ${CXX_FLAGS} \
    ${SRC_FILES_PATTERN} \
    -o ${EXECUTABLE_NAME} \
    -I${PROJECT_INCLUDE_PATH} \
    -I${SDL_INCLUDE_PATH} \
    "${SDL_DYLIBS[@]}" \
    ${RPATH_FLAG}

# Check if build was successful
BUILD_SUCCESS_CODE=$?
if [ ${BUILD_SUCCESS_CODE} -eq 0 ]; then
    echo "Build successful."
    echo "Running ${EXECUTABLE_NAME}..."
    
    # --- Run ---
    ./${EXECUTABLE_NAME}
else
    echo "Build failed with error code ${BUILD_SUCCESS_CODE}."
    exit 1
fi

exit 0