#include "controller.h"
#include "menu.h"
#include "usuarios.h"
#include "temas.h"


void controller()
{
    int i;
    ArrayList* userList=al_newArrayList();
    ArrayList* temList=al_newArrayList();
    cargarUsuarios(userList);
    cargarTemas(temList);
    ArrayList* uListOrdenadaNombre=userList->clone(userList);
    ArrayList* uListOrdenadapaisYNombre=userList->clone(userList);
    ArrayList* tListOrdenado=temList->clone(temList);
    ordenarListasDeUsuarios(uListOrdenadaNombre,uListOrdenadapaisYNombre);
    ordenarListaTemas(tListOrdenado);
    char seguir='s';
    int opcion;
    do{
        system("cls");
        printf("STOPIFY.\n\n");
        printf("1- LISTAR USUARIOS.\n");
        printf("2- LISTAR TEMAS.\n");
        printf("3- ESCUCHAR TEMA.\n");
        printf("4- GUARDAR ESTADISTICA.\n");
        printf("5- INFORMAR.\n");
        printf("6- SALIR.\n");

        fflush(stdin);
        opcion=getInt("\nOpcion: ");
        switch(opcion)
        {
        case 1:
            mostrarListaUsuarios();
            break;
        case 2:
            mostrarTemas();
            break;
        case 3:
            i=getInt("Ingrse el Id: ");
            i=obtenerIndicePorNick(i);
            if(i!=-1)
                imprimirUsuario(i,userList);
            system("pause");
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            seguir='n';
            break;
        }
    }
    while(seguir=='s' || seguir == 'S');
}

