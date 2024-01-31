#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        // base condition
        int dp[m+1][n+1];

        // initialization
        for(int i=0; i<m+1; i++){
            for(int j=0; j<n+1; j++){
                if (i==0 || j==0) dp[i][j] = 0;
            }
        }

        // code
        for(int i=1; i<m+1; i++){
            for(int j=1; j<n+1; j++){
                if (text1[i-1] == text2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[m][n];
    }

int main()
{
    string a, b; cin>>a>>b;
    int m = a.size(), n = b.size();
    int ans = m + n - longestCommonSubsequence(a,b);
    cout<<ans<<endl;
    return 0;
}