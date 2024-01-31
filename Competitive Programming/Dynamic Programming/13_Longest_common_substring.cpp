#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int longestCommonSubstr (string s1, string s2, int n, int m)
    {
        // i==0 || j==0 dp[i][j] = 0;
        vector< vector<int>> dp(n+1, vector<int>(m+1, 0));

        int res = 0;
        for(int i=1; i<n+1; i++){
            for(int j=1; j<m+1; j++){
                if (s1[i-1]==s2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = 0;
                }
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }

int main()
{
    string a,b; cin>>a>>b;
    cout<< longestCommonSubstr(a,b, a.size(), b.size())<<endl;
    return 0;
}