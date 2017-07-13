#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct{
    char titulo[100];
    char genero[100];
    char duracion[5];
    char descripcion[600];
    char puntaje[4];
    char linkImagen[250];
}EMovie;

/**
 *  Agrega una pelicula al archivo binario
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 *  @param cantidadPunteros cantidad de punteros disponibles
 */
void agregarPelicula(EMovie** movie,int*  peliculasCargadas,int* capacidadTotalPeliculas,int* cantidadPunteros);


/**
 *  Borra una pelicula del archivo binario
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 *  @param cantidadPunteros cantidad de punteros disponibles
 */
void borrarPelicula(EMovie** movie, int* peliculasCargadas,int* capacidadTotalPeliculasint,int* cantidadPunteros);

/**
 *  Edita una pelicula del archivo binario
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 *  @param capacidadTotalPeliculas espacio reservado para guardar peliculas
 */
void modificarDatosPelicula(EMovie** movie, int* peliculasCargadas,int* capacidadTotalPeliculas);

/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 *  @param movie puntero a punteros de estructura EMovie a ser agregada al archivo
 *  @param peliculasCargadas cantidad de peliculas cargadas hasta el momento
 */
void imprimirArchivo(EMovie** movie,int peliculasCargadas);



#endif // FUNCIONES_H_INCLUDED
