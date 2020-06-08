#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "sortedMap.h"
#include "list.h"

typedef struct Pelicula{

    char id; //segunda posicion del archivo csv
    char * titulo; //6ta posicion del archivo csv
    int rating; //decima posicion del archivo csv
    int year; // posicion 12 del archivo csv
    List * generos; // posicion 13 del archivo csv
    int numVotos; // posicion 14 del archivo csv
    List * directores; // posicion 16 del archivo csv

}Pelicula;


#endif // FUNCTIONS_H
