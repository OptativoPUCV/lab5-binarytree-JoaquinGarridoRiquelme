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
    /*
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
            
        else if(tree-> lower_than(key, aux -> pair -> key))
        {
            if(aux -> left == NULL)
            {
                aux -> left = nuevo_nodo;
                nuevo_nodo -> parent = aux;
                return;
            }
            else 
                aux = aux -> left;
        }
            
        else 
        {
            if(aux -> right == NULL)
            {
                aux -> right = nuevo_nodo;
                nuevo_nodo -> parent = aux;
                return;
            }
            else 
                aux = aux -> right;
        }
    }
    */
}

TreeNode * minimum(TreeNode * x)
{
    TreeNode *aux = x;
    while(aux-> left != NULL)
        aux = aux -> left;
    return aux;
}


void removeNode(TreeMap * tree, TreeNode* node) {

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
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
