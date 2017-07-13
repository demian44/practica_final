#include "temas.h"
#include "ArrayList.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
ArrayList* temList;
ArrayList* tListOrdenado;
FILE* pFile;
void cargarTemas(ArrayList* tem_list)
{
    temList=tem_list;
    char buffer[1024];
    Tema* auxTema=NULL;
    pFile=fopen("temas.dat","r");
    while(pFile!=NULL && !feof(pFile))
    {
        fgets(buffer,1024,pFile);
        if(strncmp(buffer,"id",2)==0)
            continue;
        auxTema=(Tema*)malloc(sizeof(Tema));
        if(auxTema==NULL)
            break;
        sscanf(buffer," %d,%[^,],%[^\n]",&auxTema->id,auxTema->nombre,auxTema->artista);
        temList->add(temList,auxTema);
    }
    fclose(pFile);
}

void ordenarListaTemas(ArrayList*tList_Ordenado)
{
    tListOrdenado=tList_Ordenado;
    tListOrdenado->sort(tListOrdenado,ordenarTemas,1);
}
int ordenarTemas(void* auxA, void* auxB)
{
    Tema* temaA=auxA;
    Tema* temaB=auxB;
    int retorno=0;
    if(strcmp(temaA->nombre,temaB->nombre)>0)
        retorno=1;
    else if(strcmp(temaA->artista,temaB->artista)>0)
        retorno=1;
    return retorno;
}

void mostrarTemas()
{
    int i;
    for(i=0;i<tListOrdenado->len(tListOrdenado);i++)
        imprimirTema(i,tListOrdenado);
    system("pause");
}


void imprimirTema(int i,ArrayList* lista)
{
    Tema* t;
    t=(Tema*)lista->get(lista,i);
    if(t!=NULL)
        printf("NOMBRE: %s -- Artista: %s\n",t->nombre,t->artista);
}


