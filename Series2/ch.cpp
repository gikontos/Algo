#include <iostream>
#include <vector>
using namespace std;

int maximizeProfit(int N, int K, vector<int>& prices) {
    vector<vector<int>> dp(K + 1, vector<int>(N, 0));

    for (int k = 1; k <= K; ++k) {
        int maxDiff = -prices[0];

        for (int i = 1; i < N; ++i) {
            dp[k][i] = max(dp[k][i - 1], prices[i] + maxDiff);
            maxDiff = max(maxDiff, dp[k - 1][i] - prices[i]);
        }
    }

    return dp[K][N - 1];
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> prices(N);
    for (int i = 0; i < N; ++i) {
        cin >> prices[i];
    }

    int maxProfit = maximizeProfit(N, K, prices);
    cout << maxProfit << endl;

    return 0;
}
