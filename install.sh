#!/bin/bash

# This script installs all the dependencies needed for the project

# Update the repositories
sudo apt-get update -y

# Install the dependencies for C++
sudo apt-get install -y build-essential g++ cmake libjpeg-dev libpng-dev \
libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev \
libwavpack-dev libmodplug-dev libsdl2-dev libyaml-dev

# Move to the external directory where all dependencies are located
cd external

# Install SDL_mixer
cd SDL_mixer
mkdir -p build
cd build
cmake ..
make
sudo make install
cd ../..

# Install SDL_ttf
cd SDL_ttf
mkdir -p build
cd build
cmake ..
make
sudo make install
cd ../..

# Install libsdl2pp
cd SDL2pp
mkdir -p build
cd build
cmake ..
make
sudo make install
cd ../..

# Go back to the root directory
cd ..

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
