#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

long long int count(int coins[], int n, int sum) {

        // code here.
    long long int dp[n+1][sum+1];

    for(int i=0; i<n+1; i++){
        for(int j=0; j<sum+1; j++){
            if(i==0) dp[i][j]=0;
            if(j==0) dp[i][j]=1;
        }
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<sum+1; j++){
            if(coins[i-1]<=j){
                dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
            } else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][sum];
    }

int main()
{
    int n, sum; cin>>n>>sum;
    
    return 0;
}