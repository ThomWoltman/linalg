# Lineaire Algebra


## Afhankelijkheden

Dit project vereist een C++14 compiler (recente versies van `g++` en `clang++` voldoen), cmake 3.8 of hoger en SDL2 en SDL_image versie 2 of hoger. Deze afhankelijkheden kun je je installeren met je favoriete package manager. Als je vanuit Clion build en runt hoef je geen cmake te installeren gezien deze gebundeld komt met de installatie.

## Commandline compilatie

Onderstaande commando's laten zien hoe je de code compileert via de commandline. We gaan er vanuit dat je start vanuit de projectmap waar je dit framework hebt neergezet.

```
$ mkdir ./build && cd ./build
$ cmake ..
$ make -j3
```

Je kunt de `3` vervangen door het aantal processorkernen in je systeem + 1. Voor een quad-core systeem zou je dus `-j5` gebruiken in plaats van `-j3`