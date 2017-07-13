#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "validacion.h"
#include "carga.h"

void agregarPelicula(EMovie** movie,int*  peliculasCargadas,int *capacidadTotalPeliculas, int* cantidadPunteros)
{
    ampliacionMemoria(movie, *peliculasCargadas,capacidadTotalPeliculas,cantidadPunteros);
    if(agregarDatosPelicula(movie,peliculasCargadas,capacidadTotalPeliculas))
    {
        agregarPeliculaBinario(movie,peliculasCargadas);
        printf("\nCarga Exitosa!!\n\n");
        (*peliculasCargadas)++;
        cualquierTeclaContinnuar();
    }
}

void borrarPelicula(EMovie** movie, int* peliculasCargadas,int* capacidadTotalPeliculas,int* cantidadPunteros)
{
    if(*peliculasCargadas==0)
    {
        printf("No se encuentran peliculas en la base de datos.");
        getch();
        return;
    }
    char opcion;
    int i;
    int intentos=3;
    int indice;
    do
    {
        printf("\nElija la pelicula que desea borrar:\n");
        for(i=0; i<*peliculasCargadas; i++)
        {
            printf("\n%d- Pelicula: %s\n",i+1,((movie[i]))->titulo);
        }
        indice=getInt("Opcion: ")-1;
        if(indice<(*(peliculasCargadas)) && indice>0)
        {
            system("cls");
            printf("\nEsta a punto de borrar %s.\nPresione la tecla S para continuar:",(*(movie+indice))->titulo);
            opcion=getChar(" ");

        }
        else
        {
            printf("Opcion incorrecta, le quedan %d intentos. Desea reintentar? S/N  ",intentos-1);
            opcion=getChar(" ");
            intentos--;
            continue;
        }
        if(opcion=='s' || opcion== 'S')
        {
            comprimirArrayMovies(movie,peliculasCargadas, indice,capacidadTotalPeliculas);
            crearPisarArchivoBinario(movie,peliculasCargadas);
        }
        opcion='n';
    }
    while(intentos>0 && (opcion=='s'|| opcion== 'S'));
    ampliacionMemoria(movie,*peliculasCargadas,capacidadTotalPeliculas,cantidadPunteros);
    cualquierTeclaContinnuar();

}

void modificarDatosPelicula(EMovie** movie, int* peliculasCargadas,int* capacidadTotalPeliculas)
{
    if(*peliculasCargadas==0)
    {
        printf("No se encuentran peliculas en la base de datos.");
        getch();
        return;
    }
    int i;
    int indice;
    char opcion;
    int intentos=3;
    do
    {

        printf("\nElija la pelicula que desea modificar:\n");
        for(i=0; i<*peliculasCargadas; i++)
        {
            printf("\n%d- Pelicula: %s\n",i+1,((movie[i]))->titulo);
        }
        indice=getInt("Opcion: ")-1;
        if(indice<(*(peliculasCargadas)))
        {
            system("cls");
            printf("\nEsta a punto de modificar %s.\nPresione la tecla S para continuar:",(*(movie+indice))->titulo);
            opcion=getChar(" ");
        }
        else
        {
            printf("Opcion incorrecta, le quedan %d intentos. Desea reintentar? S/N  ",intentos-1);
            opcion=getChar(" ");
            intentos--;
            continue;
        }

        if(opcion=='s'|| opcion == 'S')
        {
            system("cls");
            opcion=getChar("Ingrese la opcion a modificar: \n\n1-Titulo. \n2-Genero. \n3-Duracion. \n4-Descripcion \n5-Puntaje \n6-Link de imagen\n");
            switch(opcion)
            {
            case '1':
                if(cargarTitulo(movie,indice))
                    printf("\nModificacion exitosa!");
                break;
            case '2':
                if(cargarGenero(movie,indice))
                    printf("\nModificacion exitosa!");
                break;
            case '3':
                if(cargarDuracion(movie,indice))
                    printf("\nModificacion exitosa!");
                break;
            case '4':
                if(cargarDescripcion(movie,indice))
                    printf("\nModificacion exitosa!");
                break;
            case '5':
                cargarPuntaje(movie,indice);
                break;
            case '6':
                if(cargarlinkImagen(movie,indice))
                    printf("\nModificacion exitosa!");
                break;
            default :
                printf("Error. Opcion incorrecta.");
                break;
            }
            for(i=0; i<=indice; i++)
                editMovieInFile(movie,indice);
            // return retorno;
        }
    }
    while(intentos>0 && (opcion =='s'&& opcion =='S'));
cualquierTeclaContinnuar();
}

void imprimirArchivo(EMovie** movie,int peliculasCargadas)
{
    FILE* pFile;
    char fileName[50];
    char opcion;
    int contador=3;
    int index;
    char fragmentoLink[]="\n<article class='col-md-4 article-intro'>\n<a href='#'>\n<img class='img-responsive img-rounded' src='";
    char fragmentoTitulo[]="\'nalt=''>\n </a>\n <h3>\n <a href='#'>";
    char fragmentoGenero[]="</a>\n </h3>\n<ul>\n<li>Género:";
    char fragmentoPuntaje[]="</li>\n<li>Puntaje:";
    char fragmentoDuracion[]="</li>\n<li>Duración:";
    char fragmentoDescripcion[]="</li>\n</ul>\n <p>";
    char fragmentoFin[]="</p>\n</article>";
    strcpy(fileName,"index.html");
    pFile=fopen(fileName,"rb");
    if(pFile!=NULL)
    {
        do
        {
            if(contador>0)
            {
                contador--;
                opcion=getChar("\nEl archivo  ya existe. Elija una opcion:\n1-Cambiar nombre\n2-Sobreescribir\n3-Salir");
            }
            else
                opcion='3';
            switch(opcion)
            {
            case '1':
                getTexto("\nElija un nombre distinto de index: ",fileName,"44");
                agregarExtension(fileName,".html");
                pFile=fopen(fileName,"rb");
                break;
            case '2':
                pFile=NULL;
                printf("\nEl archivo sera pisado!");
                getch();
                break;
            case '3':
                return;
            default:
                printf("\nOpcion incorrecta");
                break;
            }
        }
        while(pFile!=NULL);
    }
    pFile=fopen(fileName,"wb");
    if(pFile==NULL)
    {
        printf("NO SE PUDO GUARDAR O ACTUALIZAR LA PAGINA!!!");
        getch();
    }
    else
    {
        for(index=0; index<peliculasCargadas; index++)
        {
            fwrite(fragmentoLink,sizeof(char),strlen(fragmentoLink),pFile);
            fwrite(((*(movie+index))->linkImagen),sizeof(char),strlen(((*(movie+index))->linkImagen)),pFile);

            fwrite(fragmentoTitulo,sizeof(char),strlen(fragmentoTitulo),pFile);
            fwrite(((*(movie+index))->titulo),sizeof(char),strlen((*(movie+index))->titulo),pFile);

            fwrite(fragmentoGenero,sizeof(char),strlen(fragmentoGenero),pFile);
            fwrite(((*(movie+index))->genero),sizeof(char),strlen((*(movie+index))->genero),pFile);

            fwrite(fragmentoPuntaje,sizeof(char),strlen(fragmentoPuntaje),pFile);
            fwrite(((*(movie+index))->puntaje),sizeof(char),strlen((*(movie+index))->puntaje),pFile);

            fwrite(fragmentoDuracion,sizeof(char),strlen(fragmentoDuracion),pFile);
            fwrite(((*(movie+index))->duracion),sizeof(char),strlen((*(movie+index))->duracion),pFile);

            fwrite(fragmentoDescripcion,sizeof(char),strlen(fragmentoDescripcion),pFile);
            fwrite(((*(movie+index))->descripcion),sizeof(char),strlen((*(movie+index))->descripcion),pFile);

            fwrite(fragmentoFin,sizeof(char),strlen(fragmentoFin),pFile);
        }
        fclose(pFile);
        printf("\nDatos guardados exitosamente!\n");
        cualquierTeclaContinnuar();
    }
}
