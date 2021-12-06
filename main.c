#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memorama.h"

int main()
{
    Tablero t = newTablero();
    Cartas k = newCartas();
    GameStatus g = newGameStatus();
    gameMode(t);
    getSize(t);
    char ** matriz = fillMatrix(getF(t), getC(t));
    char ** newMatrix = hiddenMatrix(getF(t), getC(t));
    //printMatrix(getF(t), getC(t), newMatrix); //Matriz del memorama
    printf("\n\n");
    play(t, getF(t), getC(t), matriz, newMatrix,k,g);
    printMatrix(getF(t), getC(t), matriz);
    return 0;
}


