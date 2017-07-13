#include <stdlib.h>
#include <string.h>
#include "validacion.h"
#include "carga.h"
#include "ArrayList.h"


typedef struct
{
    char nombre[50];
    char mail[80];
} E_Destinatario;

/** \brief depura la lista de destinatario, eliminando los de la lista negra
 * \param this ArrayList* lista de destinatarios
 * \param this ArrayList* lista negra
 * \param int* puntero a bandera para indicar que se depuro exitosamente
 * \return int Return (0) si los punteros son nulos.
 */
int depurarLista(ArrayList* destinatarios,ArrayList* listaNegra,int* flagDepurado);

/** \brief depura la lista de destinatario, eliminando los de la lista negra
 * \param this ArrayList* lista de destinatarios
 * \param string nombre del archivo de donde se extraera la informacion
 * \param int* bandera que indica si la lista ya esta cargada y depurada
 */
void  cargarDestinatarios(ArrayList* lista, char* nombreArchivo,int* flagDepurado);

/** \brief imprime la lista, si es que la misma se encuentra depurada
 * \param this ArrayList* lista de destinatarios
 * \param int* puntero a bandera que indica si la lista fue depurada
 */
void imprimirListaDepurada(ArrayList* listaDepurada,int *flagDepurado);

/** \brief elimina elementos repetidos en un arraylist de destinatarios
 * \param this ArrayList* lista de destinatarios
 */
void eliminarRepetidos(ArrayList* lista);

/** \brief encuentra y elimina un usuario repetido
 * \param this ArrayList* lista de destinatarios
 * \param E_Usuario* usuario a revisar
 */
void encontrarBorrarRepetido(ArrayList* lista, E_Destinatario* destinatario);
