#!/bin/bash

# Este script desinstala todas las dependencias instaladas para el proyecto

echo "Desinstalando las dependencias..."

# Desinstalar los paquetes de C++
sudo apt-get remove --purge -y build-essential g++ cmake

# Desinstalar SDL2 y las bibliotecas necesarias (SDL2_image, SDL2_ttf, SDL2_mixer)
sudo apt-get remove --purge -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Desinstalar libyaml
sudo apt-get remove --purge -y libyaml-dev

# Limpiar los paquetes no necesarios
sudo apt-get autoremove -y

# Eliminar los archivos de configuración restantes
sudo apt-get clean

# Verificar si se desinstalaron correctamente
echo "Paquetes desinstalados:"
dpkg -l | grep -E 'libsdl2-dev|libsdl2-image-dev|libsdl2-ttf-dev|libsdl2-mixer-dev|libyaml-dev|build-essential|g++|cmake'

echo "Desinstalación completada."
