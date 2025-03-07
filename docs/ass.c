#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1001
#define MAX_COMBINATIONS 1000

char** combinations;
int comb_count = 0;

int isUnique(char* str) {
    for(int i = 0; i < comb_count; i++) {
        if(strcmp(combinations[i], str) == 0) {
            return 0;
        }
    }
    return 1;
}

void findLCS(char* X, char* Y, int m, int n, int** dp, char* current, int index) {
    if(m == 0 || n == 0) {
        current[index] = '\0';
        if(strlen(current) == dp[strlen(X)][strlen(Y)] && isUnique(current)) {
            strcpy(combinations[comb_count++], current);
        }
        return;
    }
    if(X[m-1] == Y[n-1]) {
        current[index] = X[m-1];
        findLCS(X, Y, m-1, n-1, dp, current, index+1);
    } else {
        if(dp[m-1][n] >= dp[m][n-1]) {
            findLCS(X, Y, m-1, n, dp, current, index);
        }
        if(dp[m][n-1] >= dp[m-1][n]) {
            findLCS(X, Y, m, n-1, dp, current, index);
        }
    }
}

int** createDPTable(char* X, char* Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for(int i = 0; i <= m; i++) {
        dp[i] = (int*)calloc((n + 1), sizeof(int));
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(X[i-1] == Y[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }
    return dp;
}

int main() {
    char str1[MAX_LEN], str2[MAX_LEN];
    
    fgets(str1, MAX_LEN, stdin);
    fgets(str2, MAX_LEN, stdin);
    
    str1[strcspn(str1, "\n")] = 0;
    str2[strcspn(str2, "\n")] = 0;
    
    int m = strlen(str1);
    int n = strlen(str2);
    
    combinations = (char**)malloc(MAX_COMBINATIONS * sizeof(char*));
    for(int i = 0; i < MAX_COMBINATIONS; i++) {
        combinations[i] = (char*)malloc(MAX_LEN * sizeof(char));
    }
    
    int** dp = createDPTable(str1, str2);
    
    char current[MAX_LEN];
    findLCS(str1, str2, m, n, dp, current, 0);
    
    for(int i = 0; i < comb_count; i++) {
        int len = strlen(combinations[i]);
        for(int j = 0; j < len/2; j++) {
            char temp = combinations[i][j];
            combinations[i][j] = combinations[i][len-1-j];
            combinations[i][len-1-j] = temp;
        }
        printf("%s\n", combinations[i]);
    }
    
    printf("The length of the Longest Common Subsequence is: %d", dp[m][n]);
    
    for(int i = 0; i < MAX_COMBINATIONS; i++) {
        free(combinations[i]);
    }
    free(combinations);
    for(int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return 0;
}
