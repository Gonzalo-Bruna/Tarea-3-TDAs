#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "map.h"
#include "sortedMap.h"
#include "list.h"
#include <string.h>

//función que retorna negativo si key1<key2, positivo si key1>key2
//y 0 si las claves son iguales
int cmp(const void * key1, const void * key2);

typedef struct Pelicula{

    char * id; //segunda posicion del archivo csv
    char * titulo; //6ta posicion del archivo csv
    float rating; //decima posicion del archivo csv
    int year; // posicion 11 del archivo csv
    List * generos; // posicion 12 del archivo csv
    int numVotos; // posicion 13 del archivo csv
    List * directores; // posicion 15 del archivo csv
    List * listasDePeliculasAsociadas; //guardará el nombre de las listas

}Pelicula;

//crea una pelicula y la retorna
Pelicula * crearPelicula(char *, char *, float, int, char *, int, char *);

typedef struct ListaPeliculas{

    char * nombre; //nombre de la lista
    SortedMap * peliculas; //mapa ordernado de peliculas (ordenado por rating)
    int puntos;

}ListaPeliculas;

//crea una lista de peliculas y la retorna
ListaPeliculas * crearListaPeliculas(char *);

//funcion que obtiene un campo de un archivo csv
const char *get_csv_field (char *, int);

//añade la extensión csv a la variable ingresada
void anadirExtensionCSV(char *);

void ordenarAlfabeticamente(List *);

/* Funciones del menú */

//carga las peliculas de un archivo csv a una lista de peliculas, retorna -1 para que el menú aparezca nuevamente
int cargarListaPeliculas(HashTable *, HashTable *, List *);

//muestra las listas de peliculas
int verListasDePeliculas(List *);

//muestra las peliculas de una lista
int verPeliculasLista(HashTable *, List *);

//muestra la información de una pelicula y las listas de peliculas a las que está asociada
int verInformacionPelicula(HashTable *);

#endif // FUNCTIONS_H
