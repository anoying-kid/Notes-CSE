#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int longestPalindromeSubseq(string s) {
        int n = s.size();

        string revs = s;
        reverse(revs.begin(), revs.end());

        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        
        for(int i=1; i<n+1; i++){
            for(int j=1; j<n+1; j++){
                if (s[i-1]==revs[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }

        return dp[n][n];
    }

int main()
{
    string a; cin>>a;
    cout<<longestPalindromeSubseq(a)<<endl;
    return 0;
}