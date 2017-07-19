#include "snake.h"

static snk snake[N];
static frt fruta;
static int tam;
static char campo[V][H];
static char seguir;
static int i,j;
static int muerto;
static int indexM;
static int puntuacion;

void inicio()
{
    ///*La cabeza de la serpiente
    snake[0].x=32;
    snake[0].y=10;
    puntuacion=0;
    indexM=0;

    ///* Tamaño de la serpiente
    tam = 4;
    ///*Coordenadas de la fruta.
    srand(time(NULL));
    do
    {
        fruta.x=rand() % (H-1);
    }
    while(fruta.x==0);
    do
    {
        fruta.y=rand() % (V-1);
    }
    while(fruta.y==0);

    for(i=0; i<tam ; i++)
    {
        snake[i].desplazamientoEnX = 1;
        snake[i].desplazamientoEny = 0;
    }

    intro_Campo(campo);
    intro_Datos(campo,tam);
}

void playGame()
{
    do
    {
        inicio(&tam,campo);///*Iniciar todos los elementos.
        loop(campo,tam);
        printf("\nDesea continuar?S/N");
        seguir=getch();
    }
    while(seguir!='n');
}

void intro_Campo()
{
    for(i=0; i<V; i++)
    {
        for(j=0; j<H; j++)
        {
            if(i==0 || i==V-1)
                campo[i][j]='-';
            else if(j==0 || j== (H-1))
                campo[i][j]='|';
            else
                campo[i][j]=' ';
            if(i==(V-1) && j>=H-10)
                campo[i][j]='/';
        }
    }
}
///*Metera todos los datos en la matrix campo
void intro_Datos()
{
    for(i=1; i<tam; i++)
    {
        snake[i].x = snake[i-1].x-1;
        snake[i].y = snake[i-1].y;
        snake[i].imagen= '*';

    }
    snake[0].imagen= 'O';
    for(i=0; i<tam; i++)
    {
        campo[snake[i].y][snake[i].x] = snake[i].imagen;
        campo[fruta.y][fruta.x]= '*';
    }
}

void draw()
{
    for(i=0; i<V; i++)
    {
        for(j=0; j<H; j++)
        {
            printf("%c",campo[i][j]);
        }
        if(i==10)
            printf("PUNTOS:%d",puntuacion);
        printf("\n");
    }
}
void loop()
{
    muerto=0;
    do
    {
        system("cls"); ///system("clear");
        draw();
        input();
        update();

    }
    while(muerto==0);
}

void input()
{
    char key;
    ///*saber si morimos
    if(snake[0].x==0 || snake[0].x==(H-1) || snake[0].y==0 || (snake[0].y==(V-1) && snake[0].x<(H-10)))
        muerto=1;
    if(snake[0].y>V)
        snake[0].y=2;
    for(i=1; i<tam && muerto==0; i++)
        if(snake[0].x==snake[i].x && snake[0].y==snake[i].y )
            muerto=1;
    ///*comprobar si se comio la fruta
    if(snake[0].x== fruta.x && snake[0].y==fruta.y)
    {
        puntuacion+=100;
        tam+=1;
        snake[tam-1].imagen='*';
        ///Hacer funcion apra la fruta
        do
        {
            fruta.x=rand() % (H-1);
        }
        while(fruta.x==0);

        do
        {
            fruta.y=rand() % (V-1);
        }
        while(fruta.y==0);
    }

    if(muerto==0)
    {
        ///si se oprime cualquier tecla kbhut da 1*///***////
        if(kbhit()==1)
        {
            key=getch();
            if(key=='2' && snake[0].desplazamientoEny!=-1)
            {
                snake[0].desplazamientoEnX=0;
                snake[0].desplazamientoEny=1;
            }
            if(key=='5' && snake[0].desplazamientoEny!=1)
            {
                snake[0].desplazamientoEnX=0;
                snake[0].desplazamientoEny=-1;
            }
            if(key=='1' && snake[0].desplazamientoEnX!=1)
            {
                snake[0].desplazamientoEnX=-1;
                snake[0].desplazamientoEny=0;
            }
            if(key=='3'&& snake[0].desplazamientoEnX!=-1)
            {
                snake[0].desplazamientoEnX=1;
                snake[0].desplazamientoEny=0;
            }
        }
    }
}

void update()
{
    ///Borrar odos los datos de la matriz
    intro_Campo();///borrar todo
    ///introducir los nuevos datos
    intro_Datos2();

}
void intro_Datos2()
{
    ///Crear el efecto de movimiento copiando las posiciones dee los elementos del cuerpo
    for(i=tam-1; i>0; i--)
    {
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
    snake[0].x+=snake[0].desplazamientoEnX;
    snake[0].y+=snake[0].desplazamientoEny;
    for(i=0; i<tam; i++)
    {
        campo[snake[i].y][snake[i].x]= snake[i].imagen;
    }
    campo[fruta.y][fruta.x]='*';
}


