# Kalman

Implementacja filtru Kalmana do �ledzenia cel�w i fuzji danych.

## Wymagania

- Python 2.7
- SCons
- Boost 1.57+

## Kompilacja

Pod Windowsem powinny dzia�a� pliki projektu VS2015(w projekcie s� dodane �cie�ki aby uwzgl�dni� domy�lne instalacje powy�szych program�w), pod linuxem wystarczy tylko:
```
$ scons
```
w g��wnym folderze.

Inne opcje kompilacji:
```
$ scons test          # do kompilacji testow
$ scons all           # do kompilacji programu + testow
$ scons -c [target]   # kasowanie plikow zrodlowych.
```

## Testy
Na chwile obecna kazdy modul ma oddzielna aplikacje do testowania, poniewaz tak jest _zdecydowanie_ prosciej.
