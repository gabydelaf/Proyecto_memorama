#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memorama.h"

int main()
{

    Tablero t = newTablero();
    Cartas k = newCartas();
    gameMode(t);
    getSize(t);
    //printf("Este es un nuevo mensaje \n");
    char ** matriz = fillMatrix(getF(t), getC(t));
    char ** newMatrix = hiddenMatrix(getF(t), getC(t));
    printMatrix(getF(t), getC(t), newMatrix);
    printf("\n\n");
    play(t, getF(t), getC(t), matriz, newMatrix,k);
    printMatrix(getF(t), getC(t), matriz);
    return 0;
}


