#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* findTheString(int** lcp, int lcpSize, int* lcpColSize) {
    int n = lcpSize;

    // Step 1: Check diagonal
    for (int i = 0; i < n; i++) {
        if (lcp[i][i] != n - i) {
            char* res = (char*)malloc(1);
            res[0] = '\0';
            return res;
        }
    }

    // Step 2: Allocate result string
    char* word = (char*)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) word[i] = '?';
    word[n] = '\0';

    char ch = 'a';

    // Step 3: Build string
    for (int i = 0; i < n; i++) {
        if (word[i] == '?') {
            if (ch > 'z') {
                char* res = (char*)malloc(1);
                res[0] = '\0';
                return res;
            }

            for (int j = i; j < n; j++) {
                if (lcp[i][j] > 0) {
                    word[j] = ch;
                }
            }
            ch++;
        }
    }

    // Step 4: Validate using DP
    int** dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (word[i] == word[j]) {
                if (i + 1 < n && j + 1 < n)
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                else
                    dp[i][j] = 1;
            } else {
                dp[i][j] = 0;
            }

            if (dp[i][j] != lcp[i][j]) {
                // free memory
                for (int k = 0; k < n; k++) free(dp[k]);
                free(dp);

                char* res = (char*)malloc(1);
                res[0] = '\0';
                return res;
            }
        }
    }

    // free dp
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);

    return word;
}