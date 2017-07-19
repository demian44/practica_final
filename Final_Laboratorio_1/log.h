#include "ArrayList.h"
typedef struct{
    char date[11];
    char time[6];
    int serviceId;
    int gravedad;
    char msg[65];
}LogEntry;

void cargarListalogs(ArrayList* lista, int* flag);
int log_new(LogEntry** log);
void printlog(void);
void procesarInfo(int* flag);
ArrayList* getListaLog(void);
