#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define mod 1000000007
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin>>n;

    vector<int> dp(n+1, 0);
    dp[0] = 1;
    for(int sum=1; sum<=n; sum++){
        // Dice has 6 outcome
        for(int outcome=1; outcome<=6; outcome++){
            if (outcome<=sum){
                dp[sum] = (dp[sum] + dp[sum-outcome])%mod;
            }
        }
    }
    cout<<dp[n]<<endl;
    return 0;
}