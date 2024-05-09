#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"
#include <stdbool.h>

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2))
{
    TreeMap *arbol = malloc(sizeof(TreeMap));
    arbol-> root = NULL;
    arbol-> current = NULL;
    arbol->lower_than = lower_than;
    return arbol;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    TreeNode *nuevo_nodo = createTreeNode(key,value);
    
    //Comprobamos que el arbol tenga raiz
    if(tree -> root == NULL)
    {
        tree -> root = nuevo_nodo;
        tree -> current = nuevo_nodo;
        return;
    }

    //Seguimos con el proceso sabiendo que no es la raiz,
    //ademas creamos un auxiliar que en la raiz para avanzar 
    TreeNode *aux = tree -> root;
    while(true)
    {
        //Comprobamos que el dato no se encuentre repetido
        if(is_equal(tree, aux -> pair -> key, key)) 
        {
            free(nuevo_nodo);
            return;
        }
        //Encontramos un espacio disponible para insertar   
        if(aux->left == NULL || aux->right == NULL) break;
            
        if(tree-> lower_than(aux-> pair->key, key)) aux = aux -> right;

        else aux = aux ->left;
    }
    //Ya teniendo identificadas las posiciones libres, insertamos
    if(aux->left == NULL) aux->left = nuevo_nodo;

    else aux->right = nuevo_nodo;

    nuevo_nodo -> parent = aux;
    tree -> current = nuevo_nodo;
}

TreeNode * minimum(TreeNode * x)
{
    TreeNode *aux = x;
    while(aux-> left != NULL)
        aux = aux -> left;
    return aux;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    //Si el nodo a borra es la raiz
    if(tree->root == node) tree->root = NULL;
    
    //Variables para manipular las conexiones con mayor facilidad
    TreeNode *nodo_borrar;
    TreeNode *padre = nodo_borrar -> parent;
    TreeNode *hijo = NULL;
    
    //Nodo sin hijos
    if(nodo_borrar ->left == NULL && nodo_borrar ->right == NULL)
    {
        if(padre -> left == nodo_borrar)
            padre -> left = NULL;
        else
            padre -> right = NULL;
        return;
    }

    //Nodo con un hijo(Cubriendo el caso anterior sabemos que tiene al menos 1 hijo)
    else if(nodo_borrar -> left == NULL || nodo_borrar -> right == NULL)
    {
        //Movemos las conexiones de nuestros nodos segun la direccion indicada
        if(nodo_borrar -> left != NULL)
            hijo = nodo_borrar -> left;
        else
            hijo = nodo_borrar -> right;
        if(padre ->left == nodo_borrar)
            padre -> left = hijo;
        else
            padre -> right = hijo;
        hijo -> parent = padre;
        return;
    }

    //Nodo con 2 hijos(Cubriendo los anteriores casos sabemos que hay 2 hijos)
    //Para esto reemplazaremos el nodo a eliminar por su descendiente menor hacia la derecha
    else if(nodo_borrar -> left != NULL && nodo_borrar -> right != NULL)
    {
        TreeNode *aux = minimum(nodo_borrar->right);
        removeNode(tree, aux);
        nodo_borrar->pair = aux->pair;
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key)
{
    TreeNode *aux = tree -> root;

    while(aux != NULL)
        {
            if(is_equal(tree, aux-> pair -> key, key))
            {
                tree-> current = aux;
                return aux -> pair;
            }
                
            else if(tree->lower_than(key, aux->pair->key))
            {
                    aux = aux -> left;
            }

            else
            {
                    aux = aux->right;
            }
        }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode *primero = minimum(tree->root);
    tree -> current = primero;
    return primero->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
