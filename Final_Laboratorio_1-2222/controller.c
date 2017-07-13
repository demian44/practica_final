#include "ArrayList.h"
#include "controller.h"
#include "carga.h"
#include "tarjetas.h"
#include "clientes.h"
#include <stdio.h>
#include <stdlib.h>
void controller()
{
    int i;
    ArrayList* listas[CANTIDADLISTAS];
    for(i=0;i<CANTIDADLISTAS;i++)
        *(listas+i)=al_newArrayList();
    cargarListas(listas);
    generarListaValidos();
    guardarEnArchivo();
    char seguir='s';
    int opcion;
    do
    {
        fflush(stdin);
        system("cls");
        printf("SISTEMA.\n\n1-CLIENTES CON DATOS VALDOS.\n2-CLIENTES MASTER CARD VALIDOS.\n3-CLIENTES VISA VALIDOS.\n4-CLIENTES A. EXPRES VALIDOS.\n5-LISTAR CLIENTES CON DATOS INVALIDOS.\n6-SALIR.\n");
        opcion=getInt("\nOpcion: ");
        switch(opcion)
        {
        case 1:
            imprimirLista(LVALIDOS);
            break;
        case 2:
            imprimirLista(LMASTER);
            break;
        case 3:
            imprimirLista(LVISA);
            break;
        case 4:
            imprimirLista(LAMERICAN);
            break;
        case 5:
            imprimirLista(LINVALIDOS);
            break;
        default:
            seguir='n';
            break;
        }
    }
    while(seguir=='s' || seguir == 'S');
}
