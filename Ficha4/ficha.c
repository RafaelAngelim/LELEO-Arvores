#include "ficha.h"
#define RED 1
#define BLACK 0

Node* create_node(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->p = NULL;
    node->color = RED; 
    return node;
}

Tree* create_tree() {
    Tree *T = (Tree*)malloc(sizeof(Tree));
    T->root = NULL;
    return T;
}

void left_rotate(Tree *T, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->p = x;
    y->p = x->p;
    if (x->p == NULL) T->root = y;
    else if (x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->left = x;
    x->p = y;
}

void right_rotate(Tree *T, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->p = x;
    y->p = x->p;
    if (x->p == NULL) T->root = y;
    else if (x == x->p->right) x->p->right = y;
    else x->p->left = y;
    
    y->right = x;
    x->p = y;
}


void RB_insert(Tree *T, Node *z) {
    tree_insert(T, z);  
    z->color = RED;     

    while (z != T->root && z->p->color == RED) {
        
        if (z->p == z->p->p->left) {
            Node *y = z->p->p->right;  // tio
            if (y != NULL && y->color == RED) {  // Caso 1
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {  // Caso 2
                    z = z->p;
                    left_rotate(T, z);
                }
                // Caso 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(T, z->p->p);
            }
        } else {  // Simétrico direito
            Node *y = z->p->p->left;  // Tio de z
            if (y != NULL && y->color == RED) {  // Caso 1
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {  // Caso 2
                    z = z->p;
                    right_rotate(T, z);
                }
                // Caso 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(T, z->p->p);
            }
        }
    }
    T->root->color = BLACK;  
}

void tree_insert(Tree *T, Node *z) {
    Node *y = NULL;
    Node *x = T->root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == NULL) {
        T->root = z;  
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}
