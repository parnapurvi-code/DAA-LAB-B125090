#include <iostream>
using namespace std;
int main(){
    int n;
    cout << "enter n: ";
    cin >> n;
    int dp[n+1];
    dp[0]=0;
    if (n>=1){
        dp[1] = 1;}
    for(int i = 2; i <= n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    cout << "The " << n << "the fibonacci number is " << dp[n] << endl;
    return 0;
}