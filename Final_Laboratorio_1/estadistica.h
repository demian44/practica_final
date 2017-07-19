#define CANTIDADFALLOS 4
#define CANTIDADMENORTRES 0
#define CANTIDADTRES 1
#define CANTIDADCUATROSIETE 2
#define CANTIDADMAYORSIETE 3

typedef struct{
    char nameServicioMasFallas[33];
    int maximo;
    int fallos[CANTIDADFALLOS];
    int cantidadFallasServicio;
}Estadistica;


void serviciosConMasFallos(int* flag);
void inicializarEstadistica(ArrayList* lista_Log,ArrayList* lista_Servicios);
void imprimirEstadistica();
