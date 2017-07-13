#include "ArrayList.h"
#include "tarjetas.h"
#include "clientes.h"
#include "carga.h"
#include <stdio.h>
#include <stdlib.h>


static ArrayList** listas;
static FILE* pFile;
void cargarListas(ArrayList** cListas)
{
    int i=0;
    listas=cListas;
    char buffer[1024];
    Clientes* auxCliente;
    pFile=fopen("data.csv","r");
    while(pFile!=NULL && !feof(pFile))
    {
        fgets(buffer,1024,pFile);
        if(strncmp(buffer,"id",2)==0)
            continue;
        auxCliente=clientes_new();
        if(auxCliente==NULL)
            break;
        i++;
        sscanf(buffer," %5[^,],%[^,],%[^,],%[^,],%[^\n]",auxCliente->id,auxCliente->nombre,auxCliente->apellido,auxCliente->email,auxCliente->tarjeta.numero);
        listas[LGENERAL]->add(listas[LGENERAL],auxCliente);
    }
    fclose(pFile);
}

void imprimirLista(int lista)
{
    char categoria[50];
    switch(lista)
    {
        case LINVALIDOS:
            strcpy(categoria,"USUARIOS INVALIDOS");
            break;
        case LVALIDOS:
            strcpy(categoria,"USUARIOS VALIDOS  ");
            break;
        case LMASTER:
            strcpy(categoria,"MASTER CARD       ");
            break;
        case LVISA:
            strcpy(categoria,"LVISA             ");
            break;
        case LAMERICAN:
            strcpy(categoria,"AMERICAN EXPRES   ");
            break;
    }

    Clientes* cliente;
    int i;
    if(listas[lista]==NULL)
        return;
    system("cls");
    for(i=0;i<listas[lista]->len(listas[lista]);i++){
        cliente=listas[lista]->get(listas[lista],i);
        printf("-------------------------------------\n");
        printf("                  %s |\n",categoria);
        printf("-------------------------------------\n");
        printf("ID: %s \nNOMBRE: %s APELLIDO: %s\nEMAIL: %s\nTARJERA: %s\n\n",cliente->id,cliente->nombre,cliente->apellido,cliente->email,cliente->tarjeta.numero);
    }
    system("pause");
}

void generarListaValidos(void)
{
    int i;
    int indiceDeListas;
    Clientes* cliente;
    for(i=0;i<listas[LGENERAL]->len(listas[LGENERAL]);i++)
    {
        cliente=listas[LGENERAL]->get(listas[LGENERAL],i);
        indiceDeListas=detectarTarjeta(cliente->tarjeta.numero);
        if(indiceDeListas==LINVALIDOS){
            strcpy(cliente->tarjeta.numero,"DATO INVALIDO");
        }
        if(!validarMail(cliente->email)){
            strcpy(cliente->email,"DATO INVALIDO");
            indiceDeListas=LINVALIDOS;
        }
        if(!esSoloLetras(cliente->nombre)){
            strcpy(cliente->nombre,"DATOINVALIDO");
            indiceDeListas=LINVALIDOS;
        }
        if(!esSoloLetras(cliente->apellido)){
            strcpy(cliente->apellido,"DATO INVALIDO");
            indiceDeListas=LINVALIDOS;
        }
        if(!validarId(i)){
            strcpy(cliente->id,"DATO INVALIDO");
            indiceDeListas=LINVALIDOS;
        }
        listas[indiceDeListas]->add(listas[indiceDeListas],cliente);
        if(indiceDeListas!=LINVALIDOS)
            listas[LVALIDOS]->add(listas[LVALIDOS],cliente);
    }
}


Clientes* clientes_new(){
    Clientes* pointer = (Clientes*)malloc(sizeof(Clientes));
    return pointer;
}


int validarId(int index)
{
    int retorno=0;
    Clientes* cliente=listas[LGENERAL]->get(listas[LGENERAL],index);
    Clientes* auxCliente;
    int i;
    if(esNumeroChar(cliente->id))
    {
        retorno=1;
        for(i=0;i<listas[LGENERAL]->len(listas[LGENERAL]);i++){
            if(i==index)
                continue;
            auxCliente=listas[LGENERAL]->get(listas[LGENERAL],i);
            if(strcmp(auxCliente->id,cliente->id)==0){
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}


int detectarTarjeta(char* tarjet)
{
    int retorno=LINVALIDOS;
    if(verificacionNumeroTarjeta(tarjet))
    {
        int cantidadNumeeros=strlen(tarjet);
        if((strcmp("34",tarjet)==0 || strcmp("37",tarjet)==0)&& cantidadNumeeros==15)
            retorno=LAMERICAN;
        else if((strncmp(tarjet,"50",2)>0 && strncmp(tarjet,"56",2)<0)&& cantidadNumeeros==16)
            retorno=LMASTER;
        else if(strncmp(tarjet,"4",1)==0 && ( cantidadNumeeros==13 || cantidadNumeeros==16))
            retorno=LVISA;
    }
    return retorno;
}

void guardarEnArchivo()
{
    char array_nombreArchivo[5][30];
    strcpy(array_nombreArchivo[LVALIDOS],"Usuarios_validos.csv");
    strcpy(array_nombreArchivo[LINVALIDOS],"Usuarios_invalidos.csv");
    strcpy(array_nombreArchivo[LVISA],"Usuarios_Visa.csv");
    strcpy(array_nombreArchivo[LMASTER],"Usuarios_MasterCard.csv");
    strcpy(array_nombreArchivo[LAMERICAN],"Usuarios_AMERICAN_E.csv");
    int i,j;
    Clientes* cliente;
    for(i=1;i<CANTIDADLISTAS;i++){
        pFile=fopen(array_nombreArchivo[i],"w");
        fprintf(pFile,"%s","id,first_name,last_name,email,card\n");
        for(j=0;j<listas[i]->len(listas[i]);j++){
            cliente=(Clientes*)listas[i]->get(listas[i],j);
            fprintf(pFile,"%s,%s,%s,%s,%s\n",cliente->id,cliente->nombre,cliente->apellido,cliente->email,cliente->tarjeta.numero);
        }
        fclose(pFile);
    }
}


