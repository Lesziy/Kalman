# Kalman

Implementacja filtru Kalmana do śledzenia celów i fuzji danych.

## Wymagania

- Python 2.7
 - SCons domyślnie leci architekturą procesora(a że się z nim zgadzam to nie interweniuję), więc pod Windowsem należy uważać na wersję (x86/x64)
- SCons
- Boost 1.59
 - ~~Ostrzeżenie: Ze względu na fakt, że Boost.Python wydaje się być niekompatybilny podczas standardowej kompilacji, na chwilę obecną cały projekt jest linkowany statycznie, tzn. aby skompilować za pomocą Scons należy zawczasu skompilować Boosta w sposób sugerowany niżej.~~ Aktualizacja 17.11: bez boost.log dziala normalna kompilacja. 

 
  
## Kompilacja

Pod Windowsem powinny działać pliki projektu VS2015(w projekcie są dodane ścieżki aby uwzględnić domyślne instalacje powyższych programów), pod linuxem wystarczy tylko:
```
$ scons
```
w głównym folderze.

Inne opcje kompilacji:
```
$ scons test          # do kompilacji testow
$ scons all           # do kompilacji programu + testow
$ scons -c [target]   # kasowanie plikow zrodlowych.
```

### Boost
~~
address-model to {32,64}, a -j ustala liczbę wątków - samo polecenie do uruchomienia w głównym katalogu biblioteki Boost.
 ```
 b2 --with-python --with-log -j4 link=static threading=multi variant=release runtime-link=static address-model=64 
 ``` 
~~
## Testy
Na chwile obecna kazdy moduł ma oddzielna aplikacje z testami, ponieważ tak jest _zdecydowanie_ prościej.


## TODO
- [ ] Uwzględnienie wszystkich wymagań z readme w SConscript
