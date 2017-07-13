#define LGENERAL 0
#define LVALIDOS 1
#define LINVALIDOS 2
#define LVISA 3
#define LMASTER 4
#define LAMERICAN 5
#define CANTIDADLISTAS 6

typedef struct{
    char id[5];
    char nombre[40];
    char apellido[40];
    char email[40];
    Tarjeta tarjeta;
}Clientes;

void cargarListas(ArrayList** cListas);
Clientes* clientes_new();
void imprimirLista(int lista);
int validarId(int index);
int detectarTarjeta(char* tarjet);
void generarListaValidos(void);
void guardarEnArchivo(void);
