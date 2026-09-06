#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n,w;
    cout << "Enter number of item: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> w;
    vector<int> weight(n+1);
    vector<int> profit(n+1);
    cout << "Enter weights: \n";
    for(int i = 1; i<= n; i++){
        cin >> weight[i];
    }
    cout << "Enter profits: \n";
    for(int i =1; i<=n; i++){
        cin >> profit[i];
    }
    vector<vector<int>> dp(n+1, vector<int>(w+1,0));
    for(int i = 1; i<= 1; i++){
        for(int W=1; W<=w; W++){
            if(weight[i]<=W){
                dp[i][w] = max(dp[i-1][w], profit[i]+dp[i-1][W - weight[i]]);
            }
            else{
                dp[i][w]=dp[i-1][W];
            }
        }
    }
    cout << "maximum profit = " << dp[n][w] << endl;
    return 0;
}