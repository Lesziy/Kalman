# Kalman

Implementacja filtru Kalmana do śledzenia celów i fuzji danych.

## Wymagania

- Python 2.7
 - SCons domyślnie leci architekturą procesora(a że się z nim zgadzam to nie interweniuję), więc pod Windowsem należy uważać na wersję (tylko x64)
- SCons
- Boost
 - boost.python wymaga specjalnej uwagi, por. dalej.
 - Uwaga: Aktualne, skompilowane biblioteki pod Windowsa nie współgrają z projektem - prawdopodobnie jakiś błąd w boost::log.
- SDL 2.0.3
- Plik Sconscript opiera się na 64bitowej architekturze.
- VS2015 pod Windowsem
- wxWidgets 3.0.2
- Doxygen

### Dodatkowe
Aby uruchomić pliki z folderu _maps_ bez kompilacji całego projektu należy zainstalować matplotlib, tj.
```
$ pip2 install matplotlib
```
Do tego należy zainstalować pakiet wxpython2.8, zgodnie z dystrybucją:
- Linux:
  - Pod Archem należy zainstlować paczkę `wxpython2.8`.

## Kompilacja

Pod Windows powinny działać pliki projektu VS2015(w projekcie są dodane ścieżki aby uwzględnić domyślne instalacje powyższych programów), pod linuxem wystarczy tylko:
```
$ scons
```
w głównym folderze.

Inne opcje kompilacji:
```
$ scons test          # do kompilacji testow
$ scons docs          # do kompilacji samej dokumentacji
$ scons all           # do kompilacji programu + testow
$ scons -c [target]   # kasowanie plikow zrodlowych.
```
Dostępne są również przełączniki umożliwiające liczenie pokrycia kodu i kompilację opartą na bibliotekach do debugowania - tutaj odsyłam do pomocy.
## Użycie

Program zawiera wbudowaną pomoc, dostępną pod:
```
$ app -h
```

## Testy
Na chwilę obecną każdy moduł ma oddzielną aplikację z testami, ponieważ tak jest _zdecydowanie_ prościej.

## FAQ
- Czy ostrzeżenie podczas kompilacji jest grozne?
 - Nie, ze wzgledu na http://stackoverflow.com/questions/30412951/unresolved-external-symbol-imp-fprintf-and-imp-iob-func-sdl2 wymagane jest takie brudne obejscie aby pozwolic na linkowanie.
- Udalo sie skompilowac, krzyczy o brak dlli. Co robic?
 - Skrypt after_install.bat dorzuca do zmiennej systemowej %PATH% foldery w ktorych przewidziana jest lokalizacja bibliotek i dlli, wiec wystarczy go uruchomic.

## Kompilacja pod Windowsem:
0. Instalacja VS2015
1. Ściągnięcie i instalacja:
 - http://sourceforge.net/projects/boost/files/boost-binaries/1.59.0/boost_1_59_0-msvc-14.0-64.exe/download
 - Python 2.7 & scons
 - A do katalogów sugerowanych w pliku SConscript:
  - SDL 2
  - wxWidgets 3
   - Najlepszym rozwiązaniem jest rozwiazanie binarne zawierajace same zrodla, tj.
    - Poprawki w zródłach: https://forums.wxwidgets.org/viewtopic.php?t=40491#p163676
    - Kompilacja wx_vc12.sln, Release x64.
2. Uruchomienie `scons all` w głównym katalogu.
 - Ze względu na _dojrzałość_ wxWidgets i brak aktualizacji biblioteki od ponad roku podczas kompilacji występują ostrzeżenia, które można zlikwidować większą liczbą poprawek w kodzie(por. link do forum wxWidgets).
