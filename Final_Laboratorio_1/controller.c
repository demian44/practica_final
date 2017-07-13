#include "controller.h"
#include "carga.h"
#include "ArrayList.h"
void controller()
{
    char seguir='s';
    char opcion;
    do
    {
        fflush(stdin);
        system("cls");
        printf("SISTEMA.\n\n1- CARGAR DESTINATARIOS.\n2- CARGAR LISTA NEGRA.\n3- DEPURARA LISTA\n4- LISTAR.\n5- SALIR.\n");
        opcion=getChar("\nOpcion: ");
        switch(opcion)
        {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            seguir='n';
            break;
        default:
            break;
        }
    }
    while(seguir=='s' || seguir == 'S');
}
