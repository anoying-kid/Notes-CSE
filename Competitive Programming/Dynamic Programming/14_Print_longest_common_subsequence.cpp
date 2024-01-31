#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

string findLCS(int n, int m,string &s1, string &s2){
	// Write your code here.
	int dp[n+1][m+1];
	for(int i=0; i<n+1; i++){
		for(int j=0; j<m+1; j++){
			if (i==0 || j==0) dp[i][j] = 0;
		}
	}
	for(int i=1; i<n+1; i++){
		for(int j=1; j<m+1; j++){
			if(s1[i-1]==s2[j-1]){
				dp[i][j] = 1 + dp[i-1][j-1];
			} else{
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}

    // Above same for finding LCS matrix 
	int i=n, j=m;
	string s = "";
	while(i>0 && j>0){
		if(s1[i-1]==s2[j-1]){
			s+=s1[i-1];
			i--;
			j--;
		} else {
			if (dp[i][j-1]>dp[i-1][j]){
				j--;
			} else {
				i--;
			}
		}
	}
	reverse(s.begin(), s.end());
	return s;
}

int main()
{
    
    return 0;
}