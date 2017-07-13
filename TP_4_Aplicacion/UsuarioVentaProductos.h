#include <stdlib.h>
#include <string.h>
#include "validacion.h"
#include "carga.h"
#include "ArrayList.h"

typedef struct
{
    char nombre[50];
    char pasword[50];
    int promCalific;
    int cantCalifc;
    int id;
    int isEmpty;
} E_Usuario;

typedef struct
{
    char nombreProducto[150];
    int precio;
    int id;
    int idUsuario;
    int stock;
    int vendidos;
    int isDestacado;
    int categoria;
} E_Productos;

typedef struct
{
    ArrayList* idUp;
    ArrayList* nameUp;
    ArrayList* idUserUpProduct;
    ArrayList* nameProduct;
    ArrayList* Electronica;
    ArrayList* Deportes;
    ArrayList* otros;

} E_Listas_Ordenadas;

int alta (ArrayList* lista_Usuarios,int* generadorId,E_Listas_Ordenadas* listas_Ordenadas);
void inicializar (ArrayList* lista_Usuarios, int*i);
void inicializarListas(E_Listas_Ordenadas* ELista);
void ordenarUsuario(ArrayList* lista_Usuarios,int(*pCompare)(void*,void*));
int compararPorId(void* usuarioA,void* usuarioB);
int compararPorNombre(void* usuarioA,void* usuarioB);
int obtenerIndicePorId(ArrayList* lista_Usuarios,int generadorId,char* mensaje);
void nuevaPublicacion(ArrayList* lista_Usuarios,ArrayList* lista_Productos,int* generadorIdProducto,int generadorId,E_Listas_Ordenadas* lista_Ordenada);
void printProducto (ArrayList* lista_Producto, int index);
void inicializarProducto (ArrayList* lista_Productos,E_Listas_Ordenadas* listasOrdenadas, int*generadorIdProducto,char* name);
void imprimirLista(ArrayList*lista);
void bajaUsuario(ArrayList* lista_Usuarios,E_Listas_Ordenadas* listasOrdenadas,int generadorId, ArrayList* lista_Productos);
void* generarListaUsuariosOrdenada(ArrayList* lista_Usuarios,int (*fComp)(void*,void*));
void sobreEscribirArchivo(ArrayList* lista,int size,char* nombre);
void insertarEnListaOrdenada(ArrayList* lista,E_Usuario* usuario,int (*fComp)(void*,void*));
void actualizarArchivoBinario(void* elemento,char* nombreArchivo,int size);
ArrayList* actualizarListaOrdenada(ArrayList* listasOrdenadas,ArrayList* listaUsuarios,int(*fComp)(void*,void*));
void actualizarTodasListasOrdenadas(E_Listas_Ordenadas* listasOrdenadas,ArrayList* lista_Usuarios);
void imprimirListaProductos(ArrayList* lista_Productos);
void agregarProductoDestacado(ArrayList* productos_Destacados,ArrayList* listaProductos,int index);
void destacarProducto(ArrayList* productos_Destacados,ArrayList*listaProductos);
int destacarProductoInicial(int* isDestacado);
int elegirCategoria(E_Productos* producto,E_Listas_Ordenadas* listas_Ordenadas);
int filtrarCategoria(void* auxProducto,int argu);
int indicePorIde(ArrayList* lista_Usuarios,int id);
int seleccionarCategoria(void);
int comprar(ArrayList* lista_Producto,ArrayList* lista_Usuario);
void nuevaCompra(ArrayList* lista_Usuarios,E_Listas_Ordenadas* listasOrdenadas);
void actualizarProductoEnArchivo(E_Productos* producto);
void actualizarusUarioEnArchivo(E_Usuario* Usuario);
void eliminarProductosAsociados(int id, ArrayList* lista_Productos);
void actualizarListasOrdenadasProductos(E_Listas_Ordenadas* listasOrdenadas,ArrayList* lista_Productos);
void bajaProducto(ArrayList* lista_Usuarios,E_Listas_Ordenadas* listasOrdenadas,int generadorId, ArrayList* lista_Productos);
int mismoIdProducto(void* auxProducto,int id);
ArrayList* generarListaProductosAsociados(int id, ArrayList* lista_Productos);
int borrarPorIdProducto(ArrayList* lista_Producto,int id);
void agregarProductoListaOrdenada(ArrayList* listaAgrupada,E_Productos* producto);
void actualizarListaOrdenadaProductos(E_Listas_Ordenadas* lista_Ordenada, E_Productos* producto,int lista);
