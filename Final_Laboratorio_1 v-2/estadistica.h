typedef struct{
    char tema_masEscuchado[100];
    int cantidadEscuchas;
    char** tema_masEscuchadoPorNacionalidad;
    int* cantidadEscuchasPorNacionalidad;
    char autor_masReproducciones[100];
    int cantReproduccionesAutor;
    char autor_conMasTemas[100];
    int cantTemasAutor;
}Estadistica;
