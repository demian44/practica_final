#include <stdio.h>
#include <stdlib.h>
#define N 100
#define H 65
#define V 21
#include <time.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    int x,y;
    int desplazamientoEnX,desplazamientoEny;
    char imagen;
} snk;
typedef struct
{
    int x,y;
} frt;


void intro_Campo();
void inicio();
void playGame();
void intro_Datos();
void draw();
void loop();
void input();
void update();
void intro_Datos2();
