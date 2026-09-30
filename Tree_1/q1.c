#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the Binary Search Tree
struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->val = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Function to insert a new element into the BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return newNode(key);
    }
    if (key < root->val) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

// Function to print the pre-order traversal of the tree
void preorder(struct Node* root, int* isFirst) {
    if (root != NULL) {
        if (*isFirst) {
            printf("%d", root->val);
            *isFirst = 0;
        } else {
            printf(" %d", root->val);
        }
        preorder(root->left, isFirst);
        preorder(root->right, isFirst);
    }
}

// Helper function to free the allocated memory of the tree
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        if (scanf("%d", &val) == 1) {
            root = insert(root, val);
        }
    }
    
    int isFirst = 1;
    preorder(root, &isFirst);
    printf("\n");
    
    freeTree(root);
    return 0;
}
