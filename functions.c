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
    nuevaPelicula->listasDePeliculasAsociadas = createList();

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

void ordenarAlfabeticamente(List * listasDePeliculasList){

    Node * p1 = retornarNodoCabeza(listasDePeliculasList);
    Node * j1;

    ListaPeliculas * p;
    ListaPeliculas * j;
    ListaPeliculas * aux;

    while(p1){

        j1 = p1->next;
        p = returnNodeData(p1);
        while(j1){

            j = returnNodeData(j1);
            if(strcmp(p->nombre, j->nombre) > 0){

                p = j1->data;

                aux = j1->data;
                j1->data = p1->data;
                p1->data = aux;

            }


            j1 = j1->next;
        }

        p1 = p1->next;
    }


}

int cargarListaPeliculas(HashTable * listasDePeliculasTable, HashTable * todasLasPeliculas, List * listasDePeliculasList){

    printf("\nPara cargar la lista de peliculas, por favor ingrese el nombre del archivo csv sin su extension: ");

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

    char * nombreLista = (char *) malloc (50 * sizeof(char));
    ListaPeliculas * nuevaLista;

    do{

        printf("\nPor favor ingrese un nombre para la nueva lista de peliculas: ");
        fflush(stdin);
        scanf("%[^\n]s", nombreLista);
        fflush(stdin);

        nuevaLista = searchHashTable(listasDePeliculasTable,nombreLista);

        if (nuevaLista){

            printf("\nEl nombre que ha ingresado ya corresponde a una lista de peliculas existente, intentenlo nuevamente,\n");

        }
        else break;

    }while(1);

    nuevaLista = crearListaPeliculas(nombreLista);
    insertHashTable(listasDePeliculasTable, nuevaLista->nombre, nuevaLista); //la tabla hash almacenará para acceder rapidamente a la lista elegida
    pushBack(listasDePeliculasList, nuevaLista); //la lista nos servirá para mostrar por orden de creación las listas de peliculas

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
            int year = atoi( get_csv_field(linea, 10) );
            generos = get_csv_field(linea, 11);
            int numVotos = atoi( get_csv_field(linea, 12) );
            char * directores = get_csv_field(linea, 14);

            Pelicula * pelicula = searchHashTable(todasLasPeliculas, id);
            if(!pelicula){

                //si la pelicula no existe creamos memoria para una y se ingresa en los tdas correspondientes
                pelicula = crearPelicula(id, titulo, rating, year, generos, numVotos, directores);
                insertSortedMap(nuevaLista->peliculas, &pelicula->rating, pelicula);
                insertHashTable(todasLasPeliculas, pelicula->id, pelicula);
                pushBack(pelicula->listasDePeliculasAsociadas, nuevaLista->nombre);

            }
            else{

                //si la pelicula ya existía entonces se guarda en la lista asociada, y en la lista de listas asociadas se guarda el nombre de la lista
                insertSortedMap(nuevaLista->peliculas, &pelicula->rating, pelicula);
                pushBack(pelicula->listasDePeliculasAsociadas, nuevaLista->nombre);

            }

        }

    }

    Pelicula * pelicula = firstSortedMap(nuevaLista->peliculas);
    if (pelicula) printf("\nLa nueva lista \"%s\" ha sido creada con exito y se han agregado las peliculas\n\n", nombreLista);

    system("pause");
    return -1;
}

int verListasDePeliculas(List * listasDePeliculasList){

    ListaPeliculas * listaPeliculas = first(listasDePeliculasList);
    if(!listaPeliculas){

        printf("\nAun no existe ninguna lista de peliculas\n\n");
        system("pause");
        return -1;

    }

    ordenarAlfabeticamente(listasDePeliculasList);

    listaPeliculas = first(listasDePeliculasList);

    printf("\nEstas son todas las listas disponibles:\n\n");

    while(listaPeliculas != NULL){

        printf("%s\n", listaPeliculas->nombre);
        listaPeliculas = next(listasDePeliculasList);

    }

    printf("\n");
    system("pause");
    return -1;
}

int verPeliculasLista(HashTable * listasDePeliculasTable, List * listasDePeliculasList){

    ListaPeliculas * listaPeliculas = firstHashTable(listasDePeliculasTable);
    if(!listaPeliculas){

        printf("\nAun no ha sido agregada ninguna lista de peliculas\n\n");
        system("pause");
        return -1;

    }

    printf("\nEstas son las listas que han sido agregadas a la aplicacin: \n\n");
    listaPeliculas = first(listasDePeliculasList);

    while(listaPeliculas){

        printf("%s\n", listaPeliculas->nombre);
        listaPeliculas = next(listasDePeliculasList);

    }

    char nombreLista[50];

    do{

        printf("\nPor favor ingrese el nombre de la lista de peliculas que desea ver: ");
        fflush(stdin);
        scanf("%[^\n]s", nombreLista);
        fflush(stdin);

        listaPeliculas = searchHashTable(listasDePeliculasTable,nombreLista);

        if (!listaPeliculas){

            printf("\nNo existe ninguna lista que tenga este nombre, intentelo nuevamente,\n");

        }
        else break;

    }while(1);

    printf("\nEstas son las peliculas de la lista de peliculas seleccionada: \n\n");

    Pelicula * pelicula = firstSortedMap(listaPeliculas->peliculas);
    while(pelicula != NULL){

        printf("Titulo: %s, ID: %s, IMDb rating: %.1f\n", pelicula->titulo, pelicula->id, pelicula->rating);
        pelicula = nextSortedMap(listaPeliculas->peliculas);

    }

    printf("\n");
    system("pause");
    return -1;
}

int verInformacionPelicula(HashTable * todasLasPeliculas){

    Pelicula * pelicula = firstHashTable(todasLasPeliculas);
    if(!pelicula){

        printf("\nAun no han sido agregadas ninguna lista de peliculas\n\n");
        system("pause");
        return -1;

    }

    char id[20];
    printf("\nPor favor ingrese el id de la pelicula que desea buscar: ");
    fflush(stdin);
    scanf("%s", id);
    fflush(stdin);

    pelicula = searchHashTable(todasLasPeliculas, id);
    if (!pelicula){

        printf("\nNo hemos encontrado ninguna pelicula que coicida con este id\n\n");
        system("pause");
        return -1;

    }

    printf("\nEsta es la información de la pelicula solicitada: \n\n");
    printf("Titulo: %s\nRating: %.1f\nYear: %d\nNumero de votos: %d\nGeneros: ", pelicula->titulo, pelicula->rating, pelicula->year, pelicula->numVotos);

    char * genero = first(pelicula->generos);
    printf("%s", genero);
    while(genero){

        genero = next(pelicula->generos);
        if (!genero) break;
        printf(", %s", genero);

    }

    char * director = first(pelicula->directores);
    printf("\nDirectores: ");
    printf("%s", director);

    while(director){

        director = next(pelicula->directores);
        if(!director) break;
        printf(", %s", director);

    }

    printf("\n\nY estas son las listas de peliculas asociadas: \n\n");
    char * nombreLista = first(pelicula->listasDePeliculasAsociadas);

    while(nombreLista != NULL){

        printf("%s\n", nombreLista);
        nombreLista = next(pelicula->listasDePeliculasAsociadas);

    }

    printf("\n");
    system("pause");
    return -1;

}
