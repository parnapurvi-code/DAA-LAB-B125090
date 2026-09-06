#include <bits/stdc++.h>
using namespace std;

// Function to compute minimum multiplication cost
int matrixChainMultiplication(int arr[], int N) {
    // dp[i][j] will store minimum cost of multiplying matrices from i to j
    vector<vector<int>> dp(N, vector<int>(N, 0));

    // L is chain length
    for (int L = 2; L < N; L++) {
        for (int i = 1; i < N - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + arr[i-1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][N-1];
}

int main() {
    int N = 4;
    int arr[] = {10, 30, 5, 60};

    cout << "Minimum number of multiplications: "
         << matrixChainMultiplication(arr, N) << endl;

    return 0;
}
