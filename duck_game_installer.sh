#!/bin/bash
print_colored_message() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

# List of available colors
RED="31";GREEN="32";GREEN_BOLD="1;32";YELLOW="33";YELLOW_BOLD="1;33";

set -e 
# Verificar si el script se ejecuta como root
if [[ $EUID -ne 0 ]]; then
   echo "Este script debe ejecutarse como root. Usa 'sudo'." >&2
   exit 1
fi

print_colored_message $GREEN "[DUCK GAME INSTALLER] Installing dependencies..."
chmod +x scripts/install_dependencies.sh
./scripts/install_dependencies.sh

# 2. Crear directorio para los assets y copiarlos
print_colored_message $GREEN "\n[DUCK GAME INSTALLER] Moving assets and multimedia to /var/duckGame_g6..."
if [ -d "/var/duckGame_g6" ]; then
    rm -rf /var/duckGame_g6/*
else
    mkdir -p /var/duckGame_g6
fi
sudo cp -r assets /var/duckGame_g6
sudo cp -r multimedia /var/duckGame_g6

# 3. Crear directorio para configuraciones y copiarlas
print_colored_message $GREEN "\n[DUCK GAME INSTALLER] Moving configuration files to /etc/duckGame_g6 ..."
if [ -d "/etc/duckGame_g6" ]; then
    rm -rf /etc/duckGame_g6/*
else
    mkdir -p /etc/duckGame_g6
fi
sudo cp -r config/* /etc/duckGame_g6
sudo chmod -R o+w /etc/duckGame_g6

# 4. Compilar el proyecto
print_colored_message $GREEN "\n[DUCK GAME INSTALLER] Building the game ..."
make

# 5. Copiar binarios a /usr/bin
print_colored_message $GREEN "\n[DUCK GAME INSTALLER] Copying binary files to /usr/bin..."
if [ -f "/usr/bin/taller_server" ]; then
    rm -f /usr/bin/taller_server
fi
sudo cp build/taller_server /usr/bin/

if [ -f "/usr/bin/taller_client" ]; then
    rm -f /usr/bin/taller_client
fi
sudo cp build/taller_client /usr/bin/

if [ -f "/usr/bin/taller_editor" ]; then
    rm -f /usr/bin/taller_editor
fi
sudo cp build/taller_editor /usr/bin/

print_colored_message $GREEN_BOLD "\n[DUCK GAME INSTALLER] Installation completed successfully."
