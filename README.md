# Emulador NES sencillo

Este proyecto contiene un emulador b\u00e1sico de la consola Nintendo Entertainment System escrito en C++.

## Compilaci\u00f3n

Se utiliza CMake y la biblioteca SDL2.

En distribuciones Linux:

```bash
sudo apt-get install libsdl2-dev cmake g++
mkdir build && cd build
cmake ..
make
```

En Windows con MinGW se puede usar `mingw32-make` y una instalaci\u00f3n de SDL2.

El programa se ejecuta pasando la ruta a una ROM en formato `.nes`:

```bash
./nes juego.nes
```

