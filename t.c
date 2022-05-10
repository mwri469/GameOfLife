#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main() {
    system("cl /W4 GameOfLife.c");
    system("GameOfLife");
    return 0;
}