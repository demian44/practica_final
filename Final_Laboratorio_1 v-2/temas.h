#include <stdio.h>
#include "ArrayList.h"
typedef struct
{
    int id;
    char nombre[40];
    char artista[40];
}Tema;

void cargarTemas(ArrayList* tem_list);
int ordenarTemas(void* auxA, void* auxB);
void ordenarListaTemas(ArrayList*tList_Ordenado);
void mostrarTemas();
void imprimirTema(int i,ArrayList* lista);
