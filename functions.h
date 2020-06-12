#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "map.h"
#include "sortedMap.h"
#include "list.h"
#include <string.h>
#include <stdbool.h>

//funci�n que retorna negativo si key1<key2, positivo si key1>key2
//y 0 si las claves son iguales
int cmpfloat(const void * key1, const void * key2);

typedef struct Pelicula{

    char * id; //segunda posicion del archivo csv
    char * titulo; //6ta posicion del archivo csv
    float rating; //decima posicion del archivo csv
    int year; // posicion 11 del archivo csv
    List * generos; // posicion 12 del archivo csv
    int numVotos; // posicion 13 del archivo csv
    List * directores; // posicion 15 del archivo csv
    List * listasDePeliculasAsociadas; //guardar� el nombre de las listas
    bool marcada;

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

//a�ade la extensi�n csv a la variable ingresada
void anadirExtensionCSV(char *);

void ordenarAlfabeticamente(List *);

void ordenarPorPuntos(List *);

/* Funciones del men� */

//carga las peliculas de un archivo csv a una lista de peliculas, retorna -1 para que el men� aparezca nuevamente
int cargarListaPeliculas(HashTable *, HashTable *, List *);

//muestra las listas de peliculas
int verListasDePeliculas(List *);

//muestra las peliculas de una lista
int verPeliculasLista(HashTable *, List *);

//muestra la informaci�n de una pelicula y las listas de peliculas a las que est� asociada
int verInformacionPelicula(HashTable *);

/* Marcar una pelicula como favorita permite que todas las listas asociadas a esa pelicula sumen un punto
, por lo que ser� ordenado por la cantidad de puntos que tienen las listas*/
int marcarPeliculaComoPreferida(HashTable *,HashTable *, List *);

/*Esta opci�n recomienda las 10 peliculas con m�s puntos ordenadas por el imdb rating, de la lista de peliculas con m�s puntos */
int recomendarPelicula(HashTable *, List *);

#endif // FUNCTIONS_H
