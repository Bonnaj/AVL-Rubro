#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

int height(struct AVLNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct AVLNode *newNode(int key)
{
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct AVLNode *rightRotate(struct AVLNode *y)
{
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct AVLNode *leftRotate(struct AVLNode *x)
{
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct AVLNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct AVLNode *insert(struct AVLNode *node, int key)
{
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct AVLNode *searchAVL(struct AVLNode *root, int key)
{
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return searchAVL(root->left, key);
    return searchAVL(root->right, key);
}

void generateRandomNumbers(int *arr, int count, int min, int max)
{
    for (int i = 0; i < count; i++)
    {
        arr[i] = min + rand() % (max - min + 1);
    }
}

int main()
{
    struct AVLNode *root = NULL;
    int randomNumbers[1000];
    clock_t start, end;
    double time_elapsed;

    srand(time(NULL));

    for (int i = 1; i <= 10000; i++)
    {
        root = insert(root, i);
    }

    generateRandomNumbers(randomNumbers, 1000, 1, 10000);

    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        searchAVL(root, randomNumbers[i]);
    }
    end = clock();

    time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time to search 1000 random elements: %f seconds\n", time_elapsed);

    return 0;
}
