#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    string str1, str2;
    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;
    int n = str1.length();
    int m = str2.length();
    int dp[n+1][m+1];
    for(int i = 0; i<=n; i++){
        dp[i][0] = 0;
    }
    for(int j = 0; j <=m; j++){
        dp[0][j]=0;
    }
    for (int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            
        }
    }
}