#include <stdio.h>
#include <stdlib.h>

// Structure for a BST Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert elements into the BST sequentially
struct Node* insert(struct Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Function to perform postorder traversal (Left -> Right -> Root)
void postorder(struct Node* root, int* isFirst) {
    if (root == NULL) {
        return;
    }
    
    postorder(root->left, isFirst);
    postorder(root->right, isFirst);
    
    // Manage proper space separation formatting
    if (*isFirst) {
        printf("%d", root->data);
        *isFirst = 0;
    } else {
        printf(" %d", root->data);
    }
}

// Function to free allocated memory
void freeTree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    
    // Read total number of elements
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        if (scanf("%d", &val) == 1) {
            root = insert(root, val);
        }
    }
    
    // Print Postorder Traversal
    int isFirst = 1;
    postorder(root, &isFirst);
    printf("\n");
    
    // Clean up allocated memory
    freeTree(root);
    
    return 0;
}
