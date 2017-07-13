#include "ArrayList.h"
#include <stdio.h>
typedef struct
{
    int id;
    int idTemas;
    char nombre[40];
    char email[40];
    char sexo[9];
    char pais[40];
    char password[20];
    char ip_address[16];
}User;

void cargarUsuarios(ArrayList* user_List);
void imprimirUsuario(int i,ArrayList* lista);
int ordenarporNombre(void* user1,void* user2);
int ordenarporpaisYNombre(void* user1,void* user2);
void ordenarListasDeUsuarios(ArrayList*uListOrdenadaNombre,ArrayList*uListOrdenadapaisYNombre);
void mostrarListaUsuarios();
