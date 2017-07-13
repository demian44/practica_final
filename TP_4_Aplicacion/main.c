#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "ArrayList.h"
#include "menus.h"
int main()
{
    ArrayList* lista_Personas = al_newArrayList();
    ArrayList* lista_Productos = al_newArrayList();
    ArrayList* productos_Destacados=al_newArrayList();
    menuPrincipalMercadoLibre(lista_Personas,lista_Productos,productos_Destacados);
    return 0;
}
