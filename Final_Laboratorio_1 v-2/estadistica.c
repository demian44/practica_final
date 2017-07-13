//#include "estadistica.h"
//#include "usuarios.h"
//#include "temas.h"
//#include "strings.h"
//
//static Estadistica estadistica;
//FILE* estadFile;
//void generarEstadistica(ArrayList* userList,ArrayList* temList)
//{
//    int i,j;
//    Tema* tema;
//    User* user;
//    int cantidadEscuchas;
//    estadFile=fopen("estadistica.csv","w");
//    if(estadFile==NULL)
//        return;
//
//    estadistica.cantidadEscuchas=0;
//    for(i=0;i<temList->len(temList);i++)
//    {
//        cantidadEscuchas=0;
//        tema=temList->get(temList,i);
//        for(j=0;j<userList->len(userList);j++)
//        {
//            user=userList->get(userList,j);
//            if(user->idTemas==tema->id)
//                cantidadEscuchas++;
//        }
//        if(cantidadEscuchas>estadistica.cantidadEscuchas){
//            strcpy(estadistica.tema_masEscuchado,tema->nombre);
//            estadistica.cantidadEscuchas=cantidadEscuchas;
//        }
//    }
//    char nacionalidad[]="nacionalidad";
//    for(i=0;i<temList->len(temList);i++)
//    {
//        cantidadEscuchas=0;
//        tema=temList->get(temList,i);
//        for(j=0;j<userList->len(userList);j++)
//        {
//            if(strcmp(nacionalidad,user->pais)!=0){
//                strcpy(Estadistica.tema_masEscuchadoPorNacionalidad[indexNac],nacionalidad);
//                strcpy(Estadistica.cantidadEscuchasPorNacionalidad[indexNac],);
//                strcpy(nacionalidad,user->pais);
//            }
//
//            user=userList->get(userList,j);
//            if(user->idTemas==tema->id)
//                cantidadEscuchas++;
//        }
//        if(cantidadEscuchas>estadistica.cantidadEscuchas){
//            strcpy(estadistica.tema_masEscuchado,tema->nombre);
//            estadistica.cantidadEscuchas=cantidadEscuchas;
//        }a
//    }
//}
