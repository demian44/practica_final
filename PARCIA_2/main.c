#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main()
{
    ArrayList* listaDestinatarios=al_newArrayList();
    ArrayList* listaNegra=al_newArrayList();
    menuPrincipalMercadoLibre(listaDestinatarios,listaNegra);
    return 0;
}
