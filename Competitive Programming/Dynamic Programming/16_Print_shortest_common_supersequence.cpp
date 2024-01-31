#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size(), n = str2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=1; i<m+1; i++){
            for(int j=1; j<n+1; j++){
                if (str1[i-1]==str2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        // From Matrix
        string s = "";
        int i = m, j=n;
        while(i>0 && j>0){
            if (str1[i-1]==str2[j-1]){
                s += str1[i-1];
                i--;
                j--;
            } else if(dp[i][j-1]>dp[i-1][j]){
                s += str2[j-1];
                j--;
            } else {
                s += str1[i-1];
                i--;
            }
        }

        // If one string is empty or we stop at 0 before its required
        while(i>0){
            s += str1[i-1];
            i--;
        }
        while(j>0){
            s += str2[j-1];
            j--;
        }
        reverse(s.begin(), s.end());
        return s;
    }

int main()
{
    string a, b; cin>>a>>b;
    cout<<shortestCommonSupersequence(a,b)<<endl;
    return 0;
}