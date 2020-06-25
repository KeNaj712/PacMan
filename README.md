# Projekt_ProgramowanieObiektowe

Napisany w języku C++ (dokładniej C++ 14) z użyciem biblioteki SFML 2.5.1

Aby skompilować, najpierw trzeba zainstalować bibliotekę SFML komendą:
```
$ sudo apt-get install libsfml-dev
```
Następnie odpalamy grę komendami:
```
g++ -c *.cpp
g++ -o PacMan *.o -lsfml-graphics -lsfml-window -lsfml-system
./PacMan
```
