#include "UsuarioVentaProductos.h"
#include "conio.h"
#define ELECTRONICA 1
#define DEPORTES 2
#define OTROS 3

/**
 * \brief Carga y valida datos ingresados por usuario
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param Id pasado por parametro
 */
int alta (ArrayList* lista_Usuarios,int* generadorId,E_Listas_Ordenadas* listasOrdenadas)
{
    int retorno=-1;
    char auxNombre[50], auxpasword[50];
    E_Usuario* auxiliarUsuario;
    if(lista_Usuarios!=NULL)
    {
        auxiliarUsuario=(E_Usuario*)malloc(sizeof(E_Usuario));
        if(auxiliarUsuario==NULL)
            return retorno;
        retorno = ingresarSoloLetras(auxNombre,"\nIngrse su nombre: ","\nCaracteres invalidos para un nombre.\n");
        if(retorno)
            getString("\nIngrse su pasword: ",auxpasword);
        if(retorno==1)
        {
            strcpy((auxiliarUsuario)->nombre,auxNombre);
            strcpy((auxiliarUsuario)->pasword,auxpasword);
            (auxiliarUsuario)->promCalific=0;
            (auxiliarUsuario)->cantCalifc=0;
            (auxiliarUsuario)->id=*generadorId;
            (auxiliarUsuario)->isEmpty=0;
            al_add(lista_Usuarios,(void*)auxiliarUsuario);
            (*generadorId)++;
            actualizarArchivoBinario(auxiliarUsuario,"Usuarios_Venta.bin",sizeof(E_Usuario));
            actualizarTodasListasOrdenadas(listasOrdenadas,lista_Usuarios);
        }
    }
    return retorno;
}

void inicializar (ArrayList* lista_Usuarios, int*generadorIdUsuario)
{
    FILE* pFile=NULL;
    pFile=fopen("Usuarios_Venta.bin","rb");
    if(pFile==NULL)
        return;
    E_Usuario* usuario;

    do
    {
        usuario=(E_Usuario*)malloc(sizeof(E_Usuario));
        if(0>=fread(usuario,sizeof(E_Usuario),1,pFile))
        {
            free(usuario);
            break;
        }
        printf("\nNombre: %s, Pasword: %s",usuario->nombre,usuario->pasword);
        al_add(lista_Usuarios,(void*)usuario);
        (*generadorIdUsuario)=maximo((*generadorIdUsuario), usuario->id+1);
    }
    while(1);
    fclose(pFile);
}

void inicializarProducto (ArrayList* lista_Productos,E_Listas_Ordenadas* listasOrdenadas, int*generadorIdProducto,char* name)
{
    FILE* pFile=NULL;
    pFile=fopen(name,"rb");
    if(pFile==NULL)
        return;
    E_Productos* producto;

    do
    {
        producto=(E_Productos*)malloc(sizeof(E_Productos));
        if(0>=fread(producto,sizeof(E_Productos),1,pFile))
        {
            free(producto);
            break;
        }
        al_add(lista_Productos,(void*)producto);
        (*generadorIdProducto)=maximo((*generadorIdProducto), producto->id+1);

    }
    while(1);
    actualizarListasOrdenadasProductos(listasOrdenadas,lista_Productos);


    fclose(pFile);
}

void actualizarListasOrdenadasProductos(E_Listas_Ordenadas* listasOrdenadas,ArrayList* lista_Productos)
{
    listasOrdenadas->Electronica=lista_Productos->filter(lista_Productos,filtrarCategoria,ELECTRONICA);
    listasOrdenadas->Deportes=lista_Productos->filter(lista_Productos,filtrarCategoria,DEPORTES);
    listasOrdenadas->otros=lista_Productos->filter(lista_Productos,filtrarCategoria,OTROS);
}


void inicializarListas(E_Listas_Ordenadas* ELista)
{
    ELista->idUp=al_newArrayList();
    ELista->nameUp=al_newArrayList();
    ELista->idUserUpProduct=al_newArrayList();
    ELista->nameProduct=al_newArrayList();
    ELista->Deportes=al_newArrayList();
    ELista->otros=al_newArrayList();
    ELista->Electronica=al_newArrayList();
}

void ordenarUsuario(ArrayList* lista_Usuarios,int(*pCompare)(void*,void*))
{
    lista_Usuarios->sort(lista_Usuarios,pCompare,1);
}
void ordenarUsuarioPorNombreUsuario(ArrayList* lista_Usuarios)
{
    al_sort(lista_Usuarios,compararPorNombre,1);
}

int compararPorId(void* usuarioA,void* usuarioB)
{
    int auxReturn=0;
    if(usuarioA!=NULL && usuarioB != NULL)
    {
        E_Usuario* auxiliarUsuairoA=(E_Usuario*)usuarioA;
        E_Usuario* auxiliarUsuairoB=(E_Usuario*)usuarioB;
        if((auxiliarUsuairoA->id)>(auxiliarUsuairoB->id))
            auxReturn=1;
        else if(auxiliarUsuairoA->id<auxiliarUsuairoB->id)
            auxReturn=-1;
    }
    return auxReturn;
}



int compararPorNombre(void* usuarioA,void* usuarioB)
{
    int auxReturn=0;
    if(usuarioA!=NULL && usuarioB != NULL)
    {
        E_Usuario* auxiliarUsuairoA=(E_Usuario*)usuarioA;
        E_Usuario* auxiliarUsuairoB=(E_Usuario*)usuarioB;
        if((strcmp((auxiliarUsuairoA->nombre),(auxiliarUsuairoB->nombre)))>0)
            auxReturn=1;
        if((strcmp((auxiliarUsuairoA->nombre),(auxiliarUsuairoB->nombre)))<0)
            auxReturn=-1;
    }
    return auxReturn;
}

/**
 * \brief Busca por indice activo en dos estructuras y crea una entrada para llamadas
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 * \param array de datos a comparar
 * \param cantidad de posiciones que tiene el array.
 * \param dato pasado como parametro
 */
void nuevaPublicacion(ArrayList* lista_Usuarios,ArrayList* lista_Productos,int* generadorIdProducto,int generadorId,E_Listas_Ordenadas* lista_Ordenada)
{
    char auxiliarPrecio[10];
    char auxiliarStock[10];
    E_Productos* producto=(E_Productos*)malloc(sizeof(E_Productos));
    E_Usuario* usuario;
    int indiceId;
    int cargaExitosa;
    indiceId =obtenerIndicePorId(lista_Usuarios,generadorId,"Ingresar ID de usuario: ");
    if(indiceId!=-1)
    {
        getTexto("\nIngrese el nombre del Producto: ",producto->nombreProducto,"150");
        if(cargarNumero(auxiliarPrecio,"Ingrese el precio: ","Precio invalido",0,1000000))
        {
            producto->precio=(atoi(auxiliarPrecio));
            cargaExitosa=1;
        }
        else
        {
            cargaExitosa=0;
        }
        if(cargaExitosa==1)
        {
            if(getNumerosChar(auxiliarStock,"Ingrese stock: "))
            {
                producto->stock=(atoi(auxiliarStock));
            }
            else
                cargaExitosa=0;
        }
        if(cargaExitosa==1)
            destacarProductoInicial(&producto->isDestacado);
        if(cargaExitosa==1)
        {
            usuario=lista_Usuarios->get(lista_Usuarios,indiceId);
            if(usuario!=NULL)
            {
                producto->idUsuario=usuario->id;
                producto->id=(*generadorIdProducto);
                (*generadorIdProducto)++;
                cargaExitosa=elegirCategoria(producto,lista_Ordenada);
                actualizarArchivoBinario(producto,"Productos.bin",sizeof(E_Productos));
                lista_Productos->add(lista_Productos,producto);
            }
        }
    }
}

int obtenerIndicePorId(ArrayList* lista_Usuarios,int generadorId,char* mensaje)
{
    int auxReturn=-1;
    char auxId[10];
    if(cargarNumero(auxId,mensaje,"ID erroneo",0,generadorId))
        auxReturn=indicePorIde(lista_Usuarios,atoi(auxId));

    return auxReturn;
}


int indicePorIde(ArrayList* lista_Usuarios,int id)
{
    E_Usuario* usuario;
    int auxReturn=-1;
    int i;
    for(i=0; i<lista_Usuarios->len(lista_Usuarios); i++)
    {
        usuario=(E_Usuario*)lista_Usuarios->get(lista_Usuarios,i);
        if(usuario->id==id)
        {
            auxReturn=i;
            break;
        }
    }
    return auxReturn;
}



void imprimirLista(ArrayList*lista)
{
    system("cls");
    E_Usuario* usuario;
    int i;
    if(lista!=NULL)
        for(i=0; i<(lista->size); i++)
        {
            printf("\n*************************************************************************");
            usuario=lista->get(lista,i);
            printf("\n Nombre: %s\n  pasword: %s \n  ID: %d Calif. Prom.:%d",usuario->nombre,usuario->pasword,usuario->id,usuario->promCalific);

        }
}


void printProducto (ArrayList* lista_Producto, int index)
{
    if(lista_Producto!=NULL && lista_Producto->len(lista_Producto)>index && index >=0)
    {
        E_Productos* producto;
        producto=(E_Productos*)lista_Producto->get(lista_Producto,index);
        printf("\n%d-%s.\n\tStock: %d\tPrecio: $%d.00\n ",index+1,producto->nombreProducto,producto->stock,producto->precio);
    }
}

void imprimirListaProductos(ArrayList* lista_Productos)
{
    int i;
    if(lista_Productos!=NULL && !lista_Productos->isEmpty(lista_Productos))
    {
        for(i=0; i<lista_Productos->len(lista_Productos); i++)
            printProducto(lista_Productos,i);
    }
    else
        printf("No hay productos publicados.");

}

/**
 * \brief buscar un producto por ID de usuario y luedo ID de producto
 * \param array de datos
 * \param cantidad de posiciones que tiene el array.
 */
void nuevaCompra(ArrayList* lista_Usuarios,E_Listas_Ordenadas* listasOrdenadas)
{
    int categoria=seleccionarCategoria();
    switch(categoria)
    {
    case ELECTRONICA:
        comprar(listasOrdenadas->Electronica,lista_Usuarios);
        break;
    case DEPORTES:
        comprar(listasOrdenadas->Deportes,lista_Usuarios);
        break;
    case OTROS:
        comprar(listasOrdenadas->otros,lista_Usuarios);
        break;
    default:
        printf("\nNo se realizo ninguna compra.");
        break;
    }
}


int seleccionarCategoria(void)
{
    int retorno=0;

    system("cls");
    printf("Indique la categoria: \n\n");
    printf(" 1- Electronica.\n");
    printf(" 2- Deportes.\n");
    printf(" 3- Otros.\n");
    //printf(" 4- Todas las categorías.\n");
    char auxiliar[10];
    if(cargarNumero(auxiliar,"Indice la categoria","Opcion inexistente",1,3))
        retorno=atoi(auxiliar);
    return retorno;
}


int comprar(ArrayList* lista_Producto,ArrayList* lista_Usuario)
{
    int retorno=0;
    int indiceId;
    char auxId[5];
    char auxiliarCalificacion[4];
    E_Productos* producto;
    E_Usuario* usuario;
    char continuar='n';
    imprimirListaProductos(lista_Producto);
    do
    {
        if(cargarNumero(auxId,"Ingrese el producto a comprar","Error",1,lista_Producto->len(lista_Producto)))
        {
            indiceId =atoi(auxId)-1;
        }
        else
            break;

        producto=lista_Producto->get(lista_Producto,indiceId);
        if(producto!=NULL && producto->stock>0)
        {
            printf("\nCompra exitosa, ahora es usted mas pobre.\n");
            producto->stock--;
            actualizarProductoEnArchivo(producto);
            retorno=1;
            if(cargarNumero(auxiliarCalificacion,"\nCalifique al usuario","Error",0,10))
            {
                indiceId=indicePorIde(lista_Usuario,producto->idUsuario);
                usuario=lista_Usuario->get(lista_Usuario,indiceId);
                usuario->cantCalifc=0;
                if(usuario->cantCalifc!=0)
                {
                    usuario->promCalific=((usuario->cantCalifc*usuario->promCalific)+atoi(auxiliarCalificacion))/usuario->cantCalifc;
                    usuario->cantCalifc++;
                    actualizarusUarioEnArchivo(usuario);
                }
                else
                {
                    usuario->promCalific=atoi(auxiliarCalificacion);
                    usuario->cantCalifc=1;
                    actualizarusUarioEnArchivo(usuario);
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
    return retorno;
}


void actualizarProductoEnArchivo(E_Productos* producto)
{
    FILE* pFile;
    int i=0;
    pFile=fopen("Productos.bin","r+b");
    E_Productos* productoEnArchivo;
    while(pFile!=NULL)
    {
        productoEnArchivo=(E_Productos*)malloc(sizeof(E_Productos));
        if(0>=fread(productoEnArchivo,sizeof(E_Productos),1,pFile))
        {
            free(productoEnArchivo);
            productoEnArchivo=NULL;
            break;
        }
        if(productoEnArchivo->id==producto->id);
        break;
        i++;
    }
    if(productoEnArchivo!=NULL)
    {
        fseek(pFile,sizeof(E_Productos)*i,SEEK_SET);
        fwrite(producto,sizeof(E_Productos),1,pFile);

    }

    fclose(pFile);

}

void actualizarusUarioEnArchivo(E_Usuario* Usuario)
{
    FILE* pFile;
    int i=0;
    pFile=fopen("Usuarios_Venta.bin","r+b");
    E_Usuario* usuarioEnArchivo;
    while(pFile!=NULL)
    {
        usuarioEnArchivo=(E_Usuario*)malloc(sizeof(E_Usuario));
        if(0>=fread(usuarioEnArchivo,sizeof(E_Usuario),1,pFile))
        {
            free(usuarioEnArchivo);
            usuarioEnArchivo=NULL;
            break;
        }
        if(usuarioEnArchivo->id==Usuario->id);
        break;
        i++;
    }
    if(usuarioEnArchivo!=NULL)
        fseek(pFile,sizeof(E_Usuario)*i,SEEK_SET);
    fwrite(Usuario,sizeof(E_Usuario),1,pFile);
    fclose(pFile);
}


/*************************//**ELIMINAR_ELEMENTOS******************************************************/

int borrarPorIdProducto(ArrayList* lista_Producto,int id)
{
    E_Productos* producto;
    int auxReturn=-1;
    int i;
    for(i=0; i<lista_Producto->len(lista_Producto); i++)
    {
        producto=(E_Productos*)lista_Producto->get(lista_Producto,i);
        if(producto->id==id)
        {
            auxReturn=1;
            lista_Producto->remove(lista_Producto,i);
            free(producto);
            break;
        }
    }
    return auxReturn;
}

void bajaProducto(ArrayList* lista_Usuarios,E_Listas_Ordenadas* listasOrdenadas,int generadorId, ArrayList* lista_Productos)
{
    int index;
    char auxIndex[7];
    char pasword[50];
    E_Usuario* usuario;
    E_Productos* producto;
    ArrayList* listaProductosDeUsuario;
    index=obtenerIndicePorId(lista_Usuarios,generadorId-1,"\nIngrese el ID del usuario");
    if(index==-1)
        return;
    usuario=lista_Usuarios->get(lista_Usuarios,index);
    if(!introducirContrasenia(usuario->pasword,pasword))
        return;
    listaProductosDeUsuario=generarListaProductosAsociados(usuario->id,lista_Productos);
    imprimirListaProductos(listaProductosDeUsuario);
    if(cargarNumero(auxIndex,"Ingrese la opcion a eliminar","Opcion incorrecta",1,listaProductosDeUsuario->len(listaProductosDeUsuario)))
    {
        producto=listaProductosDeUsuario->get(listaProductosDeUsuario,atoi(auxIndex)-1);
        if(borrarPorIdProducto(lista_Productos,producto->id))
        {
            printf("\nProducto eliminado.\n");
            getch();
            sobreEscribirArchivo(lista_Productos,sizeof(E_Productos),"Productos.bin");
        }
        actualizarListasOrdenadasProductos(listasOrdenadas,lista_Productos);
    }
    listaProductosDeUsuario->deleteArrayList(listaProductosDeUsuario);
}

void bajaUsuario(ArrayList* lista_Usuarios,E_Listas_Ordenadas* listasOrdenadas,int generadorId, ArrayList* lista_Productos)
{
    int index;
    char confirm;
    E_Usuario* usuario;
    index=obtenerIndicePorId(lista_Usuarios,generadorId-1,"\nIngrese el ID del usuario a Eliminar:");
    if(index!=-1)
    {
        confirm=getChar("Está segunro que desea eliminar este usuario?");
        if(confirm=='s' || confirm == 'S')
        {
            usuario=lista_Usuarios->get(lista_Usuarios,index);
            eliminarProductosAsociados(usuario->id,lista_Productos);
            free(usuario);
            lista_Usuarios->remove(lista_Usuarios,index);
            printf("Usuario eliminado.");
            sobreEscribirArchivo(lista_Usuarios,sizeof(E_Usuario),"Usuarios_Venta.bin");
            getch();
            actualizarTodasListasOrdenadas(listasOrdenadas,lista_Usuarios);
            actualizarListasOrdenadasProductos(listasOrdenadas,lista_Productos);
        }
        else
            printf("Usuario no eliminado.");
        getch();
    }
}

void eliminarProductosAsociados(int id, ArrayList* lista_Productos)
{
    printf("ID: %d",id);
    getch();
    int i=0;
    E_Productos* producto;
    int flag=0;
    for(; i<lista_Productos->len(lista_Productos); i++)
    {
        producto=lista_Productos->get(lista_Productos,i);
        printf("producto: %s",producto->nombreProducto);
        getch();
        if(producto->idUsuario==id)
        {
            printf("Producto eliminado");
            getch();
            flag=1;
            free(producto);
            lista_Productos->remove(lista_Productos,i);
            i--;
        }
    }
    if(flag)
        sobreEscribirArchivo(lista_Productos,sizeof(E_Productos),"Productos.bin");
}


/*************************//**ORDENAR_ELEMENTOS******************************************************/

ArrayList* actualizarListaOrdenada(ArrayList* listasOrdenadas,ArrayList* listaUsuarios,int(*fComp)(void*,void*))
{

    int i;
    if(listasOrdenadas==NULL)
        listasOrdenadas=generarListaUsuariosOrdenada(listaUsuarios,fComp);
    else if(listasOrdenadas->containsAll((listasOrdenadas),listaUsuarios))
    {

        for(i=0; i<listaUsuarios->len(listaUsuarios); i++)
            if(0==listaUsuarios->contains(listaUsuarios,listasOrdenadas->get(listaUsuarios,i)))
            {
                listasOrdenadas->remove(listasOrdenadas,i);
                break;
            }
    }
    else
        insertarEnListaOrdenada(listasOrdenadas,listaUsuarios->get(listaUsuarios,-1+listaUsuarios->len(listaUsuarios)),compararPorId);
    return listasOrdenadas;
}

int elegirCategoria(E_Productos* producto,E_Listas_Ordenadas* listas_Ordenadas)
{
    int retorno=0;
    if(producto!=NULL)
    {
        system("cls");
        printf("CATEGORIAS \n\n");
        printf(" 1- Electronica.\n");
        printf(" 2- Deportes.\n");
        printf(" 3- Otros.\n");
        char auxiliar[10];
        if(cargarNumero(auxiliar,"Indique la categoria: ","\nOpcion inexistente.",1,3))
        {
            retorno=1;
            producto->categoria=atoi(auxiliar);
            actualizarListaOrdenadaProductos(listas_Ordenadas,producto,atoi(auxiliar));
        }
    }
    return retorno;
}

void actualizarListaOrdenadaProductos(E_Listas_Ordenadas* lista_Ordenada, E_Productos* producto,int lista)
{
    switch(lista)
    {
    case DEPORTES:
        agregarProductoListaOrdenada(lista_Ordenada->Deportes,producto);
        break;
    case ELECTRONICA:
        agregarProductoListaOrdenada(lista_Ordenada->Electronica,producto);
        break;
    case OTROS:
        agregarProductoListaOrdenada(lista_Ordenada->otros,producto);
        break;
    default:
        printf("\nNo se pudo cargar en ninguna lista!");
        getch();
        break;
    }
}

ArrayList* generarListaProductosAsociados(int id, ArrayList* lista_Productos)
{
    ArrayList* productosDelUsuario;
    productosDelUsuario=lista_Productos->filter(lista_Productos,mismoIdProducto,id);
    return productosDelUsuario;
}

void agregarProductoDestacado(ArrayList* productos_Destacados,ArrayList* listaProductos,int index)
{
    if(productos_Destacados!=NULL && listaProductos!=NULL)
    {
        E_Productos* auxiliar;
        auxiliar=listaProductos->pop(listaProductos,index);
        listaProductos->add(productos_Destacados,auxiliar);
        sobreEscribirArchivo(listaProductos,sizeof(E_Productos),"Productos.bin");
        sobreEscribirArchivo(productos_Destacados,sizeof(E_Productos),"Productos_Destacados.bin");
    }
}

int destacarProductoInicial(int* isDestacado)
{
    int retorno=0;
    if(isDestacado!=NULL)
    {
        retorno=1;
        char respuesta;
        respuesta=getChar("Desea destacar su publicacion? s/n");
        if(respuesta=='s' || respuesta=='S')
            *isDestacado=1;
    }
    return retorno;
}

void agregarProductoListaOrdenada(ArrayList* listaAgrupada,E_Productos* producto)
{
    if(listaAgrupada!=NULL && producto!=NULL)
        listaAgrupada->add(listaAgrupada,producto);
}

void* generarListaUsuariosOrdenada(ArrayList* lista_Usuarios,int (*fComp)(void*,void*))
{

    ArrayList* listas_Ordenadas=NULL;
    listas_Ordenadas=(lista_Usuarios->clone(lista_Usuarios));
    if(listas_Ordenadas!=NULL)
        ordenarUsuario(listas_Ordenadas,fComp);
    return listas_Ordenadas;
}

void insertarEnListaOrdenada(ArrayList* lista,E_Usuario* usuario,int (*fComp)(void*,void*))
{
    int i;
    E_Usuario* auxUsuario;
    for(i=0; i<lista->len(lista); i++)
    {
        auxUsuario=lista->get(lista,i);
        if(1==fComp(auxUsuario,usuario))
            break;
    }
    lista->push(lista,i,usuario);
}

void actualizarTodasListasOrdenadas(E_Listas_Ordenadas* listasOrdenadas,ArrayList* lista_Usuarios)
{
    listasOrdenadas->idUp=actualizarListaOrdenada(listasOrdenadas->idUp,lista_Usuarios,compararPorId);
    listasOrdenadas->nameUp=actualizarListaOrdenada(listasOrdenadas->nameUp,lista_Usuarios,compararPorNombre);
}

/*************************//**COMPARAR_ELEMENTOS******************************************************/
int mismoIdProducto(void* auxProducto,int id)
{
    int retorno=0;
    if(auxProducto!=NULL)
    {
        E_Productos* producto=(E_Productos*)auxProducto;
        if(producto->idUsuario==id)
            retorno=1;
    }
    return retorno;
}

int filtrarCategoria(void* auxProducto,int argu)
{
    E_Productos* producto;
    int auxReturn=0;
    if(auxProducto!=NULL)
    {
        producto=auxProducto;
        if(producto->categoria==argu)
            auxReturn=1;
    }
    return auxReturn;
}


/*************************//**ARCHIVOS******************************************************/

void actualizarArchivoBinario(void* elemento,char* nombreArchivo,int size)
{
    FILE* pFile=fopen(nombreArchivo,"ab");
    if(pFile!=NULL)
        fwrite(elemento,size,1,pFile);
    fclose(pFile);
}

void sobreEscribirArchivo(ArrayList* lista,int size,char* nombre)
{
    int index;
    E_Usuario* usuario;
    FILE* pFile=fopen(nombre,"wb");
    if(pFile==NULL)
        return;
    for(index=0; index<lista->len(lista); index++)
    {
        usuario=lista->get(lista,index);
        fwrite(usuario,size,1,pFile);
    }
    fclose(pFile);
}
