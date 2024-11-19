#!/bin/bash

# A helper function to add color to a string message
print_colored_message() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

# List of available colors
RED="31";GREEN="32";GREEN_BOLD="1;32";YELLOW="33";YELLOW_BOLD="1;33";

# This script installs all the dependencies needed for the project

# Update the repositories
sudo apt-get update -y

sudo apt-get update
        sudo apt-get install -y \
          build-essential \
          g++ \
          cmake \
          libsdl2-dev \
          libsdl2-image-dev \
          libsdl2-ttf-dev \
          libsdl2-mixer-dev \
          libyaml-dev \
          libjpeg-dev \
          libpng-dev \
          libfreetype-dev
          
print_colored_message() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

# List of available colors
RED="31";GREEN="32";GREEN_BOLD="1;32";YELLOW="33";YELLOW_BOLD="1;33";

print_colored_message $YELLOW_BOLD "══ Adding CMake files for SDL2 packages in /usr/lib/x86_64-linux-gnu/cmake/ ══"

SCRIPT_DIR="$(dirname "$0")"
#sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_image" ]; then
    sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_image
    print_colored_message $YELLOW_BOLD "══ Created SDL2_image folder ══"
fi

# Check if the CMake file exists, if not, copy it
if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_image/sdl2_image-config.cmake" ]; then
    sudo cp "$SCRIPT_DIR"/files/sdl2_image-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_image/sdl2_image-config.cmake
    print_colored_message $YELLOW_BOLD "══ Copied sdl2_image-config.cmake ══"
fi

# Check if the folder exists, if not, create it
if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer" ]; then
    sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer
    print_colored_message $YELLOW_BOLD "══ Created SDL2_mixer folder ══"
fi

# Check if the CMake file exists, if not, copy it
if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer/sdl2_mixer-config.cmake" ]; then
    sudo cp "$SCRIPT_DIR"/files/sdl2_mixer-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer/sdl2_mixer-config.cmake
    print_colored_message $YELLOW_BOLD "══ Copied sdl2_mixer-config.cmake ══"
fi

# Check if the folder exists, if not, create it
if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf" ]; then
    sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf
    print_colored_message $YELLOW_BOLD "══ Created SDL2_ttf folder ══"
fi

# Check if the CMake file exists, if not, copy it
if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf/sdl2_ttf-config.cmake" ]; then
    sudo cp "$SCRIPT_DIR"/files/sdl2_ttf-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf/sdl2_ttf-config.cmake
    print_colored_message $YELLOW_BOLD "══ Copied sdl2_ttf-config.cmake ══"
fi

# Check if the required packages were installed
echo "Checking installed packages..."
dpkg -s libsdl2-dev libyaml-dev

# Clean previous builds (only if a Makefile exists)
if [ -f "Makefile" ]; then
    make clean
else
    echo "No Makefile found. Skipping clean step."
fi
# Build the project
make
