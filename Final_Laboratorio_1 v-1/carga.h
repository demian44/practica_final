#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>
#include <strings.h>
#include "validacion.h"


/**
 * @brief Solicita un número al usuario y devuelve el resultado
 * @param mensaje Es el mensaje a ser mostrado
 * @return El número ingresado por el usuario
 */
int getInt(char* mensaje);

/**
 * @brief Solicita un número al usuario y devuelve el resultado
 * @param mensaje Es el mensaje a ser mostrado
 * @return El número ingresado por el usuario
 */
float getFloat(char mensaje[]);

/**
 * @brief Solicita una variable d tipo char al usuario y devuelve el resultado
 * @param mensaje Es el mensaje a ser mostrado
 * @return El caracter ingresado por el usuario
 */
char getChar(char mensaje[]);

/**
 * @brief Genera un numero aleatorio con un rango determinado
 * @param desde El valor minimo
 * @param desde El valor máximo
 * @return El numero generado de forma automática
 */
int getNumeroAleatorio(int desde, int hasta, int iniciar);

/**
 * @brief Solicita un texto al usuario y lo devuelve
 * @param mensaje Es el mensaje a ser mostrado
 * @param input Array donde se cargará el texto ingresado
 * @return void
 */
void getString(char mensaje[],char arrayChar[]);

/**
 * brief Solicita un texto al usuario y lo devuelve, a diferencia de getString, incluye todo menos el punto '.'
 * @param mensaje Es el mensaje a ser mostrado
 * @param input Array donde se cargará el texto ingresado
 * @return void
 */
void getText(char* mensaje,char* arrayChar,int cantidadDeCaracteres);
void getTexto(char* mensaje,char* arrayChar,char* cantidadDeCaracteres);

/**
 * @brief Solicita un texto numérico al usuario y lo devuelve
 * @param mensaje Es el mensaje a ser mostrado
 * @param input Array donde se cargará el texto ingresado
 * @return 1 si el texto contiene solo números
 */
int getNumerosChar (char array[],char mensaje[]);

/**
* @brief Solicita un texto, conformado solo con letras, al usuario y lo devuelve
* @param mensaje Es el mensaje a ser mostrado
* @param input Array donde se cargará el texto ingresado
* @return 1 si el texto contiene solo letras
*/
int getStringLetras(char mensaje[],char input[]);

/**
* @brief Solicita un texto, conformado solo con letras, al usuario y lo devuelve
* @param mensaje Es el mensaje a ser mostrado
* @param input Array donde se cargará el texto ingresado
* @return 1 si el texto contiene solo letras
*/
void getTexto(char* mensaje,char* arrayChar,char* cantidadDeCaracteres);

/**
 * @brief Solicita un texto, conformado solo con letras, al usuario, dando la posibilidad de reintentar cuantas veces lo desee el
 * usuario
 * @param str Array con la cadena a ser analizada
 * @param mensajeParaPedirDato mensaje para pedir el dato al usuario
 * @param mensajeError mensaje de error
 * \return 1 si contiene solo ' ' y letras y 0 si no lo es
 */
int ingresarSoloLetras (char auxiliar[], char mensajeParaPedirDato[],char mensajeError[]);

/**
 *  Carga y valida la descripcion para una pelicula
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param index valor de desplazamiento del puntero
 *  @return 1 si se cargo exitosamente y 0 en caso contrario
 */
int cargarNumero (char* auxiliar, char* mensajeParaPedirDato,char* mensajeError,int minimo, int maximo);
void getTexto(char* mensaje,char* arrayChar,char* cantidadDeCaracteres);
