// 1024

#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <random>

#define MIN 0
#define MAX 7

void printMap(int map[8][8]) {
    std::cout << "┏━━━━┯━━━━┯━━━━┯━━━━┯━━━━┯━━━━┯━━━━┯━━━━┓\n";
    for (int y = 0; y < 8; y++) {

        if (y != 0) {
            std::cout << "┠────┼────┼────┼────┼────┼────┼────┼────┨\n";
        }

        std::cout << "┃";
        for(int x = 0; x < 8; x++) {

            int n = map[y][x];
            if (n < 1) {
                std::cout << "    ";
            } else {
                printf("%4d", n);
            }

            if (x != 7) {
                std::cout << "│";
            }
        }
        std::cout << "┃\n";
    }
    std::cout << "┗━━━━┷━━━━┷━━━━┷━━━━┷━━━━┷━━━━┷━━━━┷━━━━┛\n";
}

void moveUp(int map[8][8]) {
    int i, c;
    for (int x = 0; x < 8; x++) {
        i = 0;
        for (int y = 0; y < 8; y++) {
            c = y;
            if (map[c][x] != 0) {
                if (map[i - 1][x] == map[c][x]) {
                    map[i - 1][x] = map[i - 1][x] * 2;
                } else {
                    map[i][x] = map[c][x];
                }

                if (c != i) map[c][x] = 0;
                if (map[i - 1][x] != map[c][x]) i += 1;
            }
        }
    }
}

void moveDown(int map[8][8]) {
    int i, c;
    for (int x = 0; x < 8; x++) {
        i = 7;
        for (int y = 0; y < 8; y++) {
            c = 7 - y;
            if (map[c][x] != 0) {
                if (map[i + 1][x] == map[c][x]) {
                    map[i + 1][x] = map[i + 1][x] * 2;
                } else {
                    map[i][x] = map[c][x];

                }

                if (c != i) map[c][x] = 0;
                if (map[i + 1][x] != map[c][x]) i -= 1;
            }
        }
    }
}

void moveRight(int map[8][8]) {
    int i, c;
    for (int y = 0; y < 8; y++) {
        i = 7;
        for (int x = 0; x < 8; x++) {
            c = 7 - x;
            if (map[y][c] != 0) {
                if (map[y][i + 1] == map[y][c]) {
                    map[y][i + 1] = map[y][i + 1] + map[y][c];
                } else {
                    map[y][i] = map[y][c];
                }

                if (c != i) map[y][c] = 0;
                if (map[y][i + 1] != map[y][c]) i -= 1;
            }
        }
    }
}

void moveLeft(int map[8][8]) {
    int i, c;
    for (int y = 0; y < 8; y++) {
        i = 0;
        for (int x = 0; x < 8; x++) {
            c = x;
            if (map[y][c] != 0) {
                if (map[y][i - 1] == map[y][c]) {
                    map[y][i - 1] = map[y][i - 1] * 2;
                } else {
                    map[y][i] = map[y][c];
                }

                if (c != i) map[y][c] = 0;
                if (map[y][i - 1] != map[y][c]) i += 1;
            }
        }
    }
}

bool isMovable(int map[8][8]) {

    int count = 0;
    for (int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if (map[y][x] == 0) count++;
        }
    }

    return count != 0;
}

void addNumber(int map[8][8]) {

    int count = 0;
    for (int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if (map[y][x] == 0) count++;
        }
    }

    srand(time(NULL));
    int lucky = rand() % count;
    for (int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if (map[y][x] == 0) {
                lucky--;
                if (lucky == 0) map[y][x] = 2;
            }
        }
    }
}

void initMap(int map[8][8]) {

    for (int y = 0; y < 8; y++)
        for(int x = 0; x < 8; x++)
            map[y][x] = 0;

    addNumber(map);
    addNumber(map);
    addNumber(map);
}

int main(void)
{

    int map[8][8];
    int end = 0;

    initMap(map);

    while(end == 0) {

        printMap(map);

        std::cout << "\nw:↑  d:→  s:↓  a:← || q:Quit\n\n";

        std::string c;
        std::cin >> c;
        if (c == "w") {
            moveUp(map);
        } else if(c == "d") {
            moveRight(map);
        } else if(c == "s") {
            moveDown(map);
        } else if(c == "a") {
            moveLeft(map);
        } else {
            std::cout << "Thank you for playing.";
            end = 1;
        }

        if (isMovable(map)) {
            addNumber(map);
        } else {
            std::cout << "GAME OVER";
        }
    }

    return 0;
}
