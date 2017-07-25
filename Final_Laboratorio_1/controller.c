#include "controller.h"
#include "carga.h"
#include "ArrayList.h"
#include "log.h"
#include "services.h"
#include "estadistica.h"
#include "snake/snake.h"
void controller()
{
    ArrayList* logList=al_newArrayList();
    ArrayList* serviceList=al_newArrayList();
    cargarListaServices(serviceList);
    int flag=0;
    char seguir='s';
    char opcion;
    do
    {

        fflush(stdin);
        printf("\n"); system("cls");
        printf("SISTEMA.\n\n1-Leer Log.\n2-Procesar informacion.\n3-Mostrar Estadistica\n4-Salir.\n");
        opcion=getChar("\nOpcion: ");
        switch(opcion)
        {
        case '1':
            cargarListalogs(logList,&flag);
            break;
        case '2':
            procesarInfo(&flag);
            break;
        case '3':
            serviciosConMasFallos(&flag);
            break;
        case '4':
            seguir='n';
            break;
        default:
            playGame();
            printf("Opcion incorrecta!\n");
            system("pause");
            break;
        }
    }
    while(seguir=='s' || seguir == 'S');
}
