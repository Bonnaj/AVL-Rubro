#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct RBNode
{
    int data;
    char color;
    struct RBNode *left, *right, *parent;
};

int rotations = 0;

struct RBNode *newRBNode(int data)
{
    struct RBNode *newNode = (struct RBNode *)malloc(sizeof(struct RBNode));
    newNode->data = data;
    newNode->color = 'R';
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void leftRotate(struct RBNode **root, struct RBNode *x)
{
    rotations++;
    struct RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(struct RBNode **root, struct RBNode *x)
{
    rotations++;
    struct RBNode *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void insertFixup(struct RBNode **root, struct RBNode *z)
{
    while (z != *root && z->parent->color == 'R')
    {
        struct RBNode *y;
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y != NULL && y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(root, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if (y != NULL && y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

void insert(struct RBNode **root, int data)
{
    struct RBNode *z = newRBNode(data);
    struct RBNode *y = NULL;
    struct RBNode *x = *root;

    while (x != NULL)
    {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFixup(root, z);
}

void deleteFixup(struct RBNode **root, struct RBNode *x)
{
}

struct RBNode *deleteNode(struct RBNode **root, struct RBNode *z)
{
    return *root;
}

int main()
{
    struct RBNode *root = NULL;
    int i;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (i = 1; i <= 10000; i++)
    {
        insert(&root, i);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Inserção: %f segundos, Rotações: %d\n", cpu_time_used, rotations);

    rotations = 0;
    start = clock();
    for (i = 1; i <= 10000; i++)
    {
        root = deleteNode(&root, root);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Remoção: %f segundos, Rotações: %d\n", cpu_time_used, rotations);

    return 0;
}
