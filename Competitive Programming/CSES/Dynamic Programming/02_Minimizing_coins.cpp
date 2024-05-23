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

    int n, target; cin>>n>>target;
    int coins[n]; seea(coins,0,n);
    vector<int> dp(target+1, 1e9);
    dp[0] = 0;
    for(auto coin: coins){
        for (int i=coin; i<target+1; i++){
            dp[i] = min(dp[i], dp[i-coin]+1);
        }
    }
    cout<<(dp[target]==1e9 ? -1 : dp[target]) <<endl;
    return 0;
}