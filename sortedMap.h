#ifndef SORTEDMAP_H
#define SORTEDMAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    void * value;
    struct TreeNode * left;
    struct TreeNode * right;
    struct TreeNode * parent;
} TreeNode;

typedef struct BinaryTree {
    TreeNode * root; // Puntero a la raíz.
    TreeNode * current; // Puntero para poder recorrer el árbol.
} BinaryTree;

//crea un nodo de arbol binario y lo retorna
TreeNode * createTreeNode(int, void *);

//crea un arbol binario y lo retorna
BinaryTree * createBinaryTree();

//inserta en un arbol binario de busqueda (ordenado)
void insertBinaryTree(BinaryTree *, int, void *);

//busca un dato en un arbol binario de busqueda
void * searchBinaryTree(BinaryTree *, int);

//retorna el valor del primer dato del arbol binario
void * firstBinaryTree(BinaryTree *);

//retorna el valor del dato siguiente al current
void * nextBinaryTree(BinaryTree *);

//elimina el dato con la clave ingresada
void * eraseKeyBinaryTree(BinaryTree *, int);

#endif
