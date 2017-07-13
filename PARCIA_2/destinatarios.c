#include "destinatarios.h"
#include <conio.h>


void  cargarDestinatarios(ArrayList* lista, char* nombreArchivo,int* flagDepurado)
{
    E_Destinatario* destinatario;
    FILE* pFile=fopen(nombreArchivo,"r");
    if(pFile!=NULL && *flagDepurado==0)
    {

        while(!feof(pFile))
        {
            destinatario = (E_Destinatario*)malloc(sizeof(E_Destinatario)); //asigno memoria por cada destinatario
            fscanf(pFile,"%[^,],%[^\n]",destinatario->nombre,destinatario->mail);
            lista->add(lista,(void*)destinatario);
        }
        printf("Lista cargada.");
        fclose(pFile);
    }
    else
        printf("No se pudo cargar lista.");
    getch();


}

int compararMail(E_Destinatario* destinatario, E_Destinatario* listaNegra)
{
    int retorno=0;
    if(strcmp(destinatario->mail,listaNegra->mail)==0)
        retorno=1;
    return retorno;
}

int depurarLista(ArrayList* destinatarios,ArrayList* listaNegra,int* flagDepurado)
{

    int retorno=0;
    if(destinatarios!=NULL && listaNegra !=NULL  && destinatarios->len(destinatarios)>0 && listaNegra->len(listaNegra)>0 && *flagDepurado==0)
    {
        retorno=1;
        E_Destinatario* destinatario;
        E_Destinatario* noDestinatario;
        int i;
        int j;
        for(i=0; i<listaNegra->len(listaNegra); i++)
        {
            noDestinatario=listaNegra->get(listaNegra,i);
            for(j=0; j<destinatarios->len(destinatarios); j++)
            {
                destinatario=destinatarios->get(destinatarios,j);
                if(compararMail(noDestinatario,destinatario))
                    destinatarios->remove(destinatarios,j);
            }

        }
        eliminarRepetidos(destinatarios);
        (*flagDepurado)++;
        printf("Lista depurada.");
        listaNegra->deleteArrayList(listaNegra);
        getch();
    }
    else
    {
        printf("Error, no se pudo depurar lista.");
        getch();
    }
    return retorno;
}

void eliminarRepetidos(ArrayList* lista)
{
    int i;
    E_Destinatario* destinatario;
    for(i=0; i<lista->len(lista); i++)
    {
        destinatario=lista->get(lista,i);
        encontrarBorrarRepetido(lista,destinatario);
    }
}

void imprimirListaDepurada(ArrayList* listaDepurada,int*flagDepurado)
{
    if(*flagDepurado==1)
    {
        printf("Cantidad de usuarios: %d\n",listaDepurada->len(listaDepurada));
        getch();
        E_Destinatario* destinatario;
        int i;
        for(i=0; i<listaDepurada->len(listaDepurada); i++)
        {
            destinatario=listaDepurada->get(listaDepurada,i);
            printf("\n%s -- %s",destinatario->nombre,destinatario->mail);
        }
    }
    else
        printf("Lista, no depurada.");
        getch();
}

void encontrarBorrarRepetido(ArrayList* lista, E_Destinatario* destinatario)
{
    int flag=0;
    int i=0;
    E_Destinatario* auxDestinatario;
    for(i=0; i<lista->len(lista); i++)
    {
        auxDestinatario=lista->get(lista,i);
        if(compararMail(auxDestinatario,destinatario))
            flag++;
        if(flag>1)
        {
            lista->remove(lista,i);
            flag--;
        }
    }
}

