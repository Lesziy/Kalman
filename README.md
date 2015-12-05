# Kalman

Implementacja filtru Kalmana do śledzenia celów i fuzji danych.

## Wymagania

- Python 2.7
 - SCons domyślnie leci architekturą procesora(a że się z nim zgadzam to nie interweniuję), więc pod Windowsem należy uważać na wersję (tylko x64)
- SCons
- Boost 
 - boost.python wymaga specjalnej uwagi, por. dalej.
- SDL 2.0.3
 - Pod windowsem po cichu zakładam lokalizację C:\Program Files (x86)\SDL.
- Plik Sconscript opiera się na 64bitowej architekturze.
- VS2015 pod Windowsem



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
Do klasycznej instalacji(np. sugerowanej w biowebie) należy dodać dynamiczne biblioteki w następujący sposob(komendy do uruchomienia w folderze boosta):
 ```
 bjam --with-python link=shared address-model=64 stage
 bjam --with-python link=shared address-model=64 install
 ```

## Testy
Na chwile obecna kazdy moduł ma oddzielna aplikacje z testami, ponieważ tak jest _zdecydowanie_ prościej.

## FAQ
- Czy ostrzeżenie podczas kompilacji jest grozne?
 - Nie, ze wzgledu na http://stackoverflow.com/questions/30412951/unresolved-external-symbol-imp-fprintf-and-imp-iob-func-sdl2 wymagane jest takie brudne obejscie aby pozwolic na linkowanie.
- Udalo sie skompilowac, krzyczy o brak dlli. Co robic?
 - Skrypt after_install.bat dorzuca do zmiennej systemowej %PATH% foldery w ktorych przewidziana jest lokalizacja bibliotek i dlli, wiec wystarczy go uruchomic.

## Kompilacja pod Windowsem:
0. Instalacja VS2015
1. Sciagniecie i instalacja:
 - http://sourceforge.net/projects/boost/files/boost-binaries/1.59.0/boost_1_59_0-msvc-14.0-64.exe/download
 - Python 2.7 & scons
 - A do katalogow sugerowanych w pliku SConscript:
  - SDL 2
  - wxWidgets 3
   - Najlepszym rozwiazaniem jest rozwiazanie binarne zawierajace same zrodla, tj.
    - Poprawki w zrodlach: https://forums.wxwidgets.org/viewtopic.php?t=40491#p163676
    - Kompilacja wx_vc12.sln, Release x64.
2. Uruchomienie `scons all` w glownym katalogu.
 - Ze wzgledu na _dojrzalosc_ wxWidgets i brak aktualizacji biblioteki od ponad roku jest troche niegroznych ostrzezen.
