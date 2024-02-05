#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define mod 1000000007
using namespace std;

// Mod is used for GFG optimisation
int MOD = 1000000007;

int solve(string& s, int i, int j, bool isTrue, vector<vector<vector<int>>>& dp) {
        if (i > j) return 0;
        if (i == j) return (s[i] == (isTrue ? 'T' : 'F'));
        if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];

        int ans = 0;
        for (int k = i + 1; k <= j - 1; k += 2) {
            int lt = solve(s, i, k - 1, true, dp);
            int lf = solve(s, i, k - 1, false, dp);
            int rt = solve(s, k + 1, j, true, dp);
            int rf = solve(s, k + 1, j, false, dp);

            if (s[k] == '&') {
                if (isTrue) ans = (ans + ((lt * rt) % MOD)) % MOD;
                else ans = (ans + ((lt * rf) % MOD + (lf * rt) % MOD + (lf * rf) % MOD) % MOD) % MOD;
            }
            else if (s[k] == '|') {
                if (isTrue) ans = (ans + ((lt * rt) % MOD + (lt * rf) % MOD + (lf * rt) % MOD) % MOD) % MOD;
                else ans = (ans + (lf * rf) % MOD) % MOD;
            }
            else if (s[k] == '^') {
                if (isTrue) ans = (ans + ((lt * rf) % MOD + (lf * rt) % MOD) % MOD) % MOD;
                else ans = (ans + ((lt * rt) % MOD + (lf * rf) % MOD) % MOD) % MOD;
            }
        }
        return dp[i][j][isTrue] = ans%mod;
    }

int main()
{
    string s; cin>>s;
    int n = s.length();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
    cout<< solve(s, 0, n - 1, true, dp);
    return 0;
}