#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);
    
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    
    return root;
}

Node* isolation(int k) {
    int v;
    scanf("%d", &v);
    Node* root = createNode(v);

    for (int i = 1; i < k; i++) {
        scanf("%d", &v);
        root = insert(root, v); 
    }
    return root;
}

void serializeTree(Node* root, char* buffer) {
    if (root == NULL) {
        strcat(buffer, "N");
        return;
    }
    strcat(buffer, "(");
    serializeTree(root->left, buffer);
    strcat(buffer, ")");
    strcat(buffer, "X");
    strcat(buffer, "(");
    serializeTree(root->right, buffer);
    strcat(buffer, ")");
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int compare(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    char* tree_structures[n];

    for (int i = 0; i < n; i++) {
        Node* root = isolation(k);

        tree_structures[i] = (char*)malloc(500 * sizeof(char));
        tree_structures[i][0] = '\0';

        serializeTree(root, tree_structures[i]);

        freeTree(root);
    }

    qsort(tree_structures, n, sizeof(char*), compare);

    int unique_count = 1;
    for (int i = 1; i < n; i++) {
        if (strcmp(tree_structures[i], tree_structures[i - 1]) != 0) {
            unique_count++;
        }
    }

    printf("%d\n", unique_count);

    for (int i = 0; i < n; i++) {
        free(tree_structures[i]);
    }

    return 0;
}
