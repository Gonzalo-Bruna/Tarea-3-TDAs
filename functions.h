#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "sortedMap.h"
#include "list.h"
#include <string.h>

typedef struct Pelicula{

    char * id; //segunda posicion del archivo csv
    char * titulo; //6ta posicion del archivo csv
    int rating; //decima posicion del archivo csv
    int year; // posicion 12 del archivo csv
    List * generos; // posicion 13 del archivo csv
    int numVotos; // posicion 14 del archivo csv
    List * directores; // posicion 16 del archivo csv

}Pelicula;

//crea una pelicula y la retorna
Pelicula * crearPelicula(char *, char *, int, int, char *, int, char *);

typedef struct ListaPeliculas{

    char * nombre; //nombre de la lista
    BinaryTree * peliculas; //mapa ordernado de peliculas (ordenado por rating)
    int puntos;

}ListaPeliculas;

//crea una lista de peliculas y la retorna
ListaPeliculas * crearListaPeliculas(char *);


#endif // FUNCTIONS_H
