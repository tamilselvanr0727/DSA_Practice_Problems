#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int preorder[MAX_N];
int inorder[MAX_N];
int postorder[MAX_N];

// Direct mapping array to simulate a hash map for O(1) index lookups.
// Since nodes are numbered 1 to n, size MAX_N is sufficient.
int inorder_pos[MAX_N];

int pre_idx = 0;
int post_idx = 0;

/**
 * Recursively builds the postorder traversal list.
 * @param in_start Start index of the current subtree in the inorder array
 * @param in_end   End index of the current subtree in the inorder array
 */
void build_postorder(int in_start, int in_end) {
    // Base case: if the subtree bounds are invalid
    if (in_start > in_end) {
        return;
    }

    // The current element in preorder is the root of this subtree
    int root_val = preorder[pre_idx++];

    // Find the position of this root in the inorder array in O(1) time
    int root_in_idx = inorder_pos[root_val];

    // Recursively traverse the left subtree
    build_postorder(in_start, root_in_idx - 1);

    // Recursively traverse the right subtree
    build_postorder(root_in_idx + 1, in_end);

    // Append the root node (Postorder: Left -> Right -> Root)
    postorder[post_idx++] = root_val;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // Read the preorder traversal input
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

    // Read the inorder traversal input and map each value to its index
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
        inorder_pos[inorder[i]] = i;
    }

    // Begin the recursive traversal
    build_postorder(0, n - 1);

    // Print the final postorder array space-separated
    for (int i = 0; i < post_idx; i++) {
        printf("%d%c", postorder[i], (i == post_idx - 1) ? '\n' : ' ');
    }

    return 0;
}
