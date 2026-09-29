#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FESTIVALS 10005
#define MAX_NAME_LEN 15

// Structure to hold spending profiles for each distinct festival
typedef struct {
    char name[MAX_NAME_LEN];
    long long spendings[MAX_FESTIVALS];
    int count;
} Festival;

// Comparator to sort values in descending order
int compare_desc(const void *a, const void *b) {
    long long val_a = *(const long long *)a;
    long long val_b = *(const long long *)b;
    if (val_a < val_b) return 1;
    if (val_a > val_b) return -1;
    return 0;
}

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;

    // Dynamically tracking unique festival instances
    Festival *unique_festivals = (Festival *)malloc(sizeof(Festival) * n);
    int unique_count = 0;

    for (int i = 0; i < n; i++) {
        char current_name[MAX_NAME_LEN];
        long long current_spending;
        scanf("%s %lld", current_name, &current_spending);

        // Quick check to see if the festival already exists
        int found_index = -1;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(unique_festivals[j].name, current_name) == 0) {
                found_index = j;
                break;
            }
        }

        // If it's a new festival record, register it into our list
        if (found_index == -1) {
            strcpy(unique_festivals[unique_count].name, current_name);
            unique_festivals[unique_count].count = 0;
            found_index = unique_count;
            unique_count++;
        }

        // Append the spending under the mapped festival index
        int idx = unique_festivals[found_index].count;
        unique_festivals[found_index].spendings[idx] = current_spending;
        unique_festivals[found_index].count++;
    }

    long long max_spending = -1;
    char best_festival[MAX_NAME_LEN] = "";

    // Process every recorded festival to calculate the top 3 items
    for (int i = 0; i < unique_count; i++) {
        // Sort individual festival spendings descendingly
        qsort(unique_festivals[i].spendings, unique_festivals[i].count, sizeof(long long), compare_desc);

        // Sum up at most the 3 highest recorded spendings
        long long remembered_sum = 0;
        int limit = unique_festivals[i].count < 3 ? unique_festivals[i].count : 3;
        for (int k = 0; k < limit; k++) {
            remembered_sum += unique_festivals[i].spendings[k];
        }

        // Determine the absolute winner or resolve a lexicographical tie
        if (remembered_sum > max_spending) {
            max_spending = remembered_sum;
            strcpy(best_festival, unique_festivals[i].name);
        } else if (remembered_sum == max_spending) {
            if (strcmp(unique_festivals[i].name, best_festival) < 0) {
                strcpy(best_festival, unique_festivals[i].name);
            }
        }
    }

    printf("%s %lld\n", best_festival, max_spending);
    
    // Free allocated memory block to prevent leaks
    free(unique_festivals);
}

int main() {
    int t_cases;
    if (scanf("%d", &t_cases) == 1) {
        while (t_cases--) {
            solve();
        }
    }
    return 0;
}
