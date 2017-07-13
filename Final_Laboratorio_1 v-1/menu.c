#include "menu.h"
#include "conio.h"

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
    //int flagDepurado=0;
    do
    {
        fflush(stdin);
        printMenu();
        opcion=getInt("\nOpcion: ");
        switch(opcion)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            seguir='n';
            break;
        }
    }
    while(seguir=='s' || seguir == 'S');
}
