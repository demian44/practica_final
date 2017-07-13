/*******************************************************************
*Programa:PARCIAL
*
*Nombre: Boullon Demian.
*
*
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define CANTPERS 20
#include "validaciones.h"
#include "cargaYEdicion.h"
#include "edicionArrays.h"
#include "lib.h"
#include "busqueda.h"
#define CANT 100
#define CANTIDADPRODUCTOS 100
int main()
{
    char seguir='s';
    int opcion=0;
    E_Usuario listaPersonas[CANT];
    E_Productos listaProductos[CANTIDADPRODUCTOS];

    int generadorID=4;
    int generadorIdProductos=0;
    int afiliadosConMasProductos[CANT];
    inicializarListaDePersonas(listaPersonas,CANT,1);
    inicializarListaDeProductos(listaProductos,CANTIDADPRODUCTOS,1);
    inicializarArrayDeIndices(afiliadosConMasProductos,CANT,-1);
    hardCode(listaPersonas,listaProductos);
    do
    {
        system("cls");
        printf("MERCADO LIBRE.\n\n");
        printf("1- ALTA DEL USUARIO.\n");
        printf("2- MODIFICAR DATOS DEL USUARIO.\n");
        printf("3- BAJA DEL USUARIO:.\n");
        printf("4- NUEVA PUBLICACION.\n");
        printf("5- MODIFICAR DATOS DE PUBLICACION.\n");
        printf("6- CANCELAR PUBLICACION.\n");
        printf("7- COMPRAR PRODUCTO.\n");
        printf("8- LISTAR PUBLICACIONES DE USUARIO.\n");
        printf("9- MOSTRAR LISTA DE PRODUCTO.\n");
        printf("10- LISTAR USUARIOS.\n");
        fflush(stdin);
        opcion=getInt("\nElija una opcion: ");
        switch(opcion)
        {
        case 1:
            alta(listaPersonas,CANT,generadorID,&generadorID);
            break;
        case 2:
            modificar (listaPersonas,CANT,"Ingrese ID del afiliado a modificar","\nId erroneo.\n","ID no encontrado");
            break;
        case 3:
            baja(listaPersonas,CANT,listaProductos,1000,"Ingrese ID para la baja","Error","ID no encontrado");
            break;
        case 4:
            nuevaPublicacion(listaPersonas,CANT,listaProductos,CANTIDADPRODUCTOS,generadorIdProductos);
            break;
        case 5:
            modificarPublicacion(listaPersonas,CANT,listaProductos,1000,"Ingrese ID de usuario","Error","ID no encontrado");
            break;
        case 6:
            cancelarPublicacion(listaPersonas,CANT,listaProductos,1000,"Ingrese ID de usuario","Error","ID no encontrado");
            break;
        case 7:
            nuevaCompra(listaPersonas,CANT,listaProductos, CANTIDADPRODUCTOS);
            break;
        case 8:
            listarPublicacionesDeUsuarios(listaPersonas,CANT,listaProductos,CANTIDADPRODUCTOS,"\nIngrece ID de usuario: ","\nERROR\n","ID NO ENCONTRADO");
            break;
        case 9:
            mostrarProductoConInformacion(listaProductos,listaPersonas,CANTIDADPRODUCTOS);
            break;
        case 10:
            listarUsuarios(listaPersonas,CANT);
        case 11:
            printf("\n");
            ordenarVectoresdeUsuarios(listaPersonas,CANT);
            break;
        default :
            printf("Opcion incorrecta.\n");
            system("cls");
            break;
        }
    }
    while(seguir=='s');
    return 0;
}
