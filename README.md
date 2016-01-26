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
- VS2015 pod Windowsem
- Doxygen

#### Niewymagane, aczkolwiek przydatne
- [pywin32](http://sourceforge.net/projects/pywin32/) wycisza ostrzeżenia dotyczące dorzucania flagi `j`(liczby jednoczesnych kompilacji)
- Skrypty `runme`, w wersji zależnej od systemu operacyjnego, zamieszczone w katalogu build/ bądź matlabScripts/ wymagają do działania programu Octave.

### Linux
Pod Ubuntu wymagane są następujące biblioteki:

 - libboost-dev
 - doxygen
 - python2.7
 - scons
 - octave
 - gnuplot
Na innych platformach analogicznie.
## Kompilacja

```
Dostępne cele kompilacji:
    scons               - domyślny, sama aplikacja.
    scons docs          - wrapper na doxygena(jednoznaczny z uruchomieniem polecenia doxygen w głównym folderze).
    scons test          - buduje testy.
    scons examples      - buduje wszystkie przykłady.
    scons all           - uruchamia wszystko powyżej. UWAGA: Nie zalicza się do tego poniższy cel!

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

### Kompilacja pod Windowsem:
0. Instalacja VS2015
1. Ściągnięcie i instalacja, przy kilku zastrzeżeniach:
 - [Prekomiplowanego Boosta](http://sourceforge.net/projects/boost/files/boost-binaries/1.59.0/boost_1_59_0-msvc-14.0-64.exe/download)
2. Uruchomienie `scons all` w głównym katalogu.
3. Jeżeli chcemy mieć możliwość zwizualizowania wyników należy uruchomić również polecenie `scons matlabScripts`


## Użycie
Odsyłam do aplikacji,
```
build/app --help
```

### runme - jak z tego korzystać?
***Uwaga.*** Ze względu na problemy z kopiowaniem plików w automatyczny sposób należy samodzielnie skopiować plik runme zgodny z platformą i script.m z folderu `matlabScripts` do folderu `build` po kompilacji.

Przykład użycia pod Windowsem to:
```
(projekt/build) $ runme.bat ..\maps\standard_acc.py script(1000)
```
Przykład użycia pod Linuxem(po skopiowaniu script.m i runme.sh do katalogu build):
```
(projekt/build) $ ./runme.sh ../maps/robo_acc.py "script(1000)"
```
## Testy
Na chwilę obecną każdy moduł ma oddzielną aplikację z testami, ponieważ tak jest _zdecydowanie_ prościej.

## FAQ
- Co zrobić w przypadku błędu `ImportError: No module named site` pod Windowsem?
 - Pomaga postąpienie według [tych wskazówek](http://stackoverflow.com/questions/5599872/python-windows-importerror-no-module-named-site).
