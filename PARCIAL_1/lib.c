#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "validaciones.h"
#include "cargaYEdicion.h"
#include "edicionArrays.h"
#include "busqueda.h"
/**
 * \brief Carga y valida datos ingresados por usuario
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param Id pasado por parametro
 */
int alta (E_Usuario listaPersonas[],int cantidad,int id,int* generadorId)
{
    int i;
    int retorno=0;
    int indiceVacio;
    char auxNombre[50];
    char auxpasword[50];
    indiceVacio=obtenerEspacioLibre(listaPersonas,cantidad,1);
    if(indiceVacio!=-1)
    {
        retorno = ingresarSoloLetras(auxNombre,"\nIngrse su nombre: ","\nCaracteres invalidos para un nombre.\n");
        if(retorno)
        {
            getString("\nIngrse su pasword: ",auxpasword);
        }
    }
    if(retorno==1)
    {
        strcpy(listaPersonas[indiceVacio].nombre,auxNombre);
        strcpy(listaPersonas[indiceVacio].pasword,auxpasword);
        for(i=0; i<50; i++)
        {
            listaPersonas[indiceVacio].calificacion[i]=-1;
        }
        listaPersonas[indiceVacio].id=id;
        listaPersonas[indiceVacio].isEmpty=0;
        (*generadorId)++;

    }
    return retorno;
}
/**
 * \brief Busca por indice y realiza baja lógica
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param mensaje para el usuario
 */
void baja (E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[])
{
    int indiceId;
    char continuar;
    int cargaExitosa;
    int listaProductosUsuario[cantidadProductos];
    char id[4];
    int i;
    do
    {
        if(cargarNumero(id,mensaje,mensajeError,0,99))
        {
            indiceId = buscarPorIdUsuario(listaPersonas,cantidad,atoi(id));
            if(indiceId!=-1)
            {
                buscarProductoPorIdUsuario(listaProductos,1000,atoi(id),listaProductosUsuario);
                for(i=0; i<1000; i++)
                {
                    if(listaProductosUsuario[i]==-1)
                    {
                        break;
                    }
                    listaProductos[listaProductosUsuario[i]].isEmpty=1;
                }
                listaPersonas[indiceId].isEmpty=1;
                cargaExitosa =1;

            }
            else
            {
                printf("%s",mensajeNoEncontrado);
                continuar=getChar("\nDesea continuar? s/n");
            }
        }
    }
    while(cargaExitosa==0 && continuar=='s');
}
/**
 * \brief Busca por indice y realiza carga de datos a modificar
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param mensaje para el usuario
 */
void modificar (E_Usuario listaPersonas[],int cantidad,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[])
{
    int indiceId;
    int cargaExitosa;
    char auxNombre[50];
    char auxpasword[50];
    char opcion;
    if((indiceId =obtenerIndicePorId(listaPersonas,cantidad,mensaje,mensajeError,mensajeNoEncontrado))!=-1)
    {
        opcion=getChar("Ingrese la opcion a modificar, \n\n 1-Nomrbre.\n 2-pasword.\n");
        switch(opcion)
        {
        case '1':
            cargaExitosa = ingresarSoloLetras(auxNombre,"\nNombre: ","\nCaracteres invalidos para un nombre.\n");
            if(cargaExitosa==1)
            {
                strcpy(listaPersonas[indiceId].nombre,auxNombre);
            }
            break;
        case '2':
            cargaExitosa = ingresarSoloLetras(auxpasword,"\nPasword: ","\nCaracteres invalidos para un pasword.\n");
            if(cargaExitosa==1)
            {
                strcpy(listaPersonas[indiceId].pasword,auxpasword);
            }
            break;
        default :
            printf("Error. Opcion incorrecta.");
            break;
        }
    }


}
/**
 * \brief Busca por indice activo en dos estructuras y crea una entrada para llamadas
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param array de datos a comparar
 * \param cantidad de posiciones que tiene el array.
 * \param dato pasado como parametro
 */
void nuevaPublicacion (E_Usuario listaPersonas[],int cantidad, E_Productos listaProductos[], int cantidadLlamas,int id)
{
    char auxiliarPrecio[10];
    char auxiliarStock[10];
    int indiceId;
    int indiceVacio;
    int cargaExitosa;
    indiceVacio=obtenerEspacioLibreProductos(listaProductos,cantidadLlamas,1);
    if(indiceVacio!=-1)
    {
        indiceId = obtenerIndicePorId(listaPersonas,cantidad,"Ingrese ID de usuario","ID invalido","ID no encontrado");
    }
    if(indiceId!=-1)
    {

        getString("\nIngrese el nombre del Producto: ",listaProductos[indiceVacio].nombreProducto);
        if(cargarNumero(auxiliarPrecio,"Ingrese el precio","Precio invalido",0,1000000))
        {
            listaProductos[indiceVacio].precio=(atoi(auxiliarPrecio));
            cargaExitosa=1;
        }
        else
        {
            cargaExitosa=0;
        }
        if(cargaExitosa==1)
        {
            if(getNumerosChar(auxiliarStock,"Ingrese stock"))
            {
                listaProductos[indiceVacio].stock=(atoi(auxiliarStock));
                cargaExitosa=1;
            }
            else
            {
                cargaExitosa=0;
            }
        }


        if(cargaExitosa==1)
        {
            listaProductos[indiceVacio].idUsuario=listaPersonas[indiceId].id;
            listaProductos[indiceVacio].id=id;
            listaProductos[indiceVacio].isEmpty=0;
        }


    };
}


void modificarPublicacion (E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[])
{
    int indiceId;
    char continuar;
    char auxiliarPrecio[20];
    char auxiliarStock[20];
    char opcion;
    char auxiliarId[20];
    int listaProductosUsuario[cantidadProductos];
    char id[4];
    int i;
    do
    {
        if(cargarNumero(id,mensaje,mensajeError,0,99))
        {
            indiceId = buscarPorIdUsuario(listaPersonas,cantidad,atoi(id));
            if(indiceId!=-1)
            {
                buscarProductoPorIdUsuario(listaProductos,1000,atoi(id),listaProductosUsuario);
                for(i=0; i<1000; i++)
                {
                    if(listaProductosUsuario[i]==-1)
                    {
                        break;
                    }
                    printf("-Nombre: %s\n-Precio: %.2f\n-ID: %d\n-Stock: %d\n-Cantidad vendida: %d\n\n",listaProductos[listaProductosUsuario[i]].nombreProducto,listaProductos[listaProductosUsuario[i]].precio,listaProductos[listaProductosUsuario[i]].id,listaProductos[listaProductosUsuario[i]].stock,listaProductos[listaProductosUsuario[i]].vendidos);
                }
                cargarNumero(auxiliarId,"Ingrese ID del producto a modificar:","Error",0,1000);
                indiceId=buscarPorIdProductos(listaProductos,cantidadProductos,atoi(auxiliarId));
                opcion=getChar("Ingrese la opcion a modificar.\n\n1-Precio\n2-Stock\n");
                switch(opcion)
                {
                case '1':
                    if(cargarNumero(auxiliarPrecio,"\nNuevo precio: ","Error",0,1000000))
                    {
                        listaProductos[indiceId].precio=(atoi(auxiliarPrecio));
                    }
                    break;
                case '2':
                    if(cargarNumero(auxiliarStock,"\nNuevo Stock: ","Error",0,1000))
                    {
                        listaProductos[indiceId].stock=(atoi(auxiliarStock));
                    }
                default:
                    printf("Opcion incorrecta.");
                    break;
                }
            }
            else
            {
                printf("%s",mensajeNoEncontrado);
                continuar=getChar("\nDesea continuar? s/n");
            }
        }
    }
    while(/*cargaExitosa==0 &&*/ continuar=='s');
}

void cancelarPublicacion (E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[])
{
    int indiceId;
    char continuar;
    char auxiliarId[20];
    int listaProductosUsuario[cantidadProductos];
    char id[4];
    int i;
    do
    {
        if(cargarNumero(id,mensaje,mensajeError,0,99))
        {
            indiceId = buscarPorIdUsuario(listaPersonas,cantidad,atoi(id));
            if(indiceId!=-1)
            {
                buscarProductoPorIdUsuario(listaProductos,1000,atoi(id),listaProductosUsuario);
                for(i=0; i<1000; i++)
                {
                    if(listaProductosUsuario[i]==-1)
                    {
                        break;
                    }
                    printf("-Nombre: %s\n-Precio: %.2f\n-ID: %d\n-Stock: %d\n-Cantidad vendida: %d\n\n",listaProductos[listaProductosUsuario[i]].nombreProducto,listaProductos[listaProductosUsuario[i]].precio,listaProductos[listaProductosUsuario[i]].id,listaProductos[listaProductosUsuario[i]].stock,listaProductos[listaProductosUsuario[i]].vendidos);
                }
                cargarNumero(auxiliarId,"Ingrese ID del producto a modificar:","Error",0,1000);
                indiceId=buscarPorIdProductos(listaProductos,cantidadProductos,atoi(auxiliarId));
                listaProductos[indiceId].isEmpty=1;
            }
            else
            {
                printf("%s",mensajeNoEncontrado);
                continuar=getChar("\nDesea continuar? s/n");
            }
        }
    }
    while(continuar=='s');
}
/**
 * \brief buscar un producto por ID de usuario y luedo ID de producto
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 */
void nuevaCompra(E_Usuario listaUsuarios[],int cantidadUsuarios,E_Productos listaProductos[], int cantidadProductos)
{
    int indiceId;
    char continuar;
    char auxiliarCalificacion[20];
    char id[4];
    int i;
    do
    {
        if(cargarNumero(id,"Ingrese el ID del producto a comprar","Error",0,99))
        {
            indiceId = buscarPorIdProductos(listaProductos,cantidadProductos,atoi(id));
        }
        else
        {
            break;
        }

        if(indiceId!=-1 && listaProductos[indiceId].stock>0)
        {
            listaProductos[indiceId].stock--;
            if(cargarNumero(auxiliarCalificacion,"Califique al usuario","Error",0,10))
            {
                indiceId=buscarPorIdUsuario(listaUsuarios,cantidadUsuarios,(listaProductos[indiceId].idUsuario));
                for(i=0; i<10; i++)
                {
                    if(listaUsuarios[indiceId].calificacion[i]==-1)
                    {
                        listaUsuarios[indiceId].calificacion[i]=atoi(auxiliarCalificacion);
                        break;
                    }
                }
            }
        }
        else
        {
            printf("ID no encontrado o producto sin stock. \n\n");
            continuar=getChar("\nDesea continuar? s/n");
        }
    }
    while(continuar=='s');
}


/**
 * \brief Imprime por pantalla los afiliados con más llamadas realizadas
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param array de datos a comparar
 * \param cantidad de posiciones que tiene el array.
 * \param array con indices que posean mayor cantidad de llamadas realizadas
 */
void informarAfiliadosMasProductos(E_Productos listaProductos[],int cantProductos,E_Usuario listaPersonas[],int cantidad,int afiliadosConMasProductos[])
{
    int i;
    if(usuarioConMayorCantidadDeProductos(listaProductos,cantProductos,listaPersonas,cantidad,afiliadosConMasProductos))
    {

        printf("Afiliados con mayor cantidad e llamadas: \n\n");
        for(i=0; i<cantidad && afiliadosConMasProductos[i]!=-1; i++)
        {
            printf("-%s ",listaPersonas[(afiliadosConMasProductos[i])].nombre);
            printf("%s\n",listaPersonas[(afiliadosConMasProductos[i])].pasword);

        }
    }

}
/**
 * \brief Imprime los nombreProductos más consultados
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param array de datos
 */
void informarMotivosMasRepetidos(E_Productos listaProductos[],int canttidadProductos,EMotivo nombreProducto[])
{
    int i;
    int listaMotivosMasRepetidos[3];
    nombreProductoMasRepetido(listaProductos,canttidadProductos,nombreProducto,listaMotivosMasRepetidos);
    for(i=0; i<3; i++)
    {
        if(listaMotivosMasRepetidos[i]==1)
        {
            printf("\n-Motivo mas recurrente: %s\n",nombreProducto[i].tipo);
        }
    }
}
/**
 * \brief Imprime una lista ordenada por nombre y pasword
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 */
void informarAfiliadosPorNombreypasword(E_Usuario listaPersonas[],int cantidad)
{
    int i;
    ordenarPorNombreYpasword(listaPersonas,cantidad);
    for(i=0; i<cantidad; i++)
    {
        if(listaPersonas[i].isEmpty==0)
        {
            printf("Nombre %s --pasword %s\n\n",listaPersonas[i].nombre,listaPersonas[i].pasword);
        }
    }
}

void listarPublicacionesDeUsuarios(E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[])
{
    int indiceId;
    char continuar;
    int listaProductosUsuario[cantidadProductos];
    char id[4];
    int i;
    system("cls");
    do
    {
        if(cargarNumero(id,mensaje,mensajeError,0,99))
        {
            indiceId = buscarPorIdUsuario(listaPersonas,cantidad,atoi(id));
            if(indiceId!=-1)
            {
                buscarProductoPorIdUsuario(listaProductos,1000,atoi(id),listaProductosUsuario);
                for(i=0; i<1000; i++)
                {
                    if(listaProductosUsuario[i]!=-1)
                    {
                        printf("Producto %d:\n",i+1);
                        printf("-Nombre: %s\n-Precio: %.2f\n-ID: %d\n-Stock: %d\n-Cantidad vendida: %d\n\n",listaProductos[listaProductosUsuario[i]].nombreProducto,listaProductos[listaProductosUsuario[i]].precio,listaProductos[listaProductosUsuario[i]].id,listaProductos[listaProductosUsuario[i]].stock,listaProductos[listaProductosUsuario[i]].vendidos);
                    }
                    else
                    {
                        break;
                    }

                }
            }
            else
            {
                printf("%s",mensajeNoEncontrado);
                continuar=getChar("\nDesea continuar? s/n");
            }
        }
    }
    while(continuar=='s');
    cualquierTeclaContinnuar();
}

void hardCode(E_Usuario* listaPersonas,E_Productos* listaProductos)
{
    strcpy(listaPersonas->nombre,"ZZ");
    strcpy(listaPersonas->pasword,"BBB");
    listaPersonas->isEmpty=0;
    listaPersonas->id=4;

    strcpy((listaPersonas+1)->nombre,"ZZ");
    strcpy((listaPersonas+1)->pasword,"AAA");
    (listaPersonas+1)->isEmpty=0;
    (listaPersonas+1)->id=3;
    (listaPersonas+1)->calificacion[0]=8;
    (listaPersonas+1)->calificacion[1]=2;
    (listaPersonas+1)->calificacion[2]=-1;

    strcpy((listaPersonas+2)->nombre,"AA");
    strcpy((listaPersonas+2)->pasword,"ZZZ");
    (listaPersonas+2)->isEmpty=0;
    (listaPersonas+2)->id=2;
    (listaPersonas+2)->calificacion[0]=-1;


    strcpy((listaPersonas+3)->nombre,"AA");
    strcpy((listaPersonas+3)->pasword,"SSS");
    (listaPersonas+3)->isEmpty=0;
    (listaPersonas+3)->id=1;
    (listaPersonas+3)->calificacion[0]=5;
    (listaPersonas+3)->calificacion[1]=-1;

    listaProductos->duracion=50;
    listaProductos->id=0;
    listaProductos->idUsuario=0;
    listaProductos->stock=50;
    strcpy(listaProductos->nombreProducto,"Remera");
    listaProductos->precio=40;
    listaProductos->isEmpty=0;

    (listaProductos+1)->id=1;
    (listaProductos+1)->idUsuario=0;
    strcpy((listaProductos+1)->nombreProducto,"Xbox");
    (listaProductos+1)->precio=45;
    (listaProductos+1)->isEmpty=0;
    (listaProductos+1)->stock=20;

    (listaProductos+2)->duracion=40;
    (listaProductos+2)->id=0;
    (listaProductos+2)->stock=0;
    (listaProductos+2)->idUsuario=1;
    strcpy((listaProductos+2)->nombreProducto,"GameBoy");
    (listaProductos+2)->precio=58;
    (listaProductos+2)->isEmpty=0;


    (listaProductos+3)->duracion=45;
    (listaProductos+3)->id=0;
    (listaProductos+3)->stock=0;
    (listaProductos+3)->idUsuario=2;
    strcpy((listaProductos+3)->nombreProducto,"Play");
    (listaProductos+3)->precio=77;
    (listaProductos+3)->isEmpty=0;
}


void mostrarListaUsuarioConProducto(E_Usuario* listaPersonas,E_Productos* listaProductos,int cantidad,int cantidadProductos)
{
    int i,j=0;
    printf("Nombre\n\n");
    for(i=0; i<cantidad; i++)
    {
        if(((listaPersonas+i)->isEmpty)==0)
        {
            printf("%s \nProductos\n",(listaPersonas+i)->nombre);
            for(j=0; j<cantidadProductos; j++)
            {
                if(((((listaProductos+j))->isEmpty)==0)&&(((listaProductos+j))->idUsuario)==listaPersonas[i].id)
                    printf("%s, ",((listaProductos+j))->nombreProducto);
            }
            printf(".\n");
        }
    }
    cualquierTeclaContinnuar();
}

void mostrarListaProductosPorIdUsuario(E_Productos* listaProductos,int cantidadProductos,int idUsuario)
{
    int j;
    for(j=0; j<cantidadProductos; j++)
    {
        if(((((listaProductos+j))->isEmpty)==0)&&(((listaProductos+j))->idUsuario)==idUsuario)
        {
            printf("%s \n",((listaProductos+j))->nombreProducto);
        }
    }
    printf("\n");
}

void mostrarProductoConInformacion(E_Productos* listaProductos,E_Usuario* listaPersonas,int cantidadProductos)
{
    int i,indiceId;
    system("cls");
    printf("Producto\tID\tPrecio\tVentas\tStock\tUser\n\n\n");
    for(i=0; i<cantidadProductos; i++)
    {

        if(listaProductos[i].isEmpty==0)
        {
            printf("%s\t\t",listaProductos[i].nombreProducto);
            printf("%d\t",listaProductos[i].id);
            printf("%.2f\t",listaProductos[i].precio);
            printf("%d\t",listaProductos[i].vendidos);
            printf("%d\t",listaProductos[i].stock);
            indiceId=buscarPorIdUsuario(listaPersonas,cantidadProductos,listaProductos[i].idUsuario);
            printf("%s\n\n",listaPersonas[indiceId].nombre);
        }
    }
    printf("\n\n");
    cualquierTeclaContinnuar();
}


void listarUsuarios(E_Usuario* listaPersonas,int cantidad)
{
    int i,j,contador;
    float acumuladorCalificaciones;
    float promedio;
    printf("Nombre \t CalificacionPromedio\n\n");
    for(i=0; i<cantidad; i++)
    {
        if(listaPersonas[i].isEmpty==0)
        {
            printf("%s \t",listaPersonas[i].nombre);
            acumuladorCalificaciones=0;
            contador=0;
            for(j=0; j<10; j++)
            {
                if(listaPersonas[i].calificacion[j]!=-1)
                {
                    acumuladorCalificaciones=listaPersonas[i].calificacion[j]+acumuladorCalificaciones;
                    contador++;
                }
                else
                {
                    break;
                }

            }
            if(contador>0)
            {
                promedio=acumuladorCalificaciones/contador;
                printf(" %.2f.               \t",promedio);
            }
            else
            {
                printf(" SIN CALIFICACIONES. \t");
            }
            printf("ID: %d \n",((listaPersonas+i))->id);


        }
    }
    cualquierTeclaContinnuar();
}

void ordenarVectoresdeUsuarios(E_Usuario* listaPersonas,int cantidad)
{
    int i;
    E_Usuario* punterosPersonas[cantidad];

    for(i=0;i<cantidad;i++)
    {
    (*(punterosPersonas+i))=(listaPersonas+i);
    }
    ordenarPorIdPunteros(punterosPersonas,cantidad);
    for(i=0;i<cantidad;i++)
    {
        if(!((*(punterosPersonas+i))->isEmpty))
            printf("Nombre: %s - ID: %d\n",(*((punterosPersonas+i)))->nombre,(*((punterosPersonas+i)))->id);
    }
    cualquierTeclaContinnuar();
}
