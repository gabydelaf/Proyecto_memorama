
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memorama.h"

struct tablero
{
    int filas;
    int columnas;
    int jugadores;
    int pares;
};

struct cartas
{
    int cord1f, cord2f;
    int cord1c, cord2c;
};

struct gameStatus{
    char * currentPlayer;
    int scoreJ1;
    int scoreJ2;
};

Tablero  newTablero(){
    Tablero t = malloc(sizeof(Tablero));
    t->filas=0;
    t->columnas=0;
    t->jugadores=0;
    t->pares = 0;
    return t;
}

Cartas  newCartas(){
    Cartas c = malloc(sizeof(Cartas));
    c-> cord1f=0;
    c-> cord1c=0;
    c-> cord2f=0;
    c-> cord2c=0;
    return c;
}

GameStatus newGameStatus(){
    GameStatus g = malloc(sizeof(GameStatus));
    g->currentPlayer =0;
    g->scoreJ1=0;
    g->scoreJ2=0;
    return g;
}

char ** fillMatrix(int f, int c){
    char ** matriz =(char**)malloc(f*sizeof(char*));
    for(int i = 0; i<f; i++){
        matriz[i] = (char*)malloc(c*sizeof(char));
        for(int j=0; j<c; j++){
            matriz[i][j]= '?';

        }
    }
    return matriz;
}

//funcion que contiene los resultados del juego
char ** hiddenMatrix(int f, int c){
    srand(time(NULL));
    char ** newMatrix = (char**)malloc(f*sizeof(char*));
    for(int i = 0; i<f; i++){
        newMatrix[i]=(char*)malloc(c*sizeof(char));

        for(int j=0; j<c; j++){
            newMatrix[i][j]= 'a' + rand() % ((f*c)/((f*c)/2));

            if (j>0){
                int conj = j;
                int coni = i;
                while(conj-1>= 0 && newMatrix[i][j]!= newMatrix[coni][conj-1]){
                    conj--;
                    if (conj ==0 && coni > 0 ){

                        conj = c;
                        coni--;
                    }
                    while(newMatrix[i][j]== newMatrix[coni][conj-1]){
                        newMatrix[i][j]= 'a' + rand() % 30;

                    }
                }
                while(newMatrix[i][j]== newMatrix[coni][conj-1]){
                    newMatrix[i][j]= 'a' + rand() % 30;

                }

            }
        }
    }

    return newMatrix;
}




void printMatrix(int f, int c, char ** matriz){
    int i,j;
    printf("\n");
    printf("   ");
    for(int i=1; i<=c; i++){
        printf("   %d    ",i);
    }
    printf("\n" );

    for(i=0;i<f;i++){

        printf(" %d ", i+1);
        for(j=0;j<c;j++){
            printf(" [ %c ]  ",matriz[i][j]);
        }
        printf("\n");
    }
}


void getSize(struct tablero *t) {
    int bandera =0;
    printf("\nWorales. Elije un numero de filas, crak: ");
    scanf("%d", &(t->filas));
    if(t->filas %2 == 0)
        bandera = 1;
    do{
        printf("\nAh, perro. Vas con un numero de columnas, campeon: ");
        scanf("%d", &(t->columnas));
        if(t->columnas %2 != 0 && t->filas %2 != 0){
            printf("\nAbusado broder, elegiste dos numeros impares jeje, vas otra vez xd: ");
        }
    }while(bandera == 0 && t->columnas %2 != 0);
}

//esta función define el numero de jugadores, el numero 1 si es individual, 2 si es en pareja y 3 si es contra la máquina
void gameMode(struct tablero *t){
    int modo = 0;
    printf("Bienvenido al juego 'Memorama'. \n\t*Presiona 1 para juego individual \n\t*Presiona 2 para juego de dos personas \n\t*Presiona 3 para juego contra la maquina \nElije tu modo de juego: ");
    scanf("%d",&modo);
    if(modo == 1)
        t->jugadores =1;
    if(modo == 2)
        t->jugadores= 2;
    if(modo == 3)
        t->jugadores= 3;

}

void play(struct tablero * t, int f, int c, char ** matriz, char ** matriz2 , struct cartas *k, GameStatus g){
    if(t->jugadores==1){
        int pares = 0;
        printf("***JUEGO INDIVIDUAL***");
        printMatrix(f, c, matriz);
        int compare;
        do{
            int iguales = pickCards(f,c,matriz,matriz2, k);
            if(iguales!=1){
                printf("\n No es un par :(  ");
                matriz[k->cord1f-1][k->cord1c-1]= '?';
                matriz[k->cord2f-1][k->cord2c-1]= '?';
            }
            else {
                printf("\n ¡Encontraste un par! ");
                pares++;

            }
            int enter;
            do{
                printf("\nPresiona 1 para continuar: ");
                scanf("%d", &enter);

                printf("\n[%d]",enter);
                if(enter == 1){
                    for(int i= 0; i<50; i++){
                        printf("\n");
                    }
                    printMatrix(f,c,matriz);
                }
                else printf("\nIntentalo de nuevo: ");
            }while(enter!=1);

            compare = compareMatrix (f, c, matriz,matriz2);


        }while (compare!=1);
        printf("¡Felicidades broder! encontraste todos los pares, sos un krak");
    }




    else if(t->jugadores==2){
        int pares = 0;
        char * jugador1 = malloc(50);
        char * jugador2 = malloc(50);
        char * ganador = malloc(50);
        printf("***JUEGO EN PAREJAS***");
        printf("\n\tNombre del jugador 1: ");
        scanf("%s",jugador1);
        printf("\n\tNombre del jugador 2: ");
        scanf("%s",jugador2);
        printf("\nEs turno de %s\n", jugador1);
        g->currentPlayer=jugador1;
        printMatrix(f, c, matriz);
        int compare;
        do{
            int iguales = pickCards(f,c,matriz,matriz2, k);
            if(iguales!=1){
                printf("\n No es un par :(  ");
                matriz[k->cord1f-1][k->cord1c-1]= '?';
                matriz[k->cord2f-1][k->cord2c-1]= '?';
                if(g->currentPlayer==jugador1){
                    g->currentPlayer= jugador2;
                    printf("\nEs turno de %s", jugador2);
                }
                else if(g->currentPlayer==jugador2){
                    g->currentPlayer= jugador1;
                    printf("\nEs turno de %s", jugador1);
                }
            }
            else {
                printf("\n ¡Encontraste un par! ");
                pares++;
                if(g->currentPlayer==jugador1){
                    g->scoreJ1 ++;
                }
                else if(g->currentPlayer==jugador2){
                    g->scoreJ2++;
                }


            }
            int enter;
            do{
                printf("\nPresiona 1 para continuar: ");
                scanf("%d", &enter);

                printf("\n[%d]",enter);
                if(enter == 1){
                    for(int i= 0; i<50; i++){
                        printf("\n");
                    }
                    printMatrix(f,c,matriz);
                }
                else printf("\nIntentalo de nuevo: ");
            }while(enter!=1);

            compare = compareMatrix (f, c, matriz,matriz2);


        }while (compare!=1);
        if(g->scoreJ1 > g->scoreJ2)
            ganador = jugador1;
        else if(g->scoreJ2 > g->scoreJ1)
            ganador = jugador2;
        else{
            printf("¡FelicidadeS! encontraron todos los pares y hubo un empate");

        }
        printf("¡Felicidades! encontraron todos los pares, el ganador es: %s\n\n",ganador);
        printf("******MARCADOR******\n");
        printf("%s encontró %d pares\n",jugador1,g->scoreJ1);
        printf("%s encontró %d pares\n",jugador2,g->scoreJ2);
    }


}


int compareMatrix(int f, int c,  char ** matriz, char ** matriz2  ){
    int compare = 0;
    for(int i=0; i<f;i++){
        for(int j=0; j<c;j++){
            if(matriz[i][j]==matriz2[i][j]){
                compare++;
            }
        }
    }
    if(compare>=(f*c))
        return 1;
    else return 0;
}



//funcion para elegir dos cartas
int pickCards (int f, int c, char ** matriz, char ** matriz2 , struct cartas *k)
{
    do{
        do{
            printf("\nElige tu primer carta :\n* Fila(1 - %d): ", f);
            scanf("%d", &k->cord1f);
            if(k->cord1f <= 0 || k->cord1f>f)
                printf("Fila invalida");
        }while(k->cord1f>f || k->cord1f <1);

        do{
            printf("* Columna(1 - %d): ",c);
            scanf("%d", &k->cord1c);
            if(k->cord1c <= 0 || k->cord1c>c)
                printf("Columna invalida");
        }while(k->cord1c > c || k->cord1c <1);
        printf("\nTu primer carta,[%d][%d] es '%c'\n",k->cord1f, k->cord1c, matriz2[k->cord1f-1][k->cord1c-1]);

        if(matriz[k->cord1f-1][k->cord1c-1]==matriz2[k->cord1f-1][k->cord1c-1]){
            printf("\n Esta carta ya fue descubierta, intentalo de nuevo: ");
        }

    }while(matriz[k->cord1f-1][k->cord1c-1]==matriz2[k->cord1f-1][k->cord1c-1]);

    matriz[k->cord1f-1][k->cord1c-1] = matriz2[k->cord1f-1][k->cord1c-1];
    printMatrix(f,c,matriz);

    do{
        do{
            if(k->cord1f==k->cord2f && k->cord1c==k->cord2c)
                printf("\nCarta igual a la anterior");
            do{
                printf("\nElige tu segunda carta :\n* Fila(1 - %d): ", f);
                scanf("%d", &k->cord2f);
                if(k->cord2f <= 0 || k->cord2f>f)
                    printf("Fila invalida");
            }while(k->cord2f>f || k->cord2f<=0);

            do{
                printf("* Columna(1 - %d): ",c);
                scanf("%d", &k->cord2c);
                if(k->cord2c <= 0 || k->cord2c>c )
                    printf("Columna invalida");
            }while(k->cord2c > c || k->cord2c<=0);
        }while(k->cord1f==k->cord2f && k->cord1c==k->cord2c);

        printf("\nTu segunda carta,[%d][%d] es '%c'\n",k->cord2f, k->cord2c, matriz2[k->cord2f-1][k->cord2c-1]);

        if(matriz[k->cord2f-1][k->cord2c-1]==matriz2[k->cord2f-1][k->cord2c-1]){
            printf("\n Esta carta ya fue descubierta, intentalo de nuevo: ");
        }

    }while(matriz[k->cord2f-1][k->cord2c-1]==matriz2[k->cord2f-1][k->cord2c-1]);

    matriz[k->cord2f-1][k->cord2c-1] = matriz2[k->cord2f-1][k->cord2c-1];
    printMatrix(f,c,matriz);

    if(matriz[k->cord1f-1][k->cord1c-1]!= matriz[k->cord2f-1][k->cord2c-1]){
        return 0;
    }
    else return 1;

}

int getF(struct tablero *t)
{
    return t->filas;
}

int getC(struct tablero *t)
{
    return t->columnas;
}
