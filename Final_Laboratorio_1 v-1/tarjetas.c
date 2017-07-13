#include "ArrayList.h"
#include "tarjetas.h"
#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include "validacion.h"

int verificacionNumeroTarjeta(char* charNumero)
{
    int retorno=0;
    if(esNumeroChar(charNumero))
    {
        int len=strlen(charNumero);
        int entNumero[len];
        int suma=0;
        int i,j;
        for(i=0,j=len-1;i<len;j--,i++){
            sscanf(charNumero+i,"%1d",entNumero+j);
        }
        for(i=0;i<len;i++){
            if((i%2)!=0)
                entNumero[i]*=2;
            if(entNumero[i]>9)
                entNumero[i]-=9;
            suma+=entNumero[i];
        }
        if(!(suma%10))
            retorno=1;
    }
    return retorno;
}
