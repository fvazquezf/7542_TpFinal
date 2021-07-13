<p align="center">
  <img src="readme_img/intro.gif" alt="animated" />
</p>

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
    - [Controles](#controles)
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
git clone https://github.com/fvazquezf/7542_TpFinal
cd 7542_TpFinal
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

Luego de la "Instalacion", se generan tres ejecutables: `esqueleto_server`, `client_main` y `editor_main`.

Para acceder a ellos se debe ingresar a la carpeta build dentro de la carpeta "7542_TpFinal". Para ello, se debe escribir en la consola:

```console
cd build
```
El primer ejecutable, es el servidor del juego. Este requiere como parametro el puerto donde se realizara la conexión y la dirección del archivo de configuración cuya ruta es "../config.yaml". Para ello, se debe escribir en la consola:

```console
./esqueleto_server <puerto> ../config.yaml
``` 

El segundo ejecutable, es el cliente/ Este requiere del archivo de configuracion del cliente cuya ruta es "../client_config.yaml". Para ello, se debe escribir en la consola:

```console
./client_main ../client_config.yaml
``` 
Finalemente, el ultimo ejecutable es el editor de mapas del juego. Para ello, se debe escribir en la consola:

```console
./editor_main 
``` 

## Manual de usuario
 
### Ciclo del juego

Una ves que se levanta el servidor, se pueden correr clientes. Estos se levantan con el comando indicado. Esto abre una ventana donde se debe introducir el puerto y el ip. Luego se puede elegir entre crear o unirse a una partida.
Si se elije crear una partida, indicar el mapa a utilizar y el nombre de la misma. Después de esto se debe esperar a que se complete la partida de jugadores.
Si se elige unirse a una partida. Selecciona la partida a la que se desea unir. La partida comenzara cuando la misma este completa

### Controles

- Movimiento direccional con `W` `A` `S` `D`
- Recarga de armas con `R`
- Plant/defuse de la bomba con `ESPACIO`
- Cambio de armas con 1, 2, 3, 4:
  - `1` = arma principal ( Awp, Ak47, shotgun)
  - `2` = arma secundaria (pistola)\
  - `3` = cuchillo
  - `4` = bomba (solo para Terroristas)
- PickUp de arma con `E`
- Atacar con el click izquierdo del mouse

### Armas
 
### Mapa
 
### Editor de mapas
 
El juego provee un "Editor de mapas" que consiste en un programa que permite a los jugadores crear y editar mapas que luego va a poder jugar.
 
Este programa se ejecuta con el siguiente comando:
 
```console
./editor_main
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

Cada mapa debe tener una de las tres zonas mencionadas y estas zonas deben ser rectangulares.
Para configurar aquello, se debe indicar con cuatro marcas en el mapa tal que se forme un rectangulo. Si se pone una maraca de mas, se pone un elemento sobre esa marca o se ponen cuatro marcas que no forman un rectangulo, toda la zona se elimina automaticamnete.
 
### Configuración
 
Para configurar los parámetros de juego debe acceder al archivo config.yaml.
Actualmente, se puede modificar la vida de los jugadores, el dinero inicial y la cantidad de jugadores por partida. Ademas de los parámetros de las armas. Las distancias de los mismos están configurados en centímetros, y los tiempos en tics del mundo (actualmente 60 por segundo)
Parámetros de las armas:

- ammo: munición en el cartucho. cantidad de balas que se pueden disparar antes de recargar.
- range: rango de disparo. Distancia máxima que registra un golpe.
- pistol/shotgun/bomb_accuracy: Angulo/2 que registra el golpe. El area de acierto se determina por una sección de circunferencia, la accuracy de estas armas determinan que tan amplio es este circulo. Los valores van de 0 (nunca pega) a 180 (todo el circulo, pega hasta atrás del jugador).
- rifle/awp/pistol_accuracy: distancia de la trayectoria al centro del jugador enemigo. Mientras mas grande este numero, mas probable es que le pegue al jugador enemigo. Valor mínimo: 0.
- damage: daño que inflige el arma al acertar.
- firerate: Tiempo entre un golpe y el próximo. Las armas que no tienen esta variable golpean siempre que se hace click.
- bomb_fuse: tiempo que tarda la bomba en explotar
- bomb_activate_time: tiempo que tarda la bomba en plantarse/defusearse.
