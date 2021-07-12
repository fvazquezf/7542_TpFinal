![Alt Text](readme_img/intro.gif)
 
# 7542_TpFinal
 
**Trabajo Practico Final**
 
**7542 Taller de Programación I**
 
**Facultad de Ingeniería de la Universidad de Buenos Aires (FIUBA)**
 
 
| Integrantes                            | Padrón |
| -------------------------------------- | ------ |
| Cai, Ana Maria                         | 102150 |
| Giampieri Mutti, Leonardo              | 102358 |
| Vazquez Fernandez, Francisco Manuel    | 104128 |
 
**Tabla de contenidos**
 
- [7542_TpFinal](#7542_tpfinal)
  - [Introducción](#introducción)
  - [Manual de instalación](#manual-de-instalación)
    - [Instalación](#instalación)
    - [Desinstalación](#desinstalación)
    - [Ejecución](#ejecución)
  - [Manual de usuario](#manual-de-usuario)
    - [Ciclo del juego](#ciclo-del-juego)
    - [Comandos](#comandos)
    - [Armas](#armas)
    - [Mapa](#mapa)
    - [Editor de mapas](#editor-de-mapas)
      - [Creación de mapas](#creación-de-mapas)
      - [Edición de mapas](#edición-de-mapas)
      - [Insertar y mover elementos en el mapa mapa](#insertar-y-mover-elementos-en-el-mapa-mapa)
    - [Configuración](#configuración)
 
## Introducción
 
 
 
## Manual de instalación
 
### Instalación
 
Para instalar las dependencias del juego se debe correr el siguiente comando en la consola:
 
```console
sh installer.sh
```
 
### Desinstalación
 
Para instalar las dependencias del juego se debe correr el siguiente comando en la consola:
 
```console
sh desinstaller.sh <flags>
```
 
Flags soportados y su comportamiento:
 
- `--qt`:  borra las dependencias de qt
- `--sdl`:  borra las dependencias de sdl2
- `--yaml`:  borra las dependencias de yaml-cpp
- `--cpp`:  borra las dependencias: clang, cmake, make y build-essential
- `--repo`:  elimina el repositorio
- `--all`:  borra las dependencias de qt, sdl2, yaml-cpp, clang, cmake, make y build-essentials, y elimina el repositorio
 
### Ejecución
 
## Manual de usuario
 
### Ciclo del juego
 
### Comandos
 
### Armas
 
### Mapa
 
### Editor de mapas
 
El juego provee un "Editor de mapas" que consiste en un programa que permite a los jugadores crear y editar mapas que luego va a poder jugar.
 
Este programa se ejecuta con el siguiente comando:
 
```console
./edito_main
```
 
Luego, aparece una pantalla donde se van a visualizar los mapas ya creados.
 
#### Creación de mapas
 
Si se desea crear un mapa de cero se debe clickear en el botón "Create".
 
El usuario debe introducir el nombre del mapa y el tamaño de este.
 
![Alt Text](readme_img/editor_create.gif)
 
Una vez completado este paso, se debe clickear el botón "Continue" para poder colocar elementos en el mapa.
 
![Alt Text](readme_img/editor_empty_map.gif)
 
Cuando se quiera guardar los cambios se debe clickear en el botón "Save".
 
#### Edición de mapas
 
Si se desea editar algún mapa ya existente se debe clickear el nombre de tal mapa en la lista y luego clickear el botón "Edit".
 
![Alt Text](readme_img/editor_edit.gif)
 
Cuando se quiera guardar los cambios se debe clickear en el botón "Save".
 
#### Insertar y mover elementos en el mapa mapa
 
El mapa provee una lista de cuatro tipos de elementos en el mapa:
 
- background: fondo del mapa (uno por mapa)
- weapons: armas del mapa
- walls: paredes o zonas donde el jugador no puede pasar
- zones:
 - zoneA: zona donde empieza un equipo el juego
 - zoneB: zona donde empieza el otro equipo el juego
 - zoneBomb: zona donde se quiere colocar las bombas
 
![Alt Text](readme_img/editor_elements.gif)
 
Para poder insertar tales elementos en el mapa se debe primero clickear en el nombre de la categoría para desplegar sus opciones.
Luego, se debe primero clickear el elemento que desea insertar y segundo clickear las posiciones en el mapa donde se quiere colocar tal elemento.
 
Para poder mover elementos en el mapa se debe clickear al elemento que se quiere mover y soltar el cursor en la posición nueva del mapa.
 
![Alt Text](readme_img/editor_insert.gif)
 
### Configuración
 
 