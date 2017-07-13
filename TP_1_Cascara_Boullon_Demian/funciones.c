#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "validacion.h"

/*
* \brief  Solicita un n�mero al usuario y devuelve el mismo.
* \param  mensaje "Mensaje que debe introducir el usuario, el cual refiere al numero que se solicitar�".
* \return El n�mero ingresado por el usuario.
*/
float ingreso(char mensaje [])
{
    float numero;
    printf("%s", mensaje);
    scanf("%f", &numero);
    return numero;
}

/*
* \brief   Suma dos n�meros y devuelve el resultado.
* \param   a y b Dos n�meros que ser�n sumados.
* \return  El resultado de la suma.
*/
float sumarDosNumFlot(float num1, float num2)
{
    float resultado;
    resultado=num1+num2;
    return resultado;
}

/*
* \brief   Resta dos n�meros y devuelve el resultado.
* \param   a y b "valores usados para realizar la divisi�n("a" sobre "b").
* \return  El resultado de la resta.
*/
float restarDosNumFlot(float num1, float num2)
{
    float resultado;
    resultado=num1-num2;
    return resultado;
}

/*
* \brief   Divide dos n�meros y devuelve el resultado.
* \param   a y b   valores para realiar la divisi�n.
* \return  El resultado de la divisi�n.
*/
float dividirDosNumFlot(float num1, float num2)
{
    float resultado;
    resultado=num1/num2;
    return resultado;
}

/*
* \brief   Multiplica dos n�meros y devuelve el resultado.
* \param   a y b valores que ser�n multiplicados.
* \return  El resultado de la multiplicaci�n.
*/
float multiDosNumFlot(float num1, float num2)
{
    float resultado;
    resultado=num1*num2;
    return resultado;
}

/*
* \brief   Se factoriza un n�mero y devuelve el resultado.
* \param   num1  valor para realizar la factorizaci�n.
* \return  El resultado de la factorizaci�n.
*/
long long factorialA(float num1)
{
    long long respuesta=1;
    int i;
    for(i=num1; i>1; i--)
    {
        respuesta=respuesta*i;
    }
    return respuesta;
}

/*
* \brief  Piede al usuario una tecla cualquiera para continuar.
* \param  -
* \return -
*/
void CualquierTeclaContinnuar (void)
{
    printf("Presione cualquier tecla para continuar.");
    getch();
}

/*
* \brief  Llama a las funciones de suma, resta, multiplicacion, divisi�n y factorial, e imprime el resultado en pantalla.
* \param  num1 y num2  valores que utilizar� para realizar todas las operaciones.
* \return -
*/
void integralDeOperaciones (float num1, float num2)
{
    float resultado;
    long long resultadoFactorial;

    resultado=sumarDosNumFlot(num1,num2);
    printf("\n -El resultado de la suma entre %.2f y %.2f es: %.2f\n",num1,num2,resultado);

    resultado=restarDosNumFlot(num1,num2);
    printf(" -El resultado de %.2f menos %.2f da: %.2f\n",num1,num2,resultado);

    if(num2!=0)
    {
        resultado=dividirDosNumFlot(num1,num2);
        printf(" -La division entre %.2f y %.2f es: %.2f\n",num1,num2,resultado);
    }
    else
    {
        printf(" -Error, imposible dividir por cero.\n");
    }
    resultado=multiDosNumFlot(num1,num2);
    printf(" -El producto entre %.2f y %.2f es: %.2f\n",num1,num2,resultado);

    if(validarEntero(num1))
    {
        resultadoFactorial= factorialA(num1);
        printf(" -El factorial de %.0f es %lld\n\n",num1,resultadoFactorial);//en windows la firma long long es "%I64d"
    }
    else
    {
        printf(" -%.2f no se puede factorizar.\n\n",num1);
    }
}
