#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int LCS(string s1, string s2, int m, int n){
	    int dp[m+1][n+1];
	    for(int i=0; i<m+1; i++){
	        for(int j=0; j<n+1; j++){
	            if (i==0 || j==0) dp[i][j] = 0;
	        }
	    }
	    for(int i=1; i<m+1; i++){
	        for(int j=1; j<n+1; j++){
	            if (s1[i-1]==s2[j-1]){
	                dp[i][j] = 1 + dp[i-1][j-1];
	            } else {
	                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
	            }
	        }
	    }
	    return dp[m][n];
	}
	
int minOperations(string str1, string str2) 
{ 
    // Your code goes here
    int m = str1.length(), n = str2.length();
    int lcs = LCS(str1, str2, m, n);
    return (m - lcs) + (n - lcs);
}

int main()
{
    string a, b; cin>>a>>b;
    cout<<minOperations(a,b)<<endl;
    return 0;
}