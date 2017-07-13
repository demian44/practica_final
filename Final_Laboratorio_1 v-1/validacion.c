#include "validacion.h"
#include "strings.h"
#include "carga.h"

//#include <conio.h>

int esSoloLetras(char array[])
{
    int  i=0;
    while(array[i]!='\0')
    {
        if(array[i]!=' ' && (array[i]<'a' || array[i]>'z') &&(array[i]<'A' || array[i]>'Z'))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int esSoloLetrasSinEspacio(char array[])
{
    int  i=0;
    while(array[i]!='\0')
    {
        if(array[i]==' ' && (array[i]<'a' || array[i]>'z') &&(array[i]<'A' || array[i]>'Z'))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/**
 * \brief verifica si el dato ingresado es un numero
 * \param str es la cadena a ser analizada
 * \return devuelve 1 si es numerico 0 sino lo es
 *
 */
int esNumeroChar (char num[])
{
    int i=0;
    while(num[i]!='\0')
    {
        if(num[i] < '0' || num[i] > '9')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int esNumeroDecimalChar (char num[])
{
    int i=0;
    int j=0;
    int retorno=0;
    int contadorComas=0;
    char auxiliar[50];
    if(*(num)==',')
    {
        *auxiliar=0;
        *(auxiliar+1)=(*num);
        if(num[1] < '1' || num[1] > '9')
            auxiliar[2]=num[1];
        j=2;
        i=1;
    }

    while(num[i]!='\0')
    {
        if(num[i] < '1' || num[i] > '9' || *(num+i)!=',')
        {
            break;
        }
        if(*(num+i)==',')
        {
            contadorComas++;
            if(contadorComas==1)
                *(auxiliar+j)=*(num+i);
        }
        else
        {
            (*(auxiliar+j))=(*(num+i));
            if(contadorComas==1)
            {
                retorno=1;
                (*(auxiliar+j+1))='\0';
                break;
            }
        }
        i++;
        j++;
    }
    if(retorno==1)
        strcpy(num,auxiliar);
    return retorno;
}

/**
 * \brief Verifica si el valor recibido contiene solo letras y números
 * \param str Array con la cadena a ser analizada
 * \return 1 si contiene solo espacio o letras y números, y 0 si no lo es
 *
 */
int esAlfaNumerico(char str[])
{
    int i=0;
    while(str[i] != '\0')
    {
        if((str[i] != ' ') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') && (str[i] < '0' || str[i] > '9'))
            return 0;
        i++;
    }
    return 1;

}



/**
 * \brief Verifica si el valor recibido contiene solo números, + y -
 * \param str Array con la cadena a ser analizada
 * \return 1 si contiene solo numeros, espacios y un guion.
 *
 */
int esTelefono(char str[])
{
    int i=0;
    int contadorGuiones=0;
    while(str[i] != '\0')
    {
        if((str[i] != ' ') && (str[i] != '-') && (str[i] < '0' || str[i] > '9'))
            return 0;
        if(str[i] == '-')
            contadorGuiones++;
        i++;
    }
    if(contadorGuiones==1) // debe tener un guion
        return 1;

    return 0;
}

/**
 * \brief Solicita un texto numérico al usuario y valida si se encuentra dentro de un rango de edad lógico
 * \param input Array donde se cargará el texto ingresado
 * \return -
 */
void rangoEdad (char input[])
{
    int edad=atoi(input);
    if(edad<0 || edad>150)
    {
        printf("\nLA EDAD INGRESADA ES INVALIDA");
    }
}


int maximo(int maximo, int valor)
{
    int retorno=maximo;
    if(maximo<valor)
        retorno= valor;
    return retorno;
}

int introducirContrasenia(char* truePass, char* pasword)
{
    int retorno=0;
    char continuar='s';
    int intentos=0;
    do
    {

        if(intentos==3)
            break;
        getTexto("Ingresar contraseña: ",pasword,"50");
        if(strcmp(pasword,truePass)!=0)
        {
            continuar=getChar("Contraseña incorrecta Desea continuar? S/N\n\t");
        }
        else
        {
            retorno=1;
            continuar='n';
        }
        intentos++;
    }
    while(continuar=='s' && continuar=='S');
    return retorno;
}



int validarMail(char* mail)
{
    int i;
    int retorno=0;
    int flagArroba=0;
    int flagPunto=0;
    for(i=0; i<strlen(mail); i++){
        if(i==0 && ((mail[i]<'a' || mail[i]>'z')&&(mail[i]<'A' || mail[i]>'Z'))){
            flagArroba=0;
            break;
        }
        else if((mail[i]<'a' || mail[i]>'z')&&(mail[i]<'A' || mail[i]>'Z') && mail[i]!='.' && mail[i]!='@'){
            flagArroba=0;
            break;
        }
        else if(mail[i]=='@' && flagArroba==0){
                flagArroba++;
        }
        else if(mail[i]=='@' && flagArroba==1){
            flagArroba=0;
            break;
        }
        else if(mail[i]=='.'){
            flagPunto++;
            break;
        }
    }
    if(flagArroba==1 && flagPunto>0)
        retorno=1;
    return retorno;
}
