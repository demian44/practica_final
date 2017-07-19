#include "services.h"
#include "log.h"
#include "ArrayList.h"
#include "stdlib.h"
#include "stdio.h"
#include "validacion.h"

static ArrayList* listaServicios;
static FILE* pFile;
static Service* service;
static    char buffer[1024];

void cargarListaServices(ArrayList* lista)
{
    char auxID[50];
    char auxName[50];
    char auxEmail[50];
    listaServicios=lista;
    pFile=fopen("services.txt","r");
    while(pFile!=NULL && !feof(pFile))
    {
        fgets(buffer,1024,pFile);
        if(service_new(&service)){
            sscanf(buffer,"%[^;];%[^;];%[^\n]",auxID,auxName,auxEmail);
            if(esNumeroChar(auxID) && validarMail(auxEmail)){
                service->id=atoi(auxID);
                strcpy(service->name,auxName);
                strcpy(service->email,auxEmail);
                listaServicios->add(listaServicios,service);
            }
        }
    }
    fclose(pFile);
   /* int i;
    for(i=0;i<listaServicios->len(listaServicios);i++){
        service=listaServicios->get(listaServicios,i);
        printService();
    }*/
}
int service_new(Service** service)
{
    int retorno=0;
    *service = (Service*)malloc(sizeof(Service));
    if(*service!=NULL)
        retorno=1;
    return retorno;
}



void printService(void)
{
    if(service!=NULL)
    {
        printf("ID: %d -- NOMBRE: %s -- EMAIL: %s\n",service->id,service->name,service->email);
    }
}

int buscarServicioPorId(int id)
{
    int retorno=-1;
    int i;
    for(i=0;i<listaServicios->len(listaServicios);i++)
    {
        service=listaServicios->get(listaServicios,i);
        if(service->id==id){
            retorno=id;
            break;
        }
    }
    return retorno;
}

int obtenerNombreServicioPorId(int id, char* retornoName)
{
    int retorno=0;
    int i;
    for(i=0;i<listaServicios->len(listaServicios);i++)
    {
        service=listaServicios->get(listaServicios,i);
        if(service->id==id){
            strcpy(retornoName,service->name);
            retorno=1;
            break;
        }
    }
    return retorno;
}

int obtenerEmailServicioPorId(int id, char* email)
{
    int retorno=0;
    int i;
    for(i=0;i<listaServicios->len(listaServicios);i++)
    {
        service=listaServicios->get(listaServicios,i);
        if(service->id==id){
            strcpy(email,service->email);
            retorno=1;
            break;
        }
    }
    return retorno;
}

ArrayList* getListaService(void)
{
    return listaServicios;
}


