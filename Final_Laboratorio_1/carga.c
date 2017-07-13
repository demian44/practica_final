#include "carga.h"

int getInt(char* mensaje)
{
    int entero;
    printf("%s",mensaje);
    scanf(" %d",&entero);
    return entero;
}

float getFloat(char mensaje[])
{
    float flotante;
    printf("%s",mensaje);
    scanf("%f",&flotante);
    return flotante;
}

char getChar(char mensaje[])
{
    char caracter;
    printf("%s",mensaje);
    fflush(stdin); // Win
    // fpurge(stdin); //Linux y OSx
    scanf(" %c",&caracter);
    return caracter;
}

int getNumeroAleatorio(int desde, int hasta, int iniciar)
{
    if(iniciar)
        srand (time(NULL));
    return desde + (rand() % (hasta + 1 - desde)) ;
}

void getString(char mensaje[],char arrayChar[])
{
    fflush(stdin);
    printf("%s",mensaje);
    scanf("%s",arrayChar);
}

void getText(char* mensaje,char* arrayChar,int cantidadDeCaracteres)
{
    if(cantidadDeCaracteres==21)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%21[^\n]",arrayChar);
    }
    else if(cantidadDeCaracteres==51)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%51[^\n]",arrayChar);
    }
    else if(cantidadDeCaracteres==101)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%101[^\n]",arrayChar);
    }
    else if(cantidadDeCaracteres==201)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%101[^\n]",arrayChar);
    }

}

void getTexto(char* mensaje,char* arrayChar,char* cantidadDeCaracteres)
{
    int i;
    char mascara[10]="%";
    strcpy((mascara+1),cantidadDeCaracteres);
    i=1+strlen(cantidadDeCaracteres);
    strcpy((mascara+i),"[^\n]");
    fflush(stdin);
    printf("%s",mensaje);
    scanf(mascara,arrayChar);
}

int getNumerosChar (char array[],char mensaje[])
{
    fflush( stdin );
    int retorno=0;
    getString(mensaje,array);
    if(esNumeroChar(array))
    {
        retorno= 1;
    }
    return retorno;
}


int getStringLetras(char mensaje[],char input[])
{
    fflush( stdin );
    getString(mensaje,input);
    if(esSoloLetras(input))
    {
        return 1;
    }
    return 0;
}

int ingresarSoloLetras (char auxiliar[], char mensajeParaPedirDato[],char mensajeError[])
{
    char seguir='s';
    int cargaExitosa;
    do
    {
        cargaExitosa=getStringLetras(mensajeParaPedirDato,auxiliar);
        if(!(cargaExitosa))
        {
            printf(mensajeError);// Ejemplo "Ha ingresado caracteres invalidos para un nombre.\n"
            seguir=getChar("Desea reintentar? s/n");
        }
    }
    while(cargaExitosa!=1 && seguir == 's');
    return cargaExitosa;
}

/**
* \brief Solicita un array de caracteres numericos al usuario,lo valida y lo devuelve
* \param array auxiliar
* \param Es el mensaje a ser mostrado
* \param Es el mensaje a ser mostrado
* \param valor minimo de referencia
* \param valor maximo de referencia
* \return 1 si el texto contiene solo letras
*/
int cargarNumero (char* auxiliar, char* mensajeParaPedirDato,char* mensajeError,int minimo, int maximo)
{
    char seguir='s';
    int retorno=0;
    int cargaExitosa;
    do
    {

        cargaExitosa=getNumerosChar(auxiliar,mensajeParaPedirDato);
        if(!(cargaExitosa) || (atoi(auxiliar)>maximo) || (atoi(auxiliar)<minimo))
            {
            printf(mensajeError);  // Ejemplo "Ha ingresado caracteres invalidos para un nombre.\n"
            seguir=getChar("Desea reintentar? s/n");
            continue;
            }
            else
            {
            retorno = 1;
            }


    }while(retorno!=1 && seguir == 's');

    return retorno;
}
