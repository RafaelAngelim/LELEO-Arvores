#include "ficha.h"


Node* create_node(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = node->p = NULL;
    return node;
}

Tree* create_tree() {
    Tree *T = (Tree*)malloc(sizeof(Tree));
    if (T != NULL) {
        T->root = NULL;
    }
    return T;
}

Node* tree_search(Node *x, int k) {
    if (x == NULL || k == x->key)
        return x;
    if (k < x->key)
        return tree_search(x->left, k);
    else
        return tree_search(x->right, k);
}

Node* iterative_tree_search(Node *x, int k) {
    while (x != NULL && k != x->key) {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node* tree_minimum(Node *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

Node* tree_maximum(Node *x) {
    while (x->right != NULL)
        x = x->right;
    return x;
}

Node* tree_successor(Node *x) {
    if (x->right != NULL)
        return tree_minimum(x->right);
    Node *y = x->p;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

void tree_insert(Tree *T, Node *z) {
    Node *y = NULL;
    Node *x = T->root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
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

void transplant(Tree *T, Node *u, Node *v) {
    if (u->p == NULL) {
        T->root = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    if (v != NULL) {
        v->p = u->p;
    }
}

void tree_delete(Tree *T, Node *z) {
    if (z->left == NULL) {
        transplant(T, z, z->right);
    } else if (z->right == NULL) {
        transplant(T, z, z->left);
    } else {
        Node *y = tree_minimum(z->right);
        if (y != z->right) {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
    }
}

void free_tree(Node *node) {
    if (node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

int main() {
    Tree *T = create_tree();
    if (T == NULL) {
        printf("Falha ao criar a árvore.\n");
        return 1;
    }

    int keys[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    for (int i = 0; i < 11; i++) {
        Node *node = create_node(keys[i]);
        tree_insert(T, node);
    }

    Node *result = tree_search(T->root, 13);
    if (result != NULL)
        printf("Node with key 13 found: %p\n", result);
    else
        printf("Node with key 13 not found.\n");

    tree_delete(T, result);
    result = tree_search(T->root, 13);
    if (result != NULL)
        printf("Node with key 13 still found: %p\n", result);
    else
        printf("Node with key 13 deleted.\n");

    free_tree(T->root);
    free(T);
    return 0;
}
