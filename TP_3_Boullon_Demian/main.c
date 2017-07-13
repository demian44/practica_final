#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "carga.h"
#include <string.h>
int main()
{
    int cantidadPunteros=100;
    EMovie** movie=(EMovie**)malloc(sizeof(EMovie*)*cantidadPunteros);
    int peliculasCargadas=0;
    int capacidadTotalPeliculas=100;
    reservarEspeacio(movie,&capacidadTotalPeliculas);
    char seguir='s';
    int opcion=8;
    //hardCodearArray(movie);
    //crearPisarArchivoBinario(movie,&peliculasCargadas);
    cargarBaseDeDatos(movie,&peliculasCargadas,&capacidadTotalPeliculas,&cantidadPunteros);
    system("cls");
    do
    {
        system("cls");
        printf("//////////////////////////////////////////////////////////////////////////////\n");
        printf("/// MOVIE SYSTEM//////////////////////////////////////////////////////////////\n");
        printf("//////////////////////////////////////////////////////////////////////////////\n\n");
        printf("\n1-Agregar pelicula\n2-Borrar pelicula\n3-Modificar pelicula\n4-Generar pagina web\n5-Salir\n\nOpcion: ");
        fflush(stdin);
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            agregarPelicula(movie,&peliculasCargadas,&capacidadTotalPeliculas,&cantidadPunteros);
            break;
        case 2:
            borrarPelicula(movie,&peliculasCargadas,&capacidadTotalPeliculas,&cantidadPunteros);
            break;
        case 3:
            modificarDatosPelicula(movie,&peliculasCargadas,&capacidadTotalPeliculas);
            break;
        case 4:
            imprimirArchivo(movie,peliculasCargadas);
            break;
        case 5:
            printf("Gracias! Vuelvas prontos!");
            getch();
            seguir = 'n';
            break;
        }
        system("cls");
    }
    while(seguir=='s');

    return 0;
}
