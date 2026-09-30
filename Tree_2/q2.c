#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to hold elements with a unique tracking ID
typedef struct {
    long long value;
    int id;
} HeapNode;

// Global array to track if an element ID is still valid in the array
bool *valid;

// --- MIN HEAP IMPLEMENTATION ---
typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *h = (MinHeap*)malloc(sizeof(MinHeap));
    h->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void pushMin(MinHeap *h, long long val, int id) {
    h->data[h->size].value = val;
    h->data[h->size].id = id;
    int i = h->size;
    h->size++;
    while (i != 0 && h->data[i].value < h->data[(i - 1) / 2].value) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void minHeapify(MinHeap *h, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < h->size && h->data[left].value < h->data[smallest].value) smallest = left;
    if (right < h->size && h->data[right].value < h->data[smallest].value) smallest = right;
    if (smallest != idx) {
        swap(&h->data[idx], &h->data[smallest]);
        minHeapify(h, smallest);
    }
}

HeapNode popMin(MinHeap *h) {
    HeapNode root = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    minHeapify(h, 0);
    return root;
}

// --- MAX HEAP IMPLEMENTATION ---
typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap *h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void pushMax(MaxHeap *h, long long val, int id) {
    h->data[h->size].value = val;
    h->data[h->size].id = id;
    int i = h->size;
    h->size++;
    while (i != 0 && h->data[i].value > h->data[(i - 1) / 2].value) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void maxHeapify(MaxHeap *h, int idx) {
    int greatest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < h->size && h->data[left].value > h->data[greatest].value) greatest = left;
    if (right < h->size && h->data[right].value > h->data[greatest].value) greatest = right;
    if (greatest != idx) {
        swap(&h->data[idx], &h->data[greatest]);
        maxHeapify(h, greatest);
    }
}

HeapNode popMax(MaxHeap *h) {
    HeapNode root = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    maxHeapify(h, 0);
    return root;
}

// --- MAIN SOLVER ---
int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    // Up to 2 * n total insertions can happen across operations
    int max_entries = 2 * n + 2;
    valid = (bool*)calloc(max_entries, sizeof(bool));

    MinHeap *min_h = createMinHeap(max_entries);
    MaxHeap *max_h = createMaxHeap(max_entries);

    long long current_sum = 0;
    int entry_count = 0;

    for (int i = 0; i < n; i++) {
        long long val;
        scanf("%lld", &val);
        current_sum += val;
        
        pushMin(min_h, val, entry_count);
        pushMax(max_h, val, entry_count);
        valid[entry_count] = true;
        entry_count++;
    }

    // Allocate lookup array for results
    long long *precomputed_sums = (long long*)malloc(sizeof(long long) * n);
    precomputed_sums[0] = current_sum;

    for (int k = 1; k < n; k++) {
        // Clear lazy-deleted/invalid elements from top of Min-Heap
        while (min_h->size > 0 && !valid[min_h->data[0].id]) {
            popMin(min_h);
        }
        // Clear lazy-deleted/invalid elements from top of Max-Heap
        while (max_h->size > 0 && !valid[max_h->data[0].id]) {
            popMax(max_h);
        }

        if (min_h->size == 0 || max_h->size == 0) break;

        HeapNode smallest_node = popMin(min_h);
        HeapNode greatest_node = popMax(max_h);

        // Mark the pulled nodes as physically out of consideration
        valid[smallest_node.id] = false;
        valid[greatest_node.id] = false;

        // Compute replacement element
        long long diff = greatest_node.value - smallest_node.value;

        // Insert new element into heaps
        pushMin(min_h, diff, entry_count);
        pushMax(max_h, diff, entry_count);
        valid[entry_count] = true;
        entry_count++;

        // Mathematical optimization: Total array sum drops by 2 * smallest
        current_sum -= 2 * smallest_node.value;
        precomputed_sums[k] = current_sum;
    }

    // Process and answer queries in O(1)
    for (int i = 0; i < q; i++) {
        int k;
        scanf("%d", &k);
        printf("%lld\n", precomputed_sums[k]);
    }

    // Clean up memory
    free(min_h->data); free(min_h);
    free(max_h->data); free(max_h);
    free(valid);
    free(precomputed_sums);

    return 0;
}
