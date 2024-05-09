#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

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
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->lower_than = lower_than;
    new->root = NULL;
    new->current = NULL;
    return new;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL || tree->root == NULL)
    {
        tree->root = createTreeNode(key, value);
        tree->current = tree->root;
        return;
    }
    TreeNode * aux = tree->root;
    while (aux != NULL)
        {
            if (tree->lower_than(key, aux->pair->key) == 1)
            {
                if (aux->left == NULL)
                {
                    aux->left = createTreeNode(key, value);
                    aux->left->parent = aux;
                    tree->current = aux->left;
                    return;
                }
                else aux = aux->left;
            }
            else
            {
                if (aux->right == NULL)
                {
                    aux->right = createTreeNode(key, value);
                    aux->right->parent = aux;
                    tree->current = aux->right;
                    return;
                }
                else aux = aux->right;
            }
            
        }
    
}

TreeNode * minimum(TreeNode * x)
{
    while (x->left != NULL)
        x = x->left;
    if(x->left == NULL) return x;
    return minimum(x->left);
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if(tree == NULL || tree->root == NULL || node == NULL) return;
    if(node->left == NULL && node->right == NULL)
    {
        if(node->parent->left == node)
        {
            node->parent->left = NULL;
            if(node->parent->right == node) 
            {
                node->parent->right = NULL;
                free(node);
            }
        }
    }
    if(node->left != NULL && node->right == NULL)
    {
        if(node->parent->left == node)
        {
            node->parent->left = node->left;
            if(node->parent->right == node)
            {
                node->parent->right = node->left; 
                free(node->pair);
                free(node->left);
                free(node->right);
                free(node);
            }
        }
    }
    if(node->left == NULL && node->right != NULL)
    {
        if(node->parent->left == node)
        {
            node->parent->left = node->right;
            if(node->parent->right == node)
            {
                node->parent->right = node->right;
                free(node->pair);
                free(node->left);
                free(node->right);
                free(node);
            }
        }
    }
    if(node->left != NULL && node->right != NULL)
    {
        TreeNode * min = minimum(node->right);
        node->pair->key = min->pair->key;
        node->pair->value = min->pair->value;
        removeNode(tree, min);
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
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * aux = tree->root;
    while (aux != NULL)
        {
            if (is_equal(tree, key, aux->pair->key) == 1)
            {
                tree->current = aux;
                return aux->pair;
            }
            if (tree->lower_than(key, aux->pair->key) == 1) aux = aux->left;
            else aux = aux->right;
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
