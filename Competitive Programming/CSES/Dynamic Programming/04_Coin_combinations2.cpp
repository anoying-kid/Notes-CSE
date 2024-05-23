#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define mod 1000000007
#define inf INT_MAX
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,x; cin>>n>>x;
    vector<int> coins; seev(coins, n);

    vector<int> dp(x+1, 0);
    dp[0] =1;

    // Iterating over coins to dont get same number again
    for(int i=0; i<n; i++){
        for(int j=1; j<=x; j++){
            if(coins[i]<=j){
                dp[j] = (dp[j]+dp[j-coins[i]])%mod;
            }
        }
    }
    cout<<dp[x]<<endl;
    return 0;
}