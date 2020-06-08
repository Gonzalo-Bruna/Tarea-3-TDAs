#include "functions.h"

ListaPeliculas * crearListaPeliculas(char * nombre){

    ListaPeliculas * nuevaLista = (ListaPeliculas *) malloc (sizeof(ListaPeliculas));
    nuevaLista->nombre = nombre;
    nuevaLista->peliculas = createBinaryTree();
    nuevaLista->puntos = 0;

}
