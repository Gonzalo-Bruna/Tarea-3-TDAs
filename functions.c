#include "functions.h"

int cmp(const void * key1, const void * key2) {
    const float * Key1 = key1;
    const float * Key2 = key2;
    if(*Key1 > *Key2) return -1;
    if(*Key1 < *Key2) return 1;
    if(*Key1 == *Key2) return 0;
}

ListaPeliculas * crearListaPeliculas(char * nombre){

    ListaPeliculas * nuevaLista = (ListaPeliculas *) malloc (sizeof(ListaPeliculas));
    nuevaLista->nombre = nombre;
    nuevaLista->peliculas = createSortedMap(cmp);
    nuevaLista->puntos = 0;
    return nuevaLista;

}

Pelicula * crearPelicula(char * id, char * titulo, float rating, int year, char * generos, int numVotos, char * directores){

    Pelicula * nuevaPelicula = (Pelicula *) malloc (sizeof (Pelicula));
    nuevaPelicula->id = id;
    nuevaPelicula->titulo = titulo;
    nuevaPelicula->rating = rating;
    nuevaPelicula->year = year;
    nuevaPelicula->numVotos = numVotos;
    nuevaPelicula->generos = createList();
    nuevaPelicula->directores = createList();

    char caracter[2] = ",";
    char * genero;
    char * director;

    genero = strtok(generos, caracter);
    while(genero != NULL){

        if(genero[0] == ' '){ // quita el espacio del principio

            size_t largo = strlen(genero);
            int i;
            for (i = 0 ; i < largo - 1; i++){

                genero[i] = genero[i + 1];

            }

            genero[largo - 1] = '\0';

        }
        pushBack(nuevaPelicula->generos, genero);
        genero = strtok(NULL, caracter);

    }
    director = strtok(directores, caracter);
    while(director != NULL){

        if(director[0] == ' '){

            size_t largo = strlen(director);
            int i;
            for (i = 0 ; i < largo - 1; i++){

                director[i] = director[i + 1];

            }

            director[largo - 1] = '\0';

        }

        pushBack(nuevaPelicula->directores, director);
        director = strtok(NULL, caracter);

    }


    return nuevaPelicula;

}

const char *get_csv_field (char * tmp, int k) {
    //se crea una copia del string tmp

    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

void anadirExtensionCSV(char * nombre){

    size_t length = strlen(nombre);
    nombre[length] = '.';
    nombre[length + 1] = 'c';
    nombre[length + 2] = 's';
    nombre[length + 3] = 'v';
    nombre[length + 4] = '\0';

}

int cargarListaPeliculas(HashTable * listasDePeliculas, HashTable * todasLasPeliculas){

    printf("Para cargar la lista de peliculas, por favor ingrese el nombre del archivo csv sin su extension: ");

    char nombreArchivo[100];
    scanf("%s", nombreArchivo);
    fflush(stdin);

    anadirExtensionCSV(nombreArchivo);

    FILE * fp = fopen(nombreArchivo, "r");
    if(fp == NULL){

        printf("\nNo ha sido posible abrir el archivo\n\n");
        system("pause");
        return -1;

    }

    printf("\nPor favor ingrese un nombre para la nueva lista de peliculas: ");
    fflush(stdin);
    char nombreLista[100];
    scanf("%[^\n]s", nombreLista);
    fflush(stdin);

    ListaPeliculas * nuevaLista = crearListaPeliculas(nombreLista);
    insertHashTable(listasDePeliculas, nuevaLista->nombre, nuevaLista);

    char linea[1024];

    int cont = 1;
    char * generos = (char *) malloc (100 * sizeof(char));

    while( fgets(linea, 1023, fp) != NULL ){

        if(cont == 1){

            cont++;

        }else{

            char * id = get_csv_field(linea, 1);
            char * titulo = get_csv_field(linea, 5);
            float rating = atof( get_csv_field(linea, 8) );
            int year = atoi( get_csv_field(linea, 9) );
            generos = get_csv_field(linea, 11);
            int numVotos = atoi( get_csv_field(linea, 12) );
            char * directores = get_csv_field(linea, 14);

            Pelicula * pelicula = crearPelicula(id, titulo, rating, year, generos, numVotos, directores);
            //cada pelicula que es creada se almacena en la nueva lista de peliculas
            insertSortedMap(nuevaLista->peliculas, &pelicula->rating, pelicula);
            insertHashTable(todasLasPeliculas, pelicula->id, pelicula);

        }

    }

    Pelicula * pelicula = firstSortedMap(nuevaLista->peliculas);
    if (pelicula) printf("\nLa nueva lista \"%s\" ha sido creada con exito y se han agregado las peliculas\n\n", nombreLista);

    system("pause");
    return -1;
}
