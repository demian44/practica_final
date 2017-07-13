#include "menus.h"
#include "conio.h"


void printMenu(void)
{
    system("cls");
    printf("VENTAS ONLINE.\n\n");
    printf("1- ALTA DEL USUARIO.\n");
    printf("2- MOSTRAR LISTA ORDENADA.\n");
    printf("3- NUEVA PUBLICACION.\n");
    printf("4- ELIMINAR USUARIO.\n");
    printf("5- COMPRAR.\n");
    printf("6- CANCELAR PUBLICACION.\n");
    printf("7- COMPRAR PRODUCTO.\n");
    printf("8- LISTAR PUBLICACIONES DE USUARIO.\n");
    printf("9- MODIFICAR DATOS DEL USUARIO.\n");
    printf("10-LISTAR USUARIOS.\n");
    printf("11-OTRACOSA\n");
    printf("12-LISTAR PRODUCTOS.\n");
    printf("13-Salir\n");
}

void menuPrincipalMercadoLibre(ArrayList* lista_Usuarios, ArrayList* lista_Productos,ArrayList* productos_Destacados)
{
    E_Listas_Ordenadas listasOrdenadas;
    int generadorId=0;
    int generadorIdProducto=0;
    int opcion=0;
    char seguir='s';
    inicializarListas(&listasOrdenadas);
    inicializar(lista_Usuarios,&generadorId);
    inicializarProducto(lista_Productos,&listasOrdenadas,&generadorIdProducto,"Productos.bin");
    actualizarTodasListasOrdenadas(&listasOrdenadas,lista_Usuarios);
    do
    {
        fflush(stdin);
        printMenu();
        opcion=getInt("\nOpcion: ");
        switch(opcion)
        {
        case 1:
            alta(lista_Usuarios,&generadorId,&listasOrdenadas);
            break;
        case 2:
            menuListasOrdenadas(lista_Usuarios,&listasOrdenadas);
            break;
        case 3:
            nuevaPublicacion(lista_Usuarios,lista_Productos,&generadorIdProducto,generadorId,&listasOrdenadas);
            break;
        case 4:
            bajaUsuario(lista_Usuarios,&listasOrdenadas,generadorId,lista_Productos);
            break;
        case 5:
            nuevaCompra(lista_Usuarios,&listasOrdenadas);
            break;
        case 6:
            bajaProducto(lista_Usuarios,&listasOrdenadas,generadorId,lista_Productos);
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            imprimirLista(lista_Usuarios);
            getch();
            break;
        case 12:
            system("cls");
            printf("\n*********************************************************");
            printf("\nELECTRONICA: ");
            imprimirListaProductos(listasOrdenadas.Electronica);
            printf("\n*********************************************************");
            printf("\nDEPORTES: ");
            imprimirListaProductos(listasOrdenadas.Deportes);
            printf("\n*********************************************************");
            printf("\nOTROS: ");
            imprimirListaProductos(listasOrdenadas.otros);
            getch();
            break;
        default:
            seguir='n';
            break;
        }
    }
    while(seguir=='s' || seguir == 'S');
}


void menuListasOrdenadas(ArrayList* lista_Usuarios,E_Listas_Ordenadas* listasOrdenadas)
{
    char opcion='0';
    char seguir='s';
    while(seguir=='s' || seguir == 'S')
    {
        system("cls");
        printf("VENTAS ONLINE->Ordenar Lista.\n\n");
        printf("1- Mostrar Usuarios por ID.\n");
        printf("2- Mostrar Usuarios por nombre.\n");
        printf("3- Mostrar Productos por ID de usuario.\n");
        printf("4- Mostrar Productos por Nombre.\n");
        printf("5- Salir.\n");
        opcion=getChar("\nOpcion: ");
        switch(opcion)
        {
        case '1':
            imprimirLista(listasOrdenadas->idUp);
            getch();
            break;
        case '2':
            imprimirLista(listasOrdenadas->nameUp);
            getch();
            break;
        case '3':

            break;
        case '4':
            break;
        case '5':
            seguir='n';
            break;
        default:
            printf("OPCION INCORRECTA!!");
            getch();
            break;

        }
    }

}


