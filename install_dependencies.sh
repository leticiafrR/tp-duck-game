#!/bin/bash

# This script installs all the dependencies needed for the project

# Update the repositories
sudo apt-get update -y

# Install the dependencies for C++
sudo apt-get install -y build-essential g++ cmake

# Install SDL2 and the necessary libraries (SDL2_image, SDL2_ttf, SDL2_mixer)
sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Install libyaml
sudo apt-get install -y libyaml-dev

# Install libyaml
sudo apt-get install -y libyaml-dev

# Check if all packages were installed successfully
dpkg -s libsdl2-dev libsdl2-image-dev libyaml-dev

