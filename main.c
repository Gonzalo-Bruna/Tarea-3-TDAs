#include <stdio.h>

#include "functions.h"

int main()
{

    int opcion;
    printf("Bienvenido a nuestro sistema recomendador de peliculas!\n");

    HashTable * listasDePeliculas = createHashTable(100);
    List * listasDePeliculasList = createList();
    HashTable * todasLasPeliculas = createHashTable(100);


    do{

        printf("\nQue desea hacer?\n\n");
        printf("Opcion 1: Cargar lista de peliculas\n");
        printf("Opcion 2: Ver listas de peliculas\n");
        printf("Opcion 3: Ver peliculas de una lista\n");
        printf("Opcion 4: Ver informacion de una pelicula\n");
        printf("Opcion 5: Marcar pelicula como preferida\n");
        printf("Opcion 6: Recomendar pelicula\n");
        printf("Opcion 0: Salir del programa\n");
        printf("\n");
        printf("Ingrese una opcion: ");

        scanf("%d", &opcion);
        if(opcion < 0 || opcion > 6) printf("\nDebe ingresar una opcion correcta\n\n");
        else{

            switch(opcion){

                case 1: opcion  = cargarListaPeliculas(listasDePeliculas, todasLasPeliculas, listasDePeliculasList);
                    break;
                case 2: opcion = verListasDePeliculas(listasDePeliculasList);
                default:
                    break;

            }

        }

    }while(opcion < 0 || opcion > 6);

    system("pause");
    return 0;
}
