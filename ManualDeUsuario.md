# 7542_TpFinal

## Counter-Strike 2d

### Grupo 5

Para ver como instalar el juego, leer el manual de instalación.

#### Controles

- Movimiento direccional con W A S D
- Recarga de armas con R
- Plant/defuse de la bomba con ESPACIO
- Cambio de armas con 1, 2, 3, 4:
  - 1 = arma principal ( Awp, Ak47, shotgun)
  - 2 = arma secundaria (pistola)\
  - 3 = cuchillo
  - 4 = bomba (solo para Terroristas)
- PickUp de arma con E
- Atacar con el click izquierdo del mouse

#### Configuración

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

#### Ejecución

Los ejecutables se generan en la carpeta build.
Se generan 3 ejecutables:

- ./esqueleto_server
- ./client_main
- ./editor_main
El único que necesita mas parámetros para ejecutarse es el server. Este requiere el puerto y la dirección del archivo de configuración (../config.yaml).
Una ves que se levanta el servidor, se pueden correr clientes. Estos se levantan con el comando indicado. Esto abre una ventana donde se debe introducir el puerto y el ip. Luego se puede elegir entre crear o unirse a una partida.
Si se elije crear una partida, indicar el mapa a utilizar y el nombre de la misma. Después de esto se debe esperar a que se complete la partida de jugadores.
Si se elige unirse a una partida. Selecciona la partida a la que se desea unir. La partida comenzara cuando la misma este completa
