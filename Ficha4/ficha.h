#ifndef RB
#define RB

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right, *p;
    int color;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

void RB_insert(Tree *T, Node *x);

Node* create_node(int key);
Tree* create_tree();
Node* tree_search(Node *x, int k);
Node* iterative_tree_search(Node *x, int k);
Node* tree_minimum(Node *x);
Node* tree_maximum(Node *x);
Node* tree_successor(Node *x);
void tree_insert(Tree *T, Node *z);
void transplant(Tree *T, Node *u, Node *v);
void tree_delete(Tree *T, Node *z);
void free_tree(Node *node);
#endif 