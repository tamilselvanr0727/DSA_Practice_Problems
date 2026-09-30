#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char varName[10];
    char valStr[50];
    
    double M = 0.0, D = 0.0, X = 0.0;
    int hasM = 0, hasD = 0, hasX = 0;
    char missing = ' ';

    // Read lines until End-Of-File (EOF)
    while (scanf("%s %s", varName, valStr) == 2) {
        char var = varName[0];
        
        if (strcmp(valStr, "?") == 0) {
            missing = var;
        } else {
            double value = atof(valStr);
            if (var == 'M') {
                M = value;
                hasM = 1;
            } else if (var == 'D') {
                D = value;
                hasD = 1;
            } else if (var == 'X') {
                X = value;
                hasX = 1;
            }
        }
    }

    // Compute the missing value based on the formula: M = -d * x
    if (missing == 'X') {
        X = M / (-D);
        printf("x %.2f\n", X);
    } else if (missing == 'D') {
        D = M / (-X);
        printf("d %.2f\n", D);
    } else if (missing == 'M') {
        M = -D * X;
        printf("m %.2f\n", M);
    }

    return 0;
}
