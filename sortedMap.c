#include "sortedMap.h"

TreeNode * createTreeNode(int key, void * value) {
    TreeNode * nodoArbol = (TreeNode *) calloc(1, sizeof(TreeNode));
    nodoArbol->key = key;
    nodoArbol->value = value;
    return nodoArbol;
}

BinaryTree * createBinaryTree() {
     BinaryTree * arbolBinario = (BinaryTree *) calloc( 1, sizeof(BinaryTree));
     return arbolBinario;
}

void insertBinaryTree(BinaryTree * tree, int key, void * value){

    TreeNode * nodo = createTreeNode(key, value);

    if(!tree->root){

        tree->root = nodo;
        tree->current = nodo;
        return;

    }

    //creo un nodo auxiliar para ir preguntando
    TreeNode * aux = tree->root;

    //recorreremos el arbol preguntando si el nuemero es mayor menor o igual, hasta que lleguemos a una posicion vacía

    while(1){
        if (nodo->key == aux->key) return; //si encontramos que ya existía el dato no se hace nada

        //si el nodo que queremos insertar es menor que la raiz
        if(nodo->key < aux->key){

            if(!aux->left){ // si es que es menor y no hay datos a la izquierda insertamos y terminamos la funcion
                aux->left = nodo;
                nodo->parent = aux;
                tree->current = nodo;
                return;
            }

            //si es que si hay un dato, movemos aux a esa posicion
            aux = aux->left;

        }
        else if(nodo->key > aux->key){

            if(!aux->right){

                aux->right = nodo;
                nodo->parent = aux;
                tree->current = nodo;
                return;

            }

            aux = aux->right;

        }

    }
}

void * searchBinaryTree(BinaryTree * tree, int key){

    if(!tree || !tree->root) return NULL;

    TreeNode * aux = tree->root;

    while(1){

        if(aux->key == key){

           tree->current = aux;
           return aux->value;

        }

        if(key < aux->key){

            if(!aux->left) return NULL;

            aux = aux->left;

        }
        else if(key > aux->key){

            if(!aux->right) return NULL;

            aux = aux->right;

        }

    }

}

void * firstBinaryTree(BinaryTree * tree){

    if(!tree || !tree->root) return NULL;

    TreeNode * aux = tree->root;
    while(aux->left){

        aux = aux->left;

    }

    tree->current = aux;
    return aux->value;

}

void * nextBinaryTree(BinaryTree * tree){

    if(!tree || !tree->current) return NULL;

    TreeNode * aux = tree->current; //creamos auxiliar para recorrer, nos situamos en el actual al que queremos avanzar

    if(!aux->right){ // si no hay dato a la derecha debemos subir

        if(!aux->parent) return NULL; //si estamos en el root y no hay datos a la derecha, estás en el ultimo, retornamos NULL
        aux = aux->parent; //de lo contrario subimos

        while(aux && aux->key < tree->current->key){ //mientras el padre sea menor que el dato actual seguimos subiendo

            aux = aux->parent;

        }

        if(!aux) return NULL; //si llegamos al final y no hay más datos estabamos en el ultimo, retornamos NULL
        tree->current = aux; // de lo contrario actualizamos el current

    }
    else{ // si es que hay dato a la derecha, nos vamos a el, y luego nos movemos a la izquierda hasta llegar al final

        aux = aux->right;

        while(aux->left){

            aux = aux->left;

        }

        tree->current = aux;

    }

    return aux->value; //retornamos el valor

}

void * eraseKeyBinaryTree(BinaryTree * tree, int key){

    if(!tree || !tree->root) return NULL;

    TreeNode * aux = tree->root; //creamos un aux para situarnos en la raiz

    while(1){ //creamos un ciclo "infinito", pondremos las condiciones de terminos en condicionales if

        if(aux->key == key) break; // si encontramos el dato cortamos el ciclo

        if(key < aux->key){

            if(!aux->left) return NULL; //si es que no encontramos el dato a la izquierda retornamos NULL
            aux = aux->left; //si la clave es menor entonces avanzamos a la izquierda

        }
        else if(key > aux->key){

            if(!aux->right) return NULL;
            aux = aux->right;
        }

    }

    void * value = aux->value; //aca vamos a igualar el valor del dato que vamos a eliminar
    //luego que encontramos el dato a eliminar hay que hacer el proceso de eliminacion

    //creamos una copia para ir recorriendo con el aux llamada mayor
    TreeNode * mayor = aux;

    //si el nodo que queremos eliminar tiene dos hijos, entonces lo reemplazamos por el mayor del sub arbol de la izquierda del nodo
    if(aux->left && aux->right){

        mayor=aux->left;

        while(mayor->right){

            mayor = mayor->right;
            //mayor se posicionará en el nodo mas grande, luego reemplazamos
        }

        mayor->parent = aux->parent; //hacemos que el padre del nodo eliminado apunte al que reemplazaremos

        //ahora haremos que el hijo correspondiente del padre apunte al nuevo nodo que intercambiamos
        if(aux->parent && aux->parent->right && aux->parent->right->key == aux->key ){

            aux->parent->right = mayor;

        }
        else if(aux->parent && aux->parent->left && aux->parent->left->key == aux->key){

            aux->parent->left = mayor;

        }

        //si uno de los nodos hijos del nodo a eliminar es de los que estamos haciendo el intercambio,
        //entonces no reemplazamos, de lo contrario si lo hacemos

        if(aux->left && aux->left->key != mayor->key){

            mayor->left = aux->left;

        }
        else if(aux->right && aux->right->key != mayor->key){

            mayor->right = aux->right;

        }

    }
    else{ //si es que solo tiene un hijo o no tiene, haremos el proceso dependiendo.

        if(aux->left){ //si tiene nodo a la izquierda, lo enlazamos con el padre

            aux->left->parent = aux->parent; //debemos conectar el hijo del nodo que vamos a eliminar con el padre del nodo a eliminar
            if(aux->parent->right && aux->parent->right->key == aux->key){

                aux->parent->right = aux->left; //debemos hacer apuntar el nuevo nodo a lo que apuntaba el nodo a eliminar

            }
            else if(aux->parent->left && aux->parent->left->key == aux->key){

                aux->parent->left = aux->left;

            }
        }
        else if(aux->right){ //hacemos el mismo proceso si el nodo está a la derecha

            aux->right->parent = aux->parent;
            if(aux->parent->right && aux->parent->right->key == aux->key){

                aux->parent->right = aux->left;

            }
            else if(aux->parent->left && aux->parent->left->key == aux->key){

                aux->parent->left = aux->left;

            }


        }
        else if(!aux->left && !aux->right){ //si no hay ni nodo a la izquierda ni a la derecha, lo eliminamos

            if(aux->parent->left && aux->parent->left->key == aux->key){

                aux->parent->left = NULL; //para eliminar debemos hacer NULL el puntero al dato que eliminariamos

            }
            else if(aux->parent->right && aux->parent->right->key == aux->key){

                aux->parent->right = NULL;

            }

        }

    }

    //limpiamos la memoria y retornamos el dato
    free(aux);
    return value;

}
