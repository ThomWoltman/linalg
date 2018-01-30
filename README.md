# Framework voor KMint (CLion optimized)

Deze repository bevat een klein opstartproject voor KMINT. Het maakt gebruik van CMake als build system. Dit project is aangepast om correct te builden met CLion. 

# Gebruik

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

## Draaien
Als je bovenstaande commando's hebt utigevoerd om het project te compileren kun je het programma als volgt starten:

```
$ ./KMintFramework
```

# Het bestand `graph.txt`

`graph.txt` bevat een beschrijving van een graaf. Het bestand bestaat uit twee delen gescheiden door een witregel.

Het eerste deel beschrijft de locatie van de knopen van de graaf. Elke regel bevat een x- en een y-coordinaat. Het gehele veld heeft een afmeting van 1280 bij 720 pixels. Houd hier rekening mee! De knoop op regel 1, krijgt automatisch index 0; de knoop op regel 2 index 1 enzovoorts.

Het tweede deel bevat de zijden van de graaf. Elke regel bestaat uit drie velden gescheiden door spaties. De eerste twee velden staan respectievelijk voor de bron- en doelknoop. Het derde veld bevat een gewicht. Je zou bijvoorbeeld een zwaarder gewicht kunnen toekennen aan een verbinding door een moeras.

# Auteur

Dit project is geschreven door Jeroen de Haas voor gebruik in de module KMINT binnen de opleiding Informatica aan Avans Hogeschool.
Aanpassingen voor gebruik in Clion door Dajo Hofman (student aan genoemde onderwijsinstelling).