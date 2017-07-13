
int alta (E_Usuario listaPersonas[],int cantidad,int id,int* generadorId);
void baja (E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[]);
void modificar (E_Usuario listaPersonas[],int cantidad,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[]);
void nuevaPublicacion (E_Usuario listaPersonas[],int cantidad, E_Productos listaProductos[], int cantidadLlamas,int id);
void asignarAmbulancia (E_Usuario listaPersonas[],int cantidadPersonas, E_Productos listaProductos[],int cantiadProductos,int stock);
void informarMotivosMasDemorados(E_Productos listaProductos[],int canttidadProductos,EMotivo nombreProducto[]);
void informarAfiliadosMasProductos(E_Productos listaProductos[],int cantProductos,E_Usuario listaPersonas[],int cantidad,int afiliadosConMasProductos[]);
void informarMotivosMasRepetidos(E_Productos listaProductos[],int canttidadProductos,EMotivo nombreProducto[]);
void imprimirListaPorNombre(E_Usuario listaPersonas[],int cantidad);
void informarAfiliadosPorNombreypasword(E_Usuario listaPersonas[],int cantidad);
void modificarPublicacion (E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[]);
void cancelarPublicacion (E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[]);
void nuevaCompra(E_Usuario listaUsuarios[],int cantidadUsuarios,E_Productos listaProductos[], int cantidadProductos);
void listarPublicacionesDeUsuarios(E_Usuario listaPersonas[],int cantidad,E_Productos listaProductos[], int cantidadProductos,char mensaje[],char mensajeError[],char  mensajeNoEncontrado[]);
void hardCode(E_Usuario* listaPersonas,E_Productos* listaProductos);
void listarUsuarios(E_Usuario* listaPersonas,int cantidad);
void mostrarProductoConInformacion(E_Productos* listaProductos,E_Usuario* listaPersonas,int cantidadProductos);
void ordenarVectoresdeUsuarios(E_Usuario* listaPersonas,int cantidad);
