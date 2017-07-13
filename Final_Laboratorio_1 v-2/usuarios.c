#include "usuarios.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "estadistica.h"

static FILE* pUserFile;
static ArrayList* userList;
static ArrayList* uListOrdenadaNombre;
static ArrayList* uListOrdenadapaisYNombre;

void cargarUsuarios(ArrayList* user_List)
{
    userList=user_List;
    char buffer[1024];
    User* auxUsuario=NULL;
    pUserFile=fopen("usuarios.dat","r");
    while(pUserFile!=NULL && !feof(pUserFile))
    {
        fgets(buffer,1024,pUserFile);
        if(strncmp(buffer,"id",2)==0)
            continue;
        auxUsuario=(User*)malloc(sizeof(User));
        if(auxUsuario==NULL)
            break;
        sscanf(buffer," %d,%[^,],%[^,],%[^,],%[^,],%[^,],%16[^\n]",&auxUsuario->id,auxUsuario->nombre,auxUsuario->email,auxUsuario->sexo,auxUsuario->pais,auxUsuario->password,auxUsuario->ip_address);
        userList->add(userList,auxUsuario);
    }
    fclose(pUserFile);
}
void ordenarListasDeUsuarios(ArrayList*uListOrdenada_Nombre,ArrayList*uListOrdenadapaisY_Nombre)
{
    uListOrdenadapaisYNombre=uListOrdenadapaisY_Nombre;
    uListOrdenadaNombre=uListOrdenada_Nombre;
    uListOrdenadaNombre->sort(uListOrdenadaNombre,ordenarporNombre,1);
    uListOrdenadapaisYNombre->sort(uListOrdenadapaisYNombre,ordenarporpaisYNombre,1);
}

int ordenarporNombre(void* user1,void* user2)
{
    int retorno=0;
    User* userA=(User*)user1;
    User* userB=(User*)user2;
    if(strcmp(userA->nombre,userB->nombre)>0)
        retorno=1;
    return retorno;
}
int ordenarporpaisYNombre(void* user1,void* user2)
{
    int retorno=0;
    User* userA=(User*)user1;
    User* userB=(User*)user2;
    if(strcmp(userA->pais,userB->pais)>0)
        retorno=1;
    else if(strcmp(userA->pais,userB->pais)==0)
    {
        if(strcmp(userA->nombre,userB->nombre)>0)
            retorno=1;
    }
    return retorno;
}

void imprimirUsuario(int i,ArrayList* lista)
{
    User* u;
    u=(User*)lista->get(lista,i);
    if(u!=NULL)
        printf("\nNOMBRE: %s -- Nacionalidad: %s -- SEXO: %s",u->nombre,u->pais,u->sexo);
}

void mostrarListaUsuarios()
{
    int i;
    char opcion;
    printf("ELEJIR OPCION: \n1-Nombre\n2-Nacionalidad y nombre.\n");
    scanf(" %c",&opcion);
    switch(opcion)
    {
    case '1':
        for(i=0; i<userList->len(userList); i++)
            imprimirUsuario(i,uListOrdenadaNombre);
        system("pause");
        break;
    case '2':
        for(i=0; i<userList->len(userList); i++)
            imprimirUsuario(i,uListOrdenadapaisYNombre);
        system("pause");
        break;
    default:
        break;
    }
}



int obtenerIndicePorNick(int id)
{
    int retorno=-1;
    int index;
    User* u;
    for (index=0;index<userList->len(userList);index++){
        u=userList->get(userList,index);
        if(u==NULL)
            break;
        if(u->id==id){
            retorno=index;
            break;
        }
    }
    return retorno;
}


