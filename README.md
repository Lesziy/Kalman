# Kalman

Implementacja filtru Kalmana do śledzenia celów i fuzji danych.

## Wymagania

- Python 2.7
- SCons
- Boost 1.57+

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

## Testy
Na chwile obecna kazdy moduł ma oddzielna aplikacje z testami, ponieważ tak jest _zdecydowanie_ prościej.
