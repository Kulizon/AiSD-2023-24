# Uruchomienie
Przed uruchomieniem programu należy użyć poniższej komendy, aby zainstalować bibliotekę SDL2.
```console
sudo apt-get install libsdl2-dev
```
Aby skompilować i uruchomić program należy użyc komendy:
```console
make
```

Aby uruchomić skompilowany program należy użyc komendy:
```console
make run
```


# Labirynt

Program służy do generacji losowych labiryntów o określonych wymiarach oraz wyświetlania wygenerowanego labiryntu użytkownikowi. Wykorzystuje algorytm DFS (Depth-First Search) do generowania labiryntu.

## Działanie

Zastosowany algorytm to algorytm DFS ("recursive backtracking"). Jego przebieg działania jest następujący:
1. Inicjalizowany jest pusty labirynt (macierz komórek, które nie są ze sobą połączone).
2. Wybierany jest losowy punkt startowy generacji.
3. Rekurencyjnie eksplorujemy sąsiednie komórki bieżącej komórki. Podczas tej eksploracji tworzone są przejścia (usuwane są ściany), łącząc bieżącą komórkę z jej sąsiadami. Kolejność, w jakiej sąsiedzi są eksplorowani, jest losowa.
4. Jeśli bieżąca komórka nie ma sąsiadów do odwiedzenia, algorytm wraca do poprzednich komórek na stosie, aż znajdzie komórkę z nieodwiedzonymi sąsiadami ("backtracking").
5. Powtarzamy kroki 3-4, aż wszystkie komórki zostaną odwiedzone, a cały labirynt zostanie wygenerowany.
6. W każdym kroku rysujemy przebieg algorytmu i aktualny labirytn, zamieniamy przy tym macierz z informacjami o połączeniach między komórkami na macierz z informacją o położeniu tych komórek na siatcę.
7. Ustawiamy losowe punkty startowy i końcowy, tworząc wejście i wyjście z labiryntu.

## Struktury danych

### Cell
Struktura reprezentująca pojedynczą komórkę labiryntu.
Zawiera informacje o współrzędnych komórki, informację o odwiedzeniu oraz flagi określające, czy komórka ma ściany (połączenia z innymi komórkami).

## Funkcje

| Nazwa  | Parametry |  Typ zwrotny |  Opis |
| ------- |------|------ |------|
| initMaze      |int w, int h, SDL_Renderer* renderer|std::vector<std::vector<Cell>>| zwraca labirynt (macierz komórek), w którym nie ma żadnych połączeń między komórkami o podanej długości i szerokości    |
| generateMaze      | std::vector<std::vector<Cell>>& maze, SDL_Renderer* renderer, int sleepMs|void| generuje labirynt z losowo wybranym startowym punktem generacji     |
| visitCell      |Cell& cell, std::vector<std::vector<Cell>>& maze, SDL_Renderer* renderer, int sleepMs|void| odwiedza komórkę i (jeżeli to możliwe) tworzy połączenia między nią a jej sąsiadami    |
| isCellValid | int x, int y, std::vector<std::vector<Cell>>& maze |bool| zwraca informację, czy komórka jest poprawna, tj. czy nie wykracza poza labirynt i nie była jeszcze odwiedzona|
| hasNeighbours |Cell& cell, std::vector<std::vector<Cell>>& maze  |Cell*|zwraca losowego sąsiada spośród poprawnych (nieodwiedzonych) sąsiadów danej komórki|
| mazeToMatrix | std::vector<std::vector<Cell>>& maze, std::vector<std::vector<int>>& mat  |void| zamienia macierz komórek (połączeń między nimi) na macierz z informacją o tym, co znajduje się na danym polu|
| setStartAndEndPoint | std::vector<std::vector<Cell>>& maze, SDL_Renderer* renderer| void| losowo ustawia punkt, z którego startujemy i punkt, do którego mamy dotrzeć|
| drawMaze |std::vector<std::vector<int>>& matrixMaze, SDL_Renderer* renderer| void |wizualizuje labirynt przy użyciu biblioteki SDL2. Jest on rysowany jako siatka komórek, gdzie białe komórki reprezentują ścieżki, czarne to ściany, czerwone to punkt startowy, a zielone to punkt docelowy|
| drawMaze | std::vector<std::vector<int>>& maze, SDL_Renderer* renderer  | void |przygotowuje "drzewo" i zamienią na macierz, następnie wykonuje przeładowaną funkcję | 
| createMaze |int w, int h, int sleepMs| void | tworzy okienko i generuje labirynt, parametr w - szerokośc labiryntu, h - szerokość labiryntu, sleepMs - czas uśpenia między kolejnymi krokami generacji w milisekundach |

## Korzystanie z programu

```
int main() {
    // ustawiamy ziarno dla generatora liczb losowych
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // podajemy wymiary labiryntu
    int width = 15;
    int height = 15;

    // generujemy labirynt
    createMaze(width, height, 30);

    return 0;
}

```