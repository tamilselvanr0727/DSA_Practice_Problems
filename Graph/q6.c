#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 505
#define MAX_M 505

// adj[i][j] is true if boy i can dance with girl j
bool adj[MAX_N][MAX_M];
// match_girl[j] stores the boy matched with girl j (0 means unmatched)
int match_girl[MAX_M];
// visited[j] keeps track of girls visited during a single DFS phase
bool visited[MAX_M];

int n, m, k;

// DFS function to find an augmenting path
bool dfs(int boy) {
    for (int girl = 1; girl <= m; girl++) {
        // If there is an edge and the girl hasn't been visited in this path
        if (adj[boy][girl] && !visited[girl]) {
            visited[girl] = true;
            
            // If the girl is unmatched or her current partner can find another match
            if (match_girl[girl] == 0 || dfs(match_girl[girl])) {
                match_girl[girl] = boy;
                return true;
            }
        }
    }
    return false;
}

int main() {
    // Read n (boys), m (girls), and k (potential pairs)
    if (scanf("%d %d %d", &n, &m, &k) != 3) {
        return 0;
    }
    
    // Initialize adjacency matrix to false
    memset(adj, 0, sizeof(adj));
    // Initialize matches to 0 (unmatched)
    memset(match_girl, 0, sizeof(match_girl));
    
    // Read potential pairs
    for (int i = 0; i < k; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            adj[u][v] = true;
        }
    }
    
    int max_pairs = 0;
    // Try to find a match for each boy
    for (int boy = 1; boy <= n; boy++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(boy)) {
            max_pairs++;
        }
    }
    
    // Print the maximum number of pairs
    printf("%d\n", max_pairs);
    
    // Print each valid paired link
    for (int girl = 1; girl <= m; girl++) {
        if (match_girl[girl] != 0) {
            printf("%d %d\n", match_girl[girl], girl);
        }
    }
    
    return 0;
}
