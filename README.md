# 7542_TpFinal

## Manual de instalacion 

Los programas fueron ejecutados utilizando los compiladores gcc-9/g++-9 y gcc-11/g++-11

Listamos las dependencias necesarias para poder correr los programas
- sudo apt-get install build-essential
- sudo apt-get install qt5-default
- sudo apt-get install clang-8
- sudo apt-get install libyaml-cpp-dev
- sudo apt-get install qtmultimedia5-dev
- sudo apt-get install libsdl2-dev
- sudo apt-get install libsdl2-image-dev
- sudo apt-get install libsdl2-gfx-dev
- sudo apt-get install libsdl2-mixer-dev

Ademas, necesitamos tener instalado Makefile y CMAKE para buildear y hacer el deploy
- sudo apt-get install make
- sudo apt-get install cmake 

Para cmake, se utiliza la version 3.10

Una vez clonado el repositorio e instalado las dependencias, debemos crear la carpeta build desde la raiz:
``` 
mkdir build 
cd build
cmake ..
make 
``` 
