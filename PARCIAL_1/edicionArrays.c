#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include "validaciones.h"
#include "estructuras.h"
#include "cargaYEdicion.h"
#include "edicionArrays.h"

/**
 * \brief Ordena un array de datos por criterio
 * \param cantidad de subindices/datos
 * \return -
 *
*/
void ordenarPorNombreYpasword(E_Usuario* listaPersonas, int cantidad)
{
    int i,j,k;
    int flag;
    comprimirArrayPersonas(listaPersonas,cantidad,1);
    E_Usuario auxiliarPersona;
    for(i=0; i<cantidad; i++)
    {
        if(listaPersonas[i].isEmpty==1)
        {
            break;
        }
        flag=0;
        auxiliarPersona = listaPersonas[i];
        for(j=i; j > 0 && stricmp(auxiliarPersona.nombre,listaPersonas[j-1].nombre)<=0 ; j--)
        {
            if(stricmp(auxiliarPersona.nombre,listaPersonas[j-1].nombre)<0)
            {
                flag=1;
                continue;
            }
            else if((stricmp(auxiliarPersona.nombre,listaPersonas[j-1].nombre))==0)
            {
                if(stricmp(auxiliarPersona.pasword,listaPersonas[j-1].pasword)>0)
                {
                    flag=1;
                }
                else if((stricmp(auxiliarPersona.pasword,listaPersonas[j-1].pasword)<0))
                {
                    break;
                }
            }
        }
        if(flag==1)
        {
            for(k=i; k>j; k--)
            {
                *(listaPersonas+k)=*(listaPersonas+(k-1));
            }
            listaPersonas[j]=auxiliarPersona;
        }
    }
}

/**
 * \brief Comprime un array de estructuras de tipo E_Usuario para diversos usos.
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param valor que indica el lugar en el índice donde se encuentra el lugar vacío.
 */
void comprimirArrayPersonas (E_Usuario arrayPersonas[],int cantidad, int banderaLibre)
{
    int i,j;
    for (i=0 ; i<cantidad; i++)
    {
        if(arrayPersonas[i].isEmpty==1)
        {
            j=i;
            for(; j<cantidad-1; j++)
            {
               ((arrayPersonas[j]))=(arrayPersonas[j+1]);
            }
            arrayPersonas[cantidad-1].isEmpty=1;
        }
    }
}
/**
 * \brief Ordena un array de datos y lo comprime
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 */
void ordenarPorNombreYComprimir (E_Usuario arrayPersona[], int cantidad)
{
    /**Esta funcion primero comprime eel array y luego valida los espacios vacios**/
    comprimirArrayPersonas(arrayPersona,cantidad,0);
    int i,j;
    E_Usuario auxiliarPersona;
    for(i=0; i<cantidad; i++)
    {
        if(arrayPersona[i].isEmpty==1)
        {
            continue;
        }
        auxiliarPersona = arrayPersona[i];
        j=i;
        for( ; j>0 && stricmp(auxiliarPersona.nombre,arrayPersona[j-1].nombre)<0 ; j--)
        {
            if(arrayPersona[j].isEmpty==1)
            {
                continue;
            }
            arrayPersona[j]=arrayPersona[j-1];
        }
        arrayPersona[j]=auxiliarPersona;
    }
}

/**
 * \brief imprime grafico utilizando cantidad de personas por edad
 * \param estructura y cantidad de personas
 * \return -
 *
*/
void ordenarProductosPorIdUsuario(E_Productos* listaProducos,int cantdadProductos)
{
    int i,j;
    E_Productos auxiliarProducto;
    for(i=1;i<cantdadProductos;i++)
    {
        auxiliarProducto=listaProducos[i];
        j=i;
        while(j>0&&auxiliarProducto.idUsuario<listaProducos[j-1].idUsuario)
        {
            listaProducos[j]=listaProducos[j-1];
            j--;
        }
        listaProducos[j]=auxiliarProducto;
    }
}

void ordenarPorId(E_Usuario arrayPersona[], int cantidad)
{
    int i,j;
    comprimirArrayPersonas(arrayPersona,cantidad,1);
    E_Usuario auxiliarPersona;
    for(i=1; i<cantidad; i++)
    {
        auxiliarPersona=arrayPersona[i];
        j=i;
        while(j>0&&(auxiliarPersona.id<arrayPersona[j-1].id))
        {
            arrayPersona[j]=arrayPersona[j-1];
            j--;
        }
        arrayPersona[j]=auxiliarPersona;
    }
}


void comprimirArrayProductos(E_Productos arrayProductos[],int cantidad, int banderaLibre)
{
    int i,j;
    for (i=0 ; i<cantidad; i++)
    {
        if(arrayProductos[i].isEmpty==banderaLibre)
        {
            j=i;
            for(; j<cantidad-1; j++)
            {
               *(arrayProductos+j)=*(arrayProductos+(j+1));
            }
            arrayProductos[cantidad-1].isEmpty=banderaLibre;
        }
    }
}

void ordenarPorIdPunteros(E_Usuario* arrayPersona[], int cantidad)
{
    int i,j;
    E_Usuario* auxiliarPersona;
    for(i=1; i<cantidad; i++)
    {
        auxiliarPersona=arrayPersona[i];
        j=i;
        while(j>0&&(auxiliarPersona->id<arrayPersona[j-1]->id))
        {
            arrayPersona[j]=arrayPersona[j-1];
            j--;
        }
        arrayPersona[j]=auxiliarPersona;
    }
}
