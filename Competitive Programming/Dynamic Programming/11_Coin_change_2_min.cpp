#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

 int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        int dp[n+1][amount+1];

        // initialization
        for(int i=0; i<n+1; i++){
            for(int j=0; j<amount+1; j++){
                if (i==0) dp[i][j] = INT_MAX - 1;
                if (j==0) dp[i][j] = 0;
                if (i==1){
                    if (j%coins[i-1]==0){
                        dp[i][j] = j/coins[i-1];
                    } else {
                        dp[i][j] = INT_MAX - 1;
                    }
                }
            }
        }

        // code
        for(int i=1; i<n+1; i++){
            for(int j=1; j<amount+1; j++){
                if (coins[i-1]<=j){
                    dp[i][j] = min(dp[i-1][j], 1+dp[i][j-coins[i-1]]);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return (dp[n][amount]!=INT_MAX-1) ? dp[n][amount] : -1;
    }

int main()
{
    int n, x; cin>>n>>x;
    vector<int> coins; seev(coins, n);

    cout<<coinChange(coins, x)<<endl;

    return 0;
}