#include "functions.h"

ListaPeliculas * crearListaPeliculas(char * nombre){

    ListaPeliculas * nuevaLista = (ListaPeliculas *) malloc (sizeof(ListaPeliculas));
    nuevaLista->nombre = nombre;
    nuevaLista->peliculas = createBinaryTree();
    nuevaLista->puntos = 0;

}

Pelicula * crearPelicula(char * id, char * titulo, int rating, int year, char * generos, int numVotos, char * directores){

    Pelicula * nuevaPelicula = (Pelicula *) malloc (sizeof (Pelicula));
    nuevaPelicula->id = id;
    nuevaPelicula->titulo = titulo;
    nuevaPelicula->rating = rating;
    nuevaPelicula->year = year;
    nuevaPelicula->numVotos = numVotos;
    nuevaPelicula->generos = createList();
    nuevaPelicula->directores = createList();

    char caracter[2] = ",";

    if(generos[0] == '"'){ //si es que el primer caracter es doble comilla significa que hay más de un elemento

        char * genero = strtok(generos, caracter);

        while (genero != NULL){

            pushBack(nuevaPelicula->generos, genero);
            genero = strtok(NULL, caracter);

        }

    }

    if(directores[0] == '"'){ //si es que el primer caracter es doble comilla significa que hay más de un elemento

        char * director = strtok(director, caracter);

        while (director != NULL){

            pushBack(nuevaPelicula->directores, director);
            director = strtok(NULL, caracter);

        }

    }

}
