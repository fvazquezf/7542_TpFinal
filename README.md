# 7542_TpFinal

| Integrantes                            | Padron |
| -------------------------------------- | ------ |
| Cai, Ana Maria                         | 102150 |
| Giampieri Mutti, Leonardo              | 102358 |
| Vazquez Fernandez, Francisco Manuel    | 104128 |

## Tabla de contenidos

- [7542_TpFinal](#7542_tpfinal)
  - [Tabla de contenidos](#tabla-de-contenidos)
  - [Introduccion](#introduccion)
  - [Manual de instalacion](#manual-de-instalacion)
    - [Instalacion](#instalacion)
    - [Desinstalacion](#desinstalacion)
  - [Manual de ususario](#manual-de-ususario)

## Introduccion


## Manual de instalacion

### Instalacion

Para instalar las dependencias del juego se debe correr el siguiente comando en la consola:

```console
sh installer.sh
```

### Desinstalacion

Para instalar las dependencias del juego se debe correr el siguiente comando en la consola:

```console
sh desinstaller.sh <flags>
```

Las flags que pueden haber y combinar son:

- `--qt`:  borra las dependencias de qt
- `--sdl`:  borra las dependencias de sdl2
- `--yaml`:  borra las dependencias de yaml-cpp
- `--cpp`:  borra las dependencias: clang, cmake, make y build-essential
- `--repo`:  elimina el repositorio
- `--all`:  borra las dependencias de qt, sdl2, yaml-cpp, clang, cmake, make y build-essentia, y elimina el repositorio

## Manual de ususario