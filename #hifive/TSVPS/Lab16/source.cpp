#include <vector>
#include <limits>
#include <iostream>
using namespace std;

int knapsack2(const vector<int>& wts, const vector<int>& cost, int W)
{
    size_t n = wts.size();
    vector<vector<int> > dp(W + 1, vector<int>(n + 1, 0));

    for (size_t j = 1; j <= n; j++)
    {
        for (int w = 1; w <= W; w++)
        {
            if (wts[j - 1] <= w)
            {
                dp[w][j] = max(dp[w][j - 1], dp[w - wts[j - 1]][j - 1] + cost[j - 1]);
            }
            else
            {
                dp[w][j] = dp[w][j - 1];
            }
        }
    }
    return dp[W][n];
}

int main() {
    const int maxWeight = 11;

    vector<int> weights = { 3, 2, 5, 6 };
    vector<int> costs = { 1, 5, 3, 3 };

    cout << knapsack2(weights, costs, maxWeight);

    return 0;
}