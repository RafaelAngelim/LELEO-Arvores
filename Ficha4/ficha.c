#include "ficha.h"
#define RED 1
#define BLACK 0
#define RED_COLOR "\033[1;31m"
#define BLACK_COLOR "\033[1;37m"
#define RESET_COLOR "\033[0m"


void print_tree(Node *node, int depth, char prefix) {
    if (node == NULL) {
        return;
    }
    print_tree(node->right, depth + 1, '/');

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    if (prefix != ' ') {
        printf("%c---", prefix);
    }

    if (node->color == RED) {
        printf(RED_COLOR "%d\n" RESET_COLOR, node->key);
    } else {
        printf(BLACK_COLOR "%d\n" RESET_COLOR, node->key);
    }

    print_tree(node->left, depth + 1, '\\');
}


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

int main() {
    Tree *T = create_tree();


    int keys[] = {10, 20, 30, 15, 25, 5, 1};
    int n = sizeof(keys) / sizeof(keys[0]);


    for (int i = 0; i < n; i++) {
        Node *new_node = create_node(keys[i]);
        RB_insert(T, new_node);

        printf("\ninserindo %d:\n", keys[i]);
        print_tree(T->root, 0, ' ');
    }

    return 0;
}