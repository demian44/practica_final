#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <strings.h>
#include "funciones.h"
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
int cargarDescripcion(EMovie** movie, int index);

/**
 *  Carga y valida el genero para una pelicula
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param index valor de desplazamiento del puntero
 *  @return 1 si se cargo exitosamente y 0 en caso contrario
 */
int cargarGenero(EMovie** movie,int index);

/**
 *  Carga y valida la duracion para una pelicula
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param index valor de desplazamiento del puntero
 *  @return 1 si se cargo exitosamente y 0 en caso contrario
 */
int cargarDuracion (EMovie** movie,int index);

/**
 *  Carga un link a una imagen para una pelicula
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param index valor de desplazamiento del puntero
 *  @return 1 si se cargo exitosamente y 0 en caso contrario
 */
int cargarlinkImagen(EMovie** movie,int index);

/**
 *  Carga y valida un puntaje a una imagen para una pelicula
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param index valor de desplazamiento del puntero
 *  @return 1 si se cargo exitosamente y 0 en caso contrario
 */
int cargarPuntaje (EMovie** movie,int index);
int cargarTitulo(EMovie** movie,int index);
void mayToMin(char* string);
void agregarExtension(char* array,char* extension);
void getTexto(char* mensaje,char* arrayChar,char* cantidadDeCaracteres);
void crearPisarArchivoBinario(EMovie** movie, int* peliculasCargadas);

/**
 *  Cuenta la cantidad de estructuras en el archivo y
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param cantidadPeliculas cantidad de peliculas cargadas, la misma se edita por referencia con el resultado del conteo
 */
int contarPeliculasFile(char* nFile,int* cantidadPeliculas);

/**
 *  Sobreescribe la una estructura dentro de un archivo
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param indice es el subindice en el array, que en este caso indica el desplazamiento dentro del archivo
 */
void editMovieInFile(EMovie** movie,int indice);

/**
 *  Carga en la memoria una cantidad determinada de peliculas
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 */
void hardCodearArray (EMovie** list);

/**
 *  Reserva espacio en memoria para una cantidad estimada de peliculas, si no llega a cumplir el requisito, avisa por pantalla y
 *  edita el valor original por referencia.
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 */
void reservarEspeacio(EMovie** movie,int* capacidadTotalPeliculas);

/**
 *  Agrega una variable de tipo EMovie al final del archivo
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 *  @param cantidadPunteros cantidad de punteros disponibles
 */
void agregarPeliculaBinario(EMovie** movie,int* peliculasCargadas);

/**
 *  Si es que existe un archivo movie.txt con datos, este los carga en el array y edita la cantidad de peliculas cargadas
 *  por referencia.
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 *  @param cantidadPunteros cantidad de punteros disponibles
 */
void cargarBaseDeDatos(EMovie** movie,int*  peliculasCargadas,int *capacidadTotalPeliculas, int* cantidadPunteros);

/**
 *  Agrega una pelicula al archivo binario
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 */
int agregarDatosPelicula(EMovie** movie,int* peliculasCargadas, int* capacidadTotalPeliculas);

/**
 *  Disminuye el valor de peliculas cargadas en 1 y hace un swap entre el puntero a la pelicula a 'eliminar' y la ultima
 *  a modo de procesar lo menos posible.
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param opcionPelicula es un numero de referencia(indice +1) para encontrar una película
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 */
void comprimirArrayMovies(EMovie** movie,int* peliculasCargadas, int opcionPelicula,int* capacidadTotalPeliculas);

/**
 *  Amplia el espacio reservado para agregar peliculas
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 *  @param cantidadPunteros cantidad de punteros disponibles
 */
void ampliacionMemoria(EMovie** movie,int  peliculasCargadas,int* capacidadTotalPeliculas,int* cantidadPunteros);

