# Kalman
Implementacja filtru Kalmana do śledzenia celów i fuzji danych.

## Wymagania
### Windows
#### Konieczne
- Python 2.7
 - SCons domyślnie leci architekturą procesora(a że się z nim zgadzam to nie interweniuję), więc pod Windowsem należy uważać na wersję (tylko x64)
- SCons
- Boost
  - **Ostrzeżenie.** Na dzień 27.12.2015 prekompilowane binaria 1.60 pod Windowsem nie umożliwiają kompilacji. 1.59 działa bez zarzutu.
- SDL 2.0.3
- VS2015 pod Windowsem
- wxWidgets 3.0.2
- Doxygen

#### Niewymagane, aczkolwiek przydatne
- [pywin32](http://sourceforge.net/projects/pywin32/) wycisza ostrzeżenia dotyczące dorzucania flagi `j`(liczby jednoczesnych kompilacji)
- Aby uruchomić pliki z folderu _maps_ bez kompilacji całego projektu za pomocą skryptu driver.py należy zainstalować matplotlib, tj.
```
$ pip2 install matplotlib
```
 - Skrypt wymaga dodatkowej biblioteki, `wxPython2.8`.


### Linux
Pod Ubuntu wymagane są następujące biblioteki:

 - wxgtk
 - libboost-dev
 - libsdl2
 - doxygen
 - python2.7
 - scons

Na innych platformach analogicznie.
## Kompilacja

```
Dostępne cele kompilacji:
    scons           - domyślny, sama aplikacja.
    scons docs      - wrapper na doxygena(jednoznaczny z uruchomieniem polecenia doxygen w głównym folderze).
    scons test      - buduje testy.
    scons examples  - buduje wszystkie przykłady.
    scons all       - uruchamia wszystko powyżej.

Dostępne flagi:
    coverage=1  	- Pod Linuxem dołączane są flagi umożliwiające liczenie pokrycia kodu.
    debug=1         - flaga /D pod Windowsem bądź -g pod Linuxem.
```
Dostępne są również przełączniki umożliwiające liczenie pokrycia kodu i kompilację opartą na bibliotekach do debugowania - tutaj odsyłam do pomocy.

Warto korzystać z `j` aby przyśpieszyć kompilację, tj.
```
  scons -j[liczba równoległych kompilacji]
```
***Ostrzeżenie.*** W trakcie testów wychodzi, że `-j4` potrafi zużywać nawet 2GB pamięci!
## Użycie

Odsyłam do aplikacji,
```
build/app --help
```

## Testy
Na chwile obecna kazdy moduł ma oddzielną aplikację z testami, ponieważ tak jest _zdecydowanie_ prościej.

## FAQ
- Czy ostrzeżenia podczas kompilacji są groźne?
 - Nie, ze względu na http://stackoverflow.com/questions/30412951/unresolved-external-symbol-imp-fprintf-and-imp-iob-func-sdl2 wymagane jest takie brudne obejście aby pozwolić na linkowanie. Fakt że wxWidgets wyszło ostatni raz ponad rok temu(gdy VS2015 był w powijakach) również negatywnie wpłwa na liczbę błędów.
- Udało się skompilować, krzyczy o brak dlli. Co robić?
 - Skrypt after_install.bat dorzuca do zmiennej systemowej %PATH% foldery w ktorych przewidziana jest lokalizacja bibliotek i dlli, wiec wystarczy go uruchomić.
- Co zrobić w przypadku błędu `ImportError: No module named site` pod Windowsem?
 - Pomaga postąpienie według [tych wskazówek](http://stackoverflow.com/questions/5599872/python-windows-importerror-no-module-named-site).

## Kompilacja pod Windowsem:
0. Instalacja VS2015
1. Ściągnięcie i instalacja, przy kilku zastrzeżeniach:
 - [Prekomiplowanego Boosta](http://sourceforge.net/projects/boost/files/boost-binaries/1.59.0/boost_1_59_0-msvc-14.0-64.exe/download)
  - wxWidgets 3
   - Najlepszym rozwiązaniem jest rozwiazanie binarne zawierajace same zrodla, tj.
    - Poprawki w zródłach: https://forums.wxwidgets.org/viewtopic.php?t=40491#p163676
    - Kompilacja wx_vc12.sln, Release x64.
2. Uruchomienie `scons all` w głównym katalogu.
 - Ze względu na _dojrzałość_ wxWidgets i brak aktualizacji biblioteki od ponad roku podczas kompilacji występują ostrzeżenia, które można zlikwidować większą liczbą poprawek w kodzie(por. link do forum wxWidgets).
