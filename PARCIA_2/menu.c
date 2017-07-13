
#include "menu.h"
#include "conio.h"
#include "destinatarios.h"


void printMenu(void)
{
    system("cls");
    printf("SISTEMA.\n\n");
    printf("1- CARGAR DESTINATARIOS.\n");
    printf("2- CARGAR LISTA NEGRA.\n");
    printf("3- DEPURARA LISTA\n");
    printf("4- LISTAR.\n");
    printf("5- SALIR.\n");
}

void menuPrincipalMercadoLibre(ArrayList* listaDestinatarios,ArrayList* listaNegra)
{

    char seguir='s';
    int opcion;
    int flagDepurado=0;
    do
    {
        fflush(stdin);
        printMenu();
        opcion=getInt("\nOpcion: ");
        switch(opcion)
        {
        case 1:
            cargarDestinatarios(listaDestinatarios,"destinatarios.csv",&flagDepurado);
            break;
        case 2:
            cargarDestinatarios(listaNegra,"black_list.csv",&flagDepurado);
            break;
        case 3:
            depurarLista(listaDestinatarios,listaNegra,&flagDepurado);
            break;
        case 4:
            imprimirListaDepurada(listaDestinatarios,&flagDepurado);
            break;
        default:
            seguir='n';
            break;
        }
    }
    while(seguir=='s' || seguir == 'S');
}
