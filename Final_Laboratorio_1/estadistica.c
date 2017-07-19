#include "services.h"
#include "log.h"
#include "ArrayList.h"
#include "stdlib.h"
#include "stdio.h"
#include "validacion.h"
#include "estadistica.h"

static Estadistica estadistica;
static ArrayList* listaLog;
static ArrayList* listaServicios;

void serviciosConMasFallos(int* flag)
{
    if(*flag==2)
    {
        listaLog=getListaLog();
        listaServicios=getListaService();
        LogEntry* log;
        Service* service;
        int contadorFallos;
        int i,j;
        for(i=0;i<listaLog->len(listaLog);i++)
        {
            log=listaLog->get(listaLog,i);
            if(log->gravedad<3)
                estadistica.fallos[CANTIDADMENORTRES]++;
            else if(log->gravedad==3)
                estadistica.fallos[CANTIDADTRES]++;
            else if(log->gravedad>=4 && log->gravedad<=7)
                estadistica.fallos[CANTIDADCUATROSIETE]++;
            else if(log->gravedad>7)
                estadistica.fallos[CANTIDADCUATROSIETE]++;
        }
        for(i=0;i<listaServicios->len(listaServicios);i++)
        {
            contadorFallos=0;
            service=listaServicios->get(listaServicios,i);
            for(j=0;j<listaLog->len(listaLog);j++)
            {
                log=listaLog->get(listaLog,i);
                if(log->serviceId==service->id)
                    contadorFallos++;
            }
            if(contadorFallos>estadistica.cantidadFallasServicio)
                {
                estadistica.cantidadFallasServicio=contadorFallos;
                strcpy(estadistica.nameServicioMasFallas,service->name);
                }

        }
        imprimirEstadistica();
    }
    else if(*flag==0){
        printf("No se ha cargado la lista log.txt, ingrese la opcion 1, luego la opcion 2 e intentelo nuevamente...\n");
        printf("\n"); system("pause");
    }
    else{
        printf("Aun no se procesado la informacion... acceda a la opcion 2 e intentelo nuevamente...");
    }

}

void inicializarEstadistica(ArrayList* lista_Log,ArrayList* lista_Servicios)
{
    listaLog=lista_Log;
    listaServicios=lista_Servicios;
    estadistica.cantidadFallasServicio=0;
    int i;
    for(i=0;i<CANTIDADFALLOS;i++)
        estadistica.fallos[i]=0;
    estadistica.maximo=0;
}

void imprimirEstadistica()
{
    system("cls");
    printf("SERVICIO CON MAS FALLOS: %s\n",estadistica.nameServicioMasFallas);
    printf("GRAVEDAD MENOR A TRES: %d\n",estadistica.fallos[CANTIDADMENORTRES]);
    printf("GRAVEDAD IGUAL A TRES: %d\n",estadistica.fallos[CANTIDADTRES]);
    printf("GRAVEDAD CUATRO-SIETE: %d\n",estadistica.fallos[CANTIDADCUATROSIETE]);
    printf("GRAVEDAD MAYOR A SIETE: %d\n",estadistica.fallos[CANTIDADMAYORSIETE]);
    system("pause");
}
