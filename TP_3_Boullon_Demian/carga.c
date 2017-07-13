#include "carga.h"

int getInt(char* mensaje)
{
    int entero;
    printf("%s",mensaje);
    scanf(" %d",&entero);
    return entero;
}

float getFloat(char mensaje[])
{
    float flotante;
    printf("%s",mensaje);
    scanf("%f",&flotante);
    return flotante;
}

char getChar(char mensaje[])
{
    char caracter;
    printf("%s",mensaje);
    fflush(stdin); // Win
    // fpurge(stdin); //Linux y OSx
    scanf("%c",&caracter);
    return caracter;
}

int getNumeroAleatorio(int desde, int hasta, int iniciar)
{
    if(iniciar)
        srand (time(NULL));
    return desde + (rand() % (hasta + 1 - desde)) ;
}

void getString(char mensaje[],char arrayChar[])
{
    fflush(stdin);
    printf("%s",mensaje);
    scanf("%s",arrayChar);
}

void getText(char* mensaje,char* arrayChar,int cantidadDeCaracteres)
{
    if(cantidadDeCaracteres==21)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%21[^\n]",arrayChar);
    }
    else if(cantidadDeCaracteres==51)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%51[^\n]",arrayChar);
    }
    else if(cantidadDeCaracteres==101)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%101[^\n]",arrayChar);
    }
    else if(cantidadDeCaracteres==201)
    {
        fflush(stdin);
        printf("%s",mensaje);
        scanf("%101[^\n]",arrayChar);
    }

}

void getTexto(char* mensaje,char* arrayChar,char* cantidadDeCaracteres)
{
    int i;
    char mascara[10]="%";
    strcpy((mascara+1),cantidadDeCaracteres);
    i=1+strlen(cantidadDeCaracteres);
    strcpy((mascara+i),"[^\n]");
    fflush(stdin);
    printf("%s",mensaje);
    scanf(mascara,arrayChar);
}

int getNumerosChar (char array[],char mensaje[])
{
    fflush( stdin );
    int retorno=0;
    getString(mensaje,array);
    if(esNumeroChar(array))
    {
        retorno= 1;
    }
    return retorno;
}


int getStringLetras(char mensaje[],char input[])
{
    fflush( stdin );
    getString(mensaje,input);
    if(esSoloLetras(input))
    {
        return 1;
    }
    return 0;
}

int ingresarSoloLetras (char auxiliar[], char mensajeParaPedirDato[],char mensajeError[])
{
    char seguir='s';
    int cargaExitosa;
    do
    {
        cargaExitosa=getStringLetras(mensajeParaPedirDato,auxiliar);
        if(!(cargaExitosa))
        {
            printf(mensajeError);// Ejemplo "Ha ingresado caracteres invalidos para un nombre.\n"
            seguir=getChar("Desea reintentar? s/n");
        }
    }
    while(cargaExitosa!=1 && seguir == 's');
    return cargaExitosa;
}

int cargarDescripcion(EMovie** movie, int index)
{
    char auxiliarDescripcion[100];
    int cantiadadDeCaracteres;
    int retorno=0;
    char seguir='n';

    do
    {
        getText("\nIngrese la descripcion(maximo de 50 caracteres):\n",auxiliarDescripcion,51);
        if((cantiadadDeCaracteres=strlen(auxiliarDescripcion))<51)
        {
            strcpy(((*(movie+index))->descripcion),auxiliarDescripcion);
            retorno=1;
        }
        else
        {
            seguir=getChar("Ingreso una descripcion superior a 50  caracteres.\nDesea reintentar? s/n:\n");
        }
    }
    while(seguir=='s' && retorno ==0);
    return retorno;

}

int cargarGenero(EMovie** movie,int index)
{
    char auxiliarGenero[52];
    int cantiadadDeCaracteres;
    int retorno=0;
    char seguir='n';
    do
    {
        getText("\nIngrese el genero(maximo de 20 caracteres):\n",auxiliarGenero,51);
        if((cantiadadDeCaracteres=strlen(auxiliarGenero))<51)
        {
            strcpy(((*(movie+index))->genero),auxiliarGenero);
            retorno=1;
        }
        else
        {
            seguir=getChar("\nDesea reintentar? s/n:\n");
        }

    }
    while(retorno!=1 && (seguir!= 's' || seguir!= 'S'));

    return retorno;
}

int cargarDuracion (EMovie** movie,int index)
{
    char seguir='s';
    int retorno=0;
    char auxiliar[20];
    do
    {

        retorno=getNumerosChar(auxiliar,"\nIngrese la duracion de la pelicula (minutos):\n");
        if(retorno==0 || (atoi(auxiliar)<40) || (atoi(auxiliar)>5220 ))
        {
            /**Largo minimo para una pelicula, segun la British Film Institute, el largo maximo corresponde a Modern
            *  Times Forever(Stora Enso Building, Helsinki), la pelicula con el record guines de mayor duracion.**/
            printf("\nValor incorrecto.");
            retorno=0;
            seguir=getChar("Desea reintentar? s/n");
        }
        else
        {
            retorno = 1;
            strcpy((*(movie+index))->duracion,(auxiliar));
        }
    }
    while(retorno!=1 && seguir == 's');


    return retorno;
}

int cargarlinkImagen(EMovie** movie,int index)
{
    char auxiliarLink[102];
    int cantiadadDeCaracteres;
    int retorno=0;
    char seguir='n';
    do
    {
        getText("\nIngrese el link:\n",auxiliarLink,101);
        if((cantiadadDeCaracteres=strlen(auxiliarLink))<101)
        {

            strcpy(((*(movie+index))->linkImagen),auxiliarLink);
            retorno=1;
        }
        else
        {
            seguir=getChar("\nDesea reintentar? s/n:\n");
        }

    }
    while(retorno!=1 && (seguir!= 's' || seguir!= 'S'));

    return retorno;
}

int cargarPuntaje (EMovie** movie,int index)
{
    char seguir='s';
    int retorno=0;
    char auxiliar[20];
    do
    {

        retorno=getNumerosChar(auxiliar,"\nIngrese el puntaje de la pelicula(0-5):\n");
        if(retorno==0 || (atoi(auxiliar)<0) || (atoi(auxiliar)>5 ))
        {
            printf("Valor incorrecto.");
            retorno=0;
            seguir=getChar("Desea reintentar? s/n");
        }
        else
        {
            retorno = 1;
            strcpy((*(movie+index))->puntaje,(auxiliar));
        }
    }
    while(retorno!=1 && seguir == 's');


    return retorno;
}

int cargarTitulo(EMovie** movie,int index)
{
    char auxiliarTitulo[22];
    int cantiadadDeCaracteres;
    int retorno=0;
    char seguir='n';
    do
    {
        getText("\nIngrese el titulo(maximo de 50 caracteres):\n",auxiliarTitulo,51);
        if((cantiadadDeCaracteres=strlen(auxiliarTitulo))<51)
        {
            strcpy(((*(movie+index))->titulo),auxiliarTitulo);
            retorno=1;
        }
        else
        {
            seguir=getChar("\nDesea reintentar? s/n:\n");
        }

    }
    while(retorno!=1 && (seguir!= 's' || seguir!= 'S'));

    return retorno;
}

void mayToMin(char* string)
{
	int i=0;
	int diferencia='A'-'a';
	for (i=0;string[i]!='\0';++i)
	{
		if(string[i]>='A'&&string[i]<='Z')
		{
			string[i]=string[i]-diferencia;
		}
	}
}
void agregarExtension(char* array,char* extension)
{
    int i;
    for(i=0;*(array+i)!='\0'&&*(array+i)!='.';)
    {
        i++;
    }
    strcpy((array+i),".html");
}

int contarPeliculasFile(char* nFile,int* cantidadPeliculas)
{
    int retorno=0;
    FILE* pFile;
    pFile=fopen(nFile,"rb");
    if(pFile!=NULL)
    {
        fseek(pFile,0,SEEK_END);
        (*cantidadPeliculas)=(ftell(pFile))/(sizeof(EMovie));
        fclose(pFile);
        retorno=1;
    }
    return retorno;
}

void editMovieInFile(EMovie** movie,int indice)
{
    FILE* pFileBin=NULL;
    pFileBin=fopen("movie.txt","r+b");
    if(pFileBin==NULL)
        printf("Error al intentar abrir el archivo.");
    else
    {
        pFileBin=fopen("movie.txt","ab");
        if(pFileBin==NULL)
        {
            printf("\nError, no se pudo acceder a la base de datos.");
            getch();
        }
        else
        {

            fseek(pFileBin,sizeof(EMovie)*indice,SEEK_SET);
            fwrite(((*(movie+indice))),sizeof(EMovie),1,pFileBin);
            fclose(pFileBin);
        }
    }
}

void comprimirArrayMovies(EMovie** movie,int* peliculasCargadas, int opcionPelicula,int* capacidadTotalPeliculas)
{
    int i;
    EMovie* auxiliarLista;

    auxiliarLista=(*(movie+opcionPelicula));
    (*(movie+opcionPelicula))=(*(movie+(*peliculasCargadas-1)));
    (*(movie+(*peliculasCargadas-1)))=auxiliarLista;
    (*peliculasCargadas)--;

    i=((*capacidadTotalPeliculas)-1);
    while(((*capacidadTotalPeliculas)-((*peliculasCargadas)))>10)
    {
        free(*(movie+i));
        (*capacidadTotalPeliculas)--;
    }
}

void hardCodearArray(EMovie** list)
{
    int i=0;
    strcpy((*(list+i))->descripcion,"Rogue One, es una pelicula de tipo spin-off con respecto al canon de peliculas de la franquicia Star Wars.");
    strcpy((*(list+i))->titulo,"Rogue One");
    strcpy((*(list+i))->genero,"Ciencia Ficcion");
    strcpy((*(list+i))->linkImagen,"https://i2.wp.com/akihabarablues.com/wp-content/uploads/2016/12/rogue-one-poster.jpg");
    strcpy(((*(list+i))->puntaje),"3");
    strcpy(((*(list+i))->duracion),"140");
    i++;
    strcpy((*(list+i))->descripcion,"Esta pelicula bla bla bla...");
    strcpy((*(list+i))->titulo,"American History X");
    strcpy((*(list+i))->genero,"Drama");
    strcpy((*(list+i))->linkImagen,"https://images-na.ssl-images-amazon.com/images/M/MV5BMjMzNDUwNTIyMF5BMl5BanBnXkFtZTcwNjMwNDg3OA@@._V1_.jpg");
    strcpy(((*(list+i))->puntaje),"5");
    strcpy(((*(list+i))->duracion),"190");
    i++;
    strcpy((*(list+i))->descripcion,"Esta pelicula bla bla bla...");
    strcpy((*(list+i))->titulo,"Pulp Fiction");
    strcpy((*(list+i))->genero,"Policial");
    strcpy((*(list+i))->linkImagen,"http://www.gstatic.com/tv/thumb/movieposters/15684/p15684_p_v8_ac.jpg");
    strcpy(((*(list+i))->puntaje),"5");
    strcpy(((*(list+i))->duracion),"140");
    i++;
    strcpy((*(list+i))->descripcion,"La mejor peli del mundo, aunque con algunos errores.");
    strcpy((*(list+i))->titulo,"Interestellar");
    strcpy((*(list+i))->genero,"Ciencia ficcion / Drama");
    strcpy((*(list+i))->linkImagen,"http://ia.media-imdb.com/images/M/MV5BMjIxNTU4MzY4MF5BMl5BanBnXkFtZTgwMzM4ODI3MjE@._V1_SX640_SY720_.jpg");
    strcpy(((*(list+i))->puntaje),"5");
    strcpy(((*(list+i))->duracion),"169");
    i++;
    strcpy((*(list+i))->descripcion,"Descripcion.");
    strcpy((*(list+i))->titulo,"The Godfather");
    strcpy((*(list+i))->genero,"Policial");
    strcpy((*(list+i))->linkImagen,"http://www.youfeelm.com/wp-content/uploads/afiche_elpadrino.jpg");
    strcpy(((*(list+i))->puntaje),"5");
    strcpy(((*(list+i))->duracion),"169");
}

void reservarEspeacio(EMovie** movie,int* capacidadTotalPeliculas)
{
    int i;
    for(i=0; i<*capacidadTotalPeliculas; i++)
    {
        (*(movie+i))=(EMovie*)malloc(sizeof(EMovie));
        if((*(movie+i))==NULL)
        {
            printf("\nPoca memoria en disco.");
            *capacidadTotalPeliculas=i;
            break;
        }
    }
}

void cargarBaseDeDatos(EMovie** movie,int*  peliculasCargadas,int *capacidadTotalPeliculas, int* cantidadPunteros)
{
    if(contarPeliculasFile("movie.txt",peliculasCargadas))
    {
        ampliacionMemoria(movie,(*peliculasCargadas),capacidadTotalPeliculas,cantidadPunteros);
        int i;
        FILE* pFileBin=NULL;
        EMovie* auxiliarMovie;
        int cantMovies=0;
        pFileBin=fopen("movie.txt","rb");
        if(pFileBin==NULL)
             return;
        else
        {
            if((*peliculasCargadas)<100)
            auxiliarMovie=(EMovie*)malloc(sizeof(EMovie)*(cantMovies+100));
            else
            auxiliarMovie=(EMovie*)malloc(sizeof(EMovie)*((*peliculasCargadas)+100));
            cantMovies+=fread(auxiliarMovie, sizeof(EMovie),(*peliculasCargadas), pFileBin);
        }
        fclose(pFileBin);
        *peliculasCargadas=cantMovies;
        ampliacionMemoria(movie, *peliculasCargadas,capacidadTotalPeliculas,cantidadPunteros);
        for(i=0; i<*peliculasCargadas; i++)
            ((**(movie+i)))=(*(auxiliarMovie+i));

    }
}

void crearPisarArchivoBinario(EMovie** movie, int* peliculasCargadas)
{
    int i;

        FILE* pFileBin=NULL;
        pFileBin=fopen("movie.txt","wb");
        for(i=0; i<*peliculasCargadas; i++)
        {
            fwrite(*(movie+i),sizeof(EMovie),1,pFileBin);
        }
        fclose(pFileBin);
        pFileBin=fopen("movie.txt","wb");
        for(i=0; i<*peliculasCargadas; i++)
        {
            fwrite(*(movie+i),sizeof(EMovie),1,pFileBin);
        }
        fclose(pFileBin);
}

void agregarPeliculaBinario(EMovie** movie,int* peliculasCargadas)
{
    FILE* pFileBin=NULL;
    pFileBin=fopen("movie.txt","rb");
    if(pFileBin==NULL)
        crearPisarArchivoBinario(movie,peliculasCargadas);
    else
    {
        pFileBin=fopen("movie.txt","ab");
        if(pFileBin==NULL)
            printf("\nError, no se pudo acceder a la base de datos.");
        else
        {
            fwrite(*(movie+*peliculasCargadas),sizeof(EMovie),1,pFileBin);
            getch();
            fclose(pFileBin);
        }
    }
}

int agregarDatosPelicula(EMovie** movie,int* peliculasCargadas, int* capacidadTotalPeliculas)
{
    int retorno;
    retorno=cargarTitulo(movie,*peliculasCargadas);
    if(retorno)
        retorno=cargarDuracion(movie,*peliculasCargadas);
    if(retorno)
        retorno=cargarGenero(movie,*peliculasCargadas);
    if(retorno)
        retorno=cargarlinkImagen(movie,*peliculasCargadas);
    if(retorno)
        retorno=cargarPuntaje(movie,*peliculasCargadas);
    if(retorno)
        retorno=cargarDescripcion(movie,*peliculasCargadas);
    return retorno;
}

void ampliacionMemoria(EMovie** movie,int peliculasCargadas,int* capacidadTotalPeliculas,int* cantidadPunteros)
{
    EMovie** auxiliarArray;
    int index;
    while(((*capacidadTotalPeliculas)-peliculasCargadas)<10)
    {
        auxiliarArray=(EMovie**)realloc(movie,sizeof(EMovie*)*((*cantidadPunteros)+100));
        if(auxiliarArray==NULL)
        {
            printf("SIN MEMORIA.");
            return;
        }
        movie=auxiliarArray;
        *cantidadPunteros+=100;
        printf("\nAmpliacion de memoria exitosa!!\n\n");

        for(index=*capacidadTotalPeliculas; index<(*capacidadTotalPeliculas+100); index++)
        {
            *(movie+index)=(EMovie*)malloc(sizeof(EMovie));
            if(*(movie+index)==NULL)
            {
                break;
                printf("SIN MEMORIA");
                auxiliarArray=(EMovie**)realloc(movie,sizeof(EMovie*)*(*cantidadPunteros-(100+index)));
                if(auxiliarArray!=NULL)
                    movie=auxiliarArray;
            }
        }
        if(index==(*capacidadTotalPeliculas+(100)))
        {
            printf("Ampliacion exitosa.");
            *capacidadTotalPeliculas=*capacidadTotalPeliculas+100;
        }
    }
    while(((*capacidadTotalPeliculas)-peliculasCargadas)>120)
    {
        auxiliarArray=(EMovie**)realloc(movie,sizeof(EMovie*)*((*cantidadPunteros)-50));
        if(auxiliarArray==NULL)
        {
            printf("SIN MEMORIA.");
            return;
        }
        movie=auxiliarArray;
        *cantidadPunteros-=50;
        printf("\nAmpliacion de memoria exitosa!!\n\n");

        for(index=*capacidadTotalPeliculas; index>(*capacidadTotalPeliculas-50); index--)
        {
            free(*(movie+index));
        }
            printf("Se livero espacio en memoria.");
            *capacidadTotalPeliculas=*capacidadTotalPeliculas-50;
    }
}
