#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARIOTS 100
#define MAX_LENGTH 105
#define GEM_COUNT 12
#define REGULAR_TIER 12

// List of gemstones in descending order of priority (0 is highest)
const char *gem_ranking[GEM_COUNT] = {
    "lapis", "topaz", "tourmaline", "sapphire", "peridot", "ruby",
    "pearl", "emerald", "diamond", "aquamarine", "amethyst", "garnet"
};

// Structure to store chariot name and its precomputed sorting attributes
typedef struct {
    char name[MAX_LENGTH];
    int tier;
} Chariot;

// Helper to find the highest priority gemstone rank within the string
int get_gemstone_tier(const char *name) {
    char copy[MAX_LENGTH];
    strcpy(copy, name);

    // Convert string copy to lowercase and replace non-alphabetic characters with spaces
    // to cleanly isolate standalone words.
    for (int i = 0; copy[i] != '\0'; i++) {
        if (isalpha((unsigned char)copy[i])) {
            copy[i] = tolower((unsigned char)copy[i]);
        } else {
            copy[i] = ' ';
        }
    }

    int highest_priority = REGULAR_TIER;

    // Tokenize the string by spaces to parse individual words
    char *token = strtok(copy, " ");
    while (token != NULL) {
        for (int i = 0; i < GEM_COUNT; i++) {
            if (strcmp(token, gem_ranking[i]) == 0) {
                // If a gemstone is found, see if it has a higher priority (lower index number)
                if (i < highest_priority) {
                    highest_priority = i;
                }
            }
        }
        token = strtok(NULL, " ");
    }

    return highest_priority;
}

// Case-insensitive string comparison for tie-breaking
int case_insensitive_compare(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

// Comparator function used by qsort
int compare_chariots(const void *a, const void *b) {
    const Chariot *chariotA = (const Chariot *)a;
    const Chariot *chariotB = (const Chariot *)b;

    // Priority 1: Sort by Gemstone Tier (Ascending numeric rank)
    if (chariotA->tier != chariotB->tier) {
        return chariotA->tier - chariotB->tier;
    }

    // Priority 2: Standard case-insensitive alphabetical sort
    return case_insensitive_compare(chariotA->name, chariotB->name);
}

int main() {
    Chariot list[MAX_CHARIOTS];
    int count = 0;
    char buffer[MAX_LENGTH];

    // Read names until end of input or "END" string
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Strip trailing newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check for stopping condition
        if (strcmp(buffer, "END") == 0 || strcmp(buffer, "end") == 0 || strlen(buffer) == 0) {
            break;
        }

        // Store the name and compute its sorting rank properties
        strcpy(list[count].name, buffer);
        list[count].tier = get_gemstone_tier(buffer);
        count++;

        if (count >= MAX_CHARIOTS) break;
    }

    // Sort the list using our structural multi-level comparator
    qsort(list, count, sizeof(Chariot), compare_chariots);

    // Print sorted array outputs
    for (int i = 0; i < count; i++) {
        printf("%s\n", list[i].name);
    }

    return 0;
}
