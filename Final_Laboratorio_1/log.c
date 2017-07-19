#include "log.h"
#include "services.h"
#include "ArrayList.h"
#include "stdlib.h"
#include "stdio.h"
#include "validacion.h"

static ArrayList* listaLog;
static FILE* pFile, * pFileDos;
static LogEntry* log;
static char buffer[1024];

void cargarListalogs(ArrayList* lista, int* flag)
{
    if(*flag!=0){
        printf("ERROR: La lista ya fue cargada.");
        printf("\n"); system("pause");
        return;
    }
    char auxDate[50];
    char auxTime[50];
    char auxId[50];
    char auxGrav[50];
    char auxMsg[50];
    listaLog=lista;
    pFile=fopen("log.txt","r");
    if(pFile==NULL)
        return;
    *flag=1;
    while(!feof(pFile))
    {
        fgets(buffer,1024,pFile);
        log=NULL;
        log_new(&log);
        if(log!=NULL){
            sscanf(buffer,"%[^;];%[^;];%[^;];%[^;];%[^\n]",auxDate,auxTime,auxId,auxGrav,auxMsg);
            if(esNumeroChar(auxId)){
                log->serviceId=atoi(auxId);
                log->gravedad=atoi(auxGrav);
                strcpy(log->date,auxDate);
                strcpy(log->time,auxTime);
                strcpy(log->msg,auxMsg);
                listaLog->add(listaLog,log);
            }
        }
        if(log==NULL)
            printf("Keh pedos\n");
    }
    fclose(pFile);
    /*int i;
    for(i=0;i<listaLog->len(listaLog);i++){
        log=listaLog->get(listaLog,i);
        printlog();
    }
    system("pause");*/
}

int log_new(LogEntry** log)
{
    int retorno=0;
    *log = (LogEntry*)malloc(sizeof(LogEntry));
    if(*log!=NULL)
        retorno=1;
    return retorno;
}

void printlog(void)
{
    char nombreServicio[33];
    if(log!=NULL){
        if(obtenerNombreServicioPorId(log->serviceId,nombreServicio)){
            printf(" %s -  %s -  %s\t-  %s\t-  %d\n",log->date,log->time,nombreServicio,log->msg,log->gravedad);
        }
    }
}

void procesarInfo(int * flag)
{
    if(*flag!=1){
        printf("Error. Lista sin cargar, ingrese la opcion 1, e intentelo nuevamente.");
        printf("\n"); system("pause");
        return;
    }
    else if(*flag==1)
        *flag=2;

    pFile=fopen("warnings.txt","w");
    pFileDos=fopen("errors.txt","w");

    char nombreServicio[33];
    char nombreEmail[33];
    int i;
    printf(" Fecha\t    -  Hora  -  Nombre serv.    -  Msg. error   - Gravedad\n\n");
    for(i=0;i<listaLog->len(listaLog) && pFile!=NULL && pFileDos!=NULL ;i++)
    {
        log=listaLog->get(listaLog,i);
       /* if(log==NULL)
        {
            printf("ERROR DE MEMORIA.");
            system("pause");
            break;
        }*/
        if(log->serviceId<3)
            continue;
        else if(log->gravedad==3)
        {
            if(log->gravedad!=45){
                obtenerNombreServicioPorId(log->serviceId,nombreServicio);
                obtenerEmailServicioPorId(log->serviceId,nombreEmail);
                fprintf(pFile,"%s;%s;%s;%s;%s\n",log->date,log->time,nombreServicio,log->msg,nombreEmail);
            }
        }
        else if(log->gravedad>=4 && log->gravedad<=7)
        {
            printlog();
        }
        else if((log->gravedad)>7)
        {

            obtenerNombreServicioPorId(log->serviceId,nombreServicio);
            obtenerEmailServicioPorId(log->serviceId,nombreEmail);
            fprintf(pFileDos,"%s;%s;%s;%s;%s\n",log->date,log->time,nombreServicio,log->msg,nombreEmail);

        }
    }
    fclose(pFile);
    fclose(pFileDos);
    printf("\n"); system("pause");
}

ArrayList* getListaLog(void)
{
    return listaLog;
}
