#include "Arraylist.h"
typedef struct{
    int id;
    char email[65];
    char name[33];
}Service;

void cargarListaServices(ArrayList* lista);
int setService(void);
void printService(void);
int service_new(Service** service);
int buscarServicioPorId(int id);
int obtenerNombreServicioPorId(int id, char* retornoName);
int obtenerEmailServicioPorId(int id, char* email);
ArrayList* getListaService(void);
