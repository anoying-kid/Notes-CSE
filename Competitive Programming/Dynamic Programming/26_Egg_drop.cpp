#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define mod 1000000007
using namespace std;

// Gives TLE
// int solve(int eggs, int floor, vector<vector<int>> &dp){
//     if (eggs == 1 || floor == 0 || floor == 1) {
//         return dp[eggs][floor] = floor;
//     }
//     if (dp[eggs][floor]!=-1){
//         return dp[eggs][floor];
//     }
//     int ans = INT_MAX;
//     for(int k=1; k<=floor; k++){
//         if (dp[eggs-1][k-1]==-1){
//             dp[eggs-1][k-1] = solve(eggs-1, k-1, dp);
//         }
//         if (dp[eggs][floor-k]==-1){
//             dp[eggs][floor-k] = solve(eggs, floor-k, dp);
//         }
//         int temp = 1 + max( dp[eggs-1][k-1], dp[eggs][floor-k]);
//         ans = min(ans, temp);
//     }
//     return dp[eggs][floor] = ans;
// }
// int superEggDrop(int k, int n) {
//     vector<vector<int>> dp(k+1, vector<int>(n+1, -1));
//     return solve(k, n, dp);
// }

// 2d array
// int superEggDrop(int k, int n) {
//     vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

//     int attempts = 0;
//     while (dp[k][attempts] < n) {
//         attempts++;
//         for (int eggs = 1; eggs <= k; eggs++) {
//             dp[eggs][attempts] = 1 + dp[eggs - 1][attempts - 1] + dp[eggs][attempts - 1];
//         }
//     }

//     return attempts;
// }

// 1d dp
int superEggDrop(int k, int n) {
    vector<int> dp(k+1, 0);
    int attempts = 0;
    while(dp[k] < n){
        attempts++;
        for(int eggs = k; eggs>0; eggs--){
            dp[eggs] += 1 + dp[eggs-1];
        }
    }
    return attempts;
}


int main()
{
    int k, n; cin>>k>>n;
    cout<<superEggDrop(k, n)<<endl;
    return 0;
}