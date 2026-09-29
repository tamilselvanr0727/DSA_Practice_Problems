#include <stdio.h>
#include <string.h>

#define MAX_LIMIT 1005

int main() {
    char str[MAX_LIMIT];
    
    // Read the complete input line including spaces
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 0;
    }
    
    // Remove the trailing newline character if it exists
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    if (len > 0 && str[len - 1] == '\r') {
        str[len - 1] = '\0';
        len--;
    }

    // Fixed-size array initialized to 0 for all ASCII characters
    int frequency[256] = {0};

    // Count the frequency of each character
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char index = (unsigned char)str[i];
        frequency[index]++;
    }

    int max_count = -1;
    char max_char = 0;

    // Traverse the ASCII table from 0 to 255.
    // Iterating in ascending order automatically prefers the lower ASCII value in case of a tie.
    for (int i = 0; i < 256; i++) {
        // By using strict greater than (>), a higher ASCII character with the same 
        // frequency will not overwrite the lower ASCII character we already found.
        if (frequency[i] > max_count) {
            max_count = frequency[i];
            max_char = (char)i;
        }
    }

    // Output the character and its frequency separated by a space
    printf("%c %d\n", max_char, max_count);

    return 0;
}
