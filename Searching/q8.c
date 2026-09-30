#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 2048
#define MAX_WORDS 100

// Structure to hold a queue of words for each placeholder category
typedef struct {
    char *items[MAX_WORDS];
    int head;
    int tail;
} WordQueue;

// Initialize the queue
void init_queue(WordQueue *q) {
    q->head = 0;
    q->tail = 0;
}

// Add a word to the queue
void enqueue(WordQueue *q, const char *word) {
    if (q->tail < MAX_WORDS) {
        q->items[q->tail++] = strdup(word);
    }
}

// Get the front-most word and advance the queue head
char* dequeue(WordQueue *q) {
    if (q->head < q->tail) {
        return q->items[q->head++];
    }
    return NULL;
}

// Free allocated memory in the queue
void free_queue(WordQueue *q) {
    for (int i = 0; i < q->tail; i++) {
        free(q->items[i]);
    }
}

int main() {
    char template_str[MAX_LINE_LEN];
    
    // Read the first line containing the story sentence template
    if (!fgets(template_str, sizeof(template_str), stdin)) {
        return 0;
    }
    // Remove trailing newline character if present
    template_str[strcspn(template_str, "\r\n")] = '\0';

    // Queues for each token category
    WordQueue q_nouns, q_adverbs, q_verbs, q_adjectives;
    init_queue(&q_nouns);
    init_queue(&q_adverbs);
    init_queue(&q_verbs);
    init_queue(&q_adjectives);

    WordQueue *current_queue = NULL;
    char line[MAX_LINE_LEN];

    // Read the remaining lines from standard input
    while (fgets(line, sizeof(line), stdin)) {
        // Remove trailing spaces/newlines
        line[strcspn(line, "\r\n")] = '\0';
        
        // Strip trailing whitespaces manually if needed
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t')) {
            line[--len] = '\0';
        }

        if (len == 0) continue;
        if (strcmp(line, "END") == 0) break;

        // Determine category headers
        if (strcmp(line, "NOUNS") == 0) {
            current_queue = &q_nouns;
        } else if (strcmp(line, "ADVERBS") == 0) {
            current_queue = &q_adverbs;
        } else if (strcmp(line, "VERBS") == 0) {
            current_queue = &q_verbs;
        } else if (strcmp(line, "ADJECTIVES") == 0) {
            current_queue = &q_adjectives;
        } else {
            // If inside a section, add the word to the target queue
            if (current_queue != NULL) {
                enqueue(current_queue, line);
            }
        }
    }

    // Process the template to build the two substituted sentences
    for (int loop = 0; loop < 2; loop++) {
        char *ptr = template_str;
        
        while (*ptr != '\0') {
            // Check for known placeholder patterns
            if (strncmp(ptr, "[AJ]", 4) == 0) {
                char *w = dequeue(&q_adjectives);
                printf("%s", w ? w : "[AJ]");
                ptr += 4;
            } else if (strncmp(ptr, "[N]", 3) == 0) {
                char *w = dequeue(&q_nouns);
                printf("%s", w ? w : "[N]");
                ptr += 3;
            } else if (strncmp(ptr, "[AV]", 4) == 0) {
                char *w = dequeue(&q_adverbs);
                printf("%s", w ? w : "[AV]");
                ptr += 4;
            } else if (strncmp(ptr, "[V]", 3) == 0) {
                char *w = dequeue(&q_verbs);
                printf("%s", w ? w : "[V]");
                ptr += 3;
            } else {
                // Regular character, print as is
                putchar(*ptr);
                ptr++;
            }
        }
        printf("\n");
    }

    // Free all dynamically allocated string memory
    free_queue(&q_nouns);
    free_queue(&q_adverbs);
    free_queue(&q_verbs);
    free_queue(&q_adjectives);

    return 0;
}
