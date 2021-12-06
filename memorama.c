
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

char CheckForRepetitives(char list[], char letter){
    if(list[letter-97] != letter){
        //printf("NOT existent\n");
        //printf("[%c]", letter);
        list[letter-97] = letter;
        return letter;
    }else{
        //printf("EXISTENT\n");
        letter = rand() % (26) + 97;
        letter = CheckForRepetitives(list, letter);
        //return letter;
    }
    return letter;
}

char ** hiddenMatrix(int f, int c){

    srand(time(NULL));
    char ** newMatrix = (char**)malloc(f*sizeof(char*));
    char letras[27];
    char neew;
    int k = (c/2);
    for(int i = 0; i<f; i++){
        newMatrix[i]=(char*)malloc(c*sizeof(char));
    }
    for(int i = 0; i<f; i++){
        for(int j=0; j<k; j++){
            neew = rand() % (26) + 97; //97
            neew = CheckForRepetitives(letras, neew);
            newMatrix[i][j] = neew;
            //printf("[%c] added to matrix\n", neew);
            newMatrix[i][j + k] = neew;
            //printf("Copy of [%c] added to matrix\n", neew);
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
        if(t->columnas %2 != 0 && t->filas %2 != 0)
            printf("\nAbusado broder, elegiste dos numeros impares jeje, vas otra vez xd: ");
    }while(bandera == 0 && t->columnas %2 != 0);
}

//esta función define el numero de jugadores, el numero 1 si es individual, 2 si es en pareja y 3 si es contra la máquina
void gameMode(struct tablero *t){
    int modo = 0;
    do{
        printf("Bienvenido al juego 'Memorama'. \n\t*Presiona 1 para juego individual \n\t*Presiona 2 para juego de dos personas \n\t*Presiona 3 para juego contra la maquina \nElije tu modo de juego: ");
        scanf("%d",&modo);
        if(modo == 1)
            t->jugadores =1;
        else if(modo == 2)
            t->jugadores= 2;
        else if(modo == 3)
            t->jugadores= 3;
        else
            printf("\nModo invalido, intenta de nuevo\n ");
    }while(modo<1 || modo > 3);

}

//Funcion que regresa 1 si el usuario encontró un par
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


void play(struct tablero * t, int f, int c, char ** matriz, char ** matriz2 , struct cartas *k, GameStatus g){
    if(t->jugadores==1){
        int pares = 0;
        printf("***JUEGO INDIVIDUAL***");
        printMatrix(f, c, matriz);
        int compare;
        do{
            int iguales = pickCards(f,c,matriz,matriz2, k); //regresa 1 si el usuario encontró un par

            if(iguales!=1){
                printf("\n No es un par :(  ");
                matriz[k->cord1f-1][k->cord1c-1]= '?';
                matriz[k->cord2f-1][k->cord2c-1]= '?';
            }
            else {
                printf("\n Encontraste un par! ");
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
        printf("Felicidades broder! encontraste todos los pares, sos un krak");
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
            int iguales = pickCards(f,c,matriz,matriz2, k); //regresa 1 si el usuario encontró un par
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
                printf("\n Encontraste un par! ");
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
            printf("Felicidades! encontraron todos los pares y hubo un empate");

        }
        printf("Felicidades! encontraron todos los pares, el ganador es: %s\n\n",ganador);
        printf("******MARCADOR******\n");
        printf("%s encontro %d pares\n",jugador1,g->scoreJ1);
        printf("%s encontro %d pares\n",jugador2,g->scoreJ2);

        free(jugador1);
        free(jugador2);
    }



    else if(t->jugadores ==3){
        //Se crea una estructura pues sólo se necesita en la opción 3
        //La estructura tiene arreglos que almacenan las filas, columnas (coordenadas) y la carta en un mismo índice.

        struct machine {
            int * filas;
            int * columnas;
            char * conten;

        };
        typedef struct machine Art;
//reservamos memoria para los miembros de la estructura

        Art * arti = malloc(sizeof(Art*)*10);
        arti->filas = malloc(sizeof(int*)*10);
        arti->columnas = malloc(sizeof(int*)*10);
        arti->conten = malloc(sizeof(char*)*10);

        int compare; //variable a la que asignaremos el resultado de la función compareMatrix
        int flag = 0; //variable que nos indica si al levantar la segunda carta ya había una igual en la memoria de Arti
        int paresM = 0;//pares de la máquina
        int paresU = 0;//pares del usuario
        int cont = 0;//variable que incrementaremos cada que la máquina memorice una carta
        //variables temporales que sirven para elegir una carta ya memorizada en el primer movimiento de Arti
        int f11 = 0;
        int c11 = 0;
        int f21= 0;
        int c21= 0;
        int f12 = 0;
        int c12 = 0;
        int f22= 0;
        int c22= 0;
        printf("***JUEGO CONTRA LA MAQUINA***");
        printMatrix(f, c, matriz);

        do{     f11 = 0;
            c11 = 0;
            f21= 0;
            c21= 0;

            int iguales = pickCards(f,c,matriz,matriz2, k); //regresa 1 si el usuario encontró un par
            if (iguales != 1){ //si encontró un par no hay que memorizarlas cartas, si no lo encontró comienza el proceso.
                int i =0;
                //si la segunda carta elegida en el turno anterior no estaba en la memoria
                if(flag==0){
                    while(arti->conten[i]){//se revisa si las cartas elegidas por el usuario están en la memoria
                        if(arti->conten[i]== matriz2[k->cord1f-1][k->cord1c-1]){
                            if(arti->filas[i]!= k->cord1f || arti->columnas[i]!= k->cord1c){//se revisa que sus coordenadas no sean las mismas
                                f11 = arti->filas[i];  //si no son las mismas se asignan a las variables, y ese sería el primer y segundo movimiento de la máquina Arti
                                c11 = arti->columnas[i];
                                f21 = k->cord1f;
                                c21 = k->cord1c;
                            }
                        }
                        //se repite el proceso para la segunda carta elegida
                        if (arti->conten[i]== matriz2[k->cord2f-1][k->cord2c-1]){
                            if(arti->filas[i]!= k->cord2f || arti->columnas[i]!= k->cord2c){
                                f12 = arti->filas[i];
                                c12 = arti->columnas[i];
                                f22 = k->cord2f;
                                c22 = k->cord2c;
                            }

                        }
                        i++;
                    }
                }

                //se almacenan las cartas elegidas, estén en la memoria con anterioridad o no
                //se incrementa cont después de cada adición

                arti->filas[cont] = k->cord1f;
                arti->columnas[cont] = k->cord1c;
                arti->conten[cont] = matriz2[k->cord1f-1][k->cord1c-1];
                cont++;
                arti->filas[cont] = k->cord2f;
                arti->columnas[cont] = k->cord2c;
                arti->conten[cont] = matriz2[k->cord2f-1][k->cord2c-1];
                cont++;
                i=0;



                printf("\n No es un par :(  ");
                matriz[k->cord1f-1][k->cord1c-1]= '?';
                matriz[k->cord2f-1][k->cord2c-1]= '?';

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

                printf("\n**TURNO DE LA MAQUINA **");

                int f1, f2; //coordenadas de la fila de la primer y segunda carta
                int c1, c2; // coordenadas de la columna de la primer y segunda carta

                do{
                    f1=0;
                    c1=0;
                    f2=0;
                    c2=0;

                    if(f11!=0){ //se revisa si ya existía un movimiento a realizar y se asigna el valor de las variables temporales a las coordenadas
                        f1 =  f11;
                        c1 = c11;
                        f2 = f21;
                        c2 = c21;
                        f11=0;
                        c11=0;
                        f21=0;
                        c21=0;



                    }
                    else if(f12!=0){ //variables temporales si existía la segunda carta elegida por el usuario
                        f1 =  f12;
                        c1 = c12;
                        f2 = f22;
                        c2 = c22;
                        f12=0;
                        c12=0;
                        f22=0;
                        c22=0;

                    }
                    else{


                        do{
                            if(flag == 1){ //si en su segundo movimiento Arti encontró una carta que ya había memorizado, su primer movimiento siguiente será esa carta.
                                f1 = arti->filas[cont-3];//cont-3 porque siempre memoriza las dos cartas del usuario
                                c1 = arti->columnas[cont-3];
                                flag = 0;
                            }
                            else{//si no, elige una carta random
                                do{
                                    f1 = (1+ rand()) % (f+1);
                                    c1 = (1+ rand()) % (c+1);
                                }while(f1==0 || c1 == 0);


                                int i=0;
                                while(arti->conten[i]){ // se asegura que la carta elegida no sea una repetida
                                    if (arti->conten[i] == matriz2[f1-1][c1-1]){
                                        while(arti->filas[i] == f1 && arti->columnas[i] == c1){
                                            do{
                                                f1 = (1+ rand()) % (f+1);
                                                c1 = (1+ rand()) % (c+1);
                                            }while(f1==0 || c1 == 0);
                                        }
                                    }
                                    i++;

                                }
                            }

                        }while(matriz[f1-1][c1-1]== matriz2[f1-1][c1-1]); //se asegura de que la carta no esté destapada
                    }

                    printf("\nElegi la fila [%d] y la columna [%d]", f1, c1);
                    matriz[f1-1][c1-1] = matriz2[f1-1][c1-1];
                    printf("\nMi primer carta es '%c'", matriz[f1-1][c1-1]);
                    printMatrix(f,c,matriz);


                    i=0;
                    if(f2 == 0 || c2 ==0){
                        int j =0;
                        while(arti->conten[j] ){//si la carta que eligió existe en su memoria y no es repetida, su segunda carta es esa
                            if (arti->conten[j] == matriz[f1-1][c1-1]){
                                if(arti->filas[j]!= f1 || arti->columnas[j]!= c1){
                                    f2 = arti->filas[j];
                                    c2 = arti->columnas[j];
                                }
                            }
                            j++;
                        }
                    }

                    if(f2 == 0 || c2 ==0){ // si no tiene segunda carta ya elegida, lo hace randomly
                        do{
                            do{
                                f2 = (1+ rand()) % (f+1);
                                c2 = (1+ rand()) % (c+1);
                            }while(f2==0 || c2 == 0);


                            i=0;
                            while(arti->conten[i]){
                                if (arti->conten[i] == matriz2[f2-1][c2-1]){
                                    while(arti->filas[i] == f2 && arti->columnas[i] == c2){

                                        do{
                                            f2 = (1+ rand()) % (f+1);
                                            c2 = (1+ rand()) % (c+1);
                                        }while(f2==0 || c2 == 0);
                                    }
                                }
                                i++;

                            }


                        }while(matriz[f2-1][c2-1]== matriz2[f2-1][c2-1] || (f2==f1 && c2 ==c1));
                    }

                    printf("\nElegi la fila [%d] y la columna [%d]", f2, c2);
                    matriz[f2-1][c2-1] = matriz2[f2-1][c2-1];
                    printf("\nMi segunda carta es '%c'", matriz[f2-1][c2-1]);
                    printMatrix(f,c,matriz);


                    if(matriz[f1-1][c1-1]== matriz[f2-1][c2-1]){
                        printf("\nEncontre un par! ");
                        printf("Voy de nuevo ");
                        paresM++;
                    }
                    else{//si no encontró un par, almacena la primer carta
                        arti->conten[cont] = matriz[f1-1][c1-1];
                        arti->filas[cont] = f1;
                        arti->columnas[cont] = c1;
                        cont++;


                        i=0;
                        while(arti->conten[i]){ //revisa si la segunda carta ya la tenía
                            if (arti->conten[i] == matriz[f2-1][c2-1]){
                                if(arti->filas[i]!= f2 || arti->columnas[i]!= c2)
                                    flag = 1;
                            }
                            i++;
                        }
                        //Y luego la almacena en su memoria
                        arti->conten[cont] = matriz[f2-1][c2-1];
                        arti->filas[cont] = f2;
                        arti->columnas[cont] = c2;
                        cont++;





                    }
                    compare = compareMatrix (f, c, matriz,matriz2);
                }while(matriz[f1-1][c1-1]== matriz[f2-1][c2-1] && compare!=1 );
                if(compare!=1){
                    matriz[f1-1][c1-1]= '?';
                    matriz[f2-1][c2-1]= '?';

                    printf("\nNo es un par :( ");
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

                    for(int j=0; j<50; j++)
                        printf("\n");
                    printf("\nTe toca mai fren ");
                    printMatrix(f, c, matriz);}


            }
            else{
                if(compare!=1){
                    printf("\n¡Encontraste un par! \nVas de nuevo ");
                    paresU++;
                }
            }

            compare = compareMatrix (f, c, matriz,matriz2);

        }while(compare!=1);//mientras no haya terminado el tablero
        printf("\nJuego Terminado! ");
        printf("\n***MARCADOR***");
        printf("\nPares encontrados por la maquina: %d ", paresM);
        printf("\nPares que tú encontraste: %d", paresU);

        if(paresM>paresU)
            printf("\nGano la maquina! ");
        else if(paresM<paresU)
            printf("\nFelicidades!Ganaste!");
        else
            printf("\nHubo un empate, Buen juego camaradas!");

        free(arti);
    }


}
