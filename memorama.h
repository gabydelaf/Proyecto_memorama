
#ifndef PROYECTO_MEMORAMA_MEMORAMA_H
#define PROYECTO_MEMORAMA_MEMORAMA_H

typedef struct tablero * Tablero;
typedef struct cartas * Cartas;
Tablero  newTablero();
Cartas  newCartas();
void getSize(struct tablero *t);
char** fillMatrix(int f, int c);
void printMatrix(int f, int c, char  ** matriz);
char ** hiddenMatrix(int f, int c);
void play(struct tablero * t, int f, int c, char ** matriz, char ** matriz2 , struct cartas *k);
int compareMatrix(int f, int c,  char ** matriz, char ** matriz2  );
//

int getF(struct tablero *t);
int getC(struct tablero *t);
void gameMode(struct tablero *t);
int pickCards (int f, int c, char ** matriz, char ** matriz2 , struct cartas *k);



#endif //PROYECTO_MEMORAMA_MEMORAMA_H
