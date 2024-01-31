#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

// Use this if array has 0 in it

// int countSubset(vector<int>& arr, int k)
// {
// 	// Write your code here.
// 	int mod = 1e9 + 7;

// 	// Wrong Test Case
// 	// 3 4
// 	// 0 1 3

// 	int n = arr.size();

// 	// Initialisation
// 	int dp[n+1][k+1];

	// bool gotZero = false; //changed

// 	// Base Condition
// 	for(int i=0; i<n+1; i++){
		// for(int j=0; j<k+1; j++){
		// 	if(i==0) dp[i][j] = 0;
		// 	if(j==0) { //changed
		// 		if(gotZero || i!=0 && i!=n && arr[i-1]==0){
        //             gotZero = true;
        //             dp[i][j] = 2;
        //         }
// 				else dp[i][j]=1;
// 			}
// 		}
// 	}

// 	// Choice Diagram
// 	for(int i=1; i<n+1; i++){
// 		for(int j=1; j<k+1; j++){
// 			if (arr[i-1]<=j){
// 				dp[i][j] = (dp[i-1][j-arr[i-1]] + dp[i-1][j])%mod;
// 			} else {
// 				dp[i][j] = dp[i-1][j];
// 			}
// 		}
// 	}

// 	return dp[n][k];
// }

int countSubset(vector<int>& arr, int k)
{
	// Write your code here.
	int mod = 1e9 + 7;

	// Wrong Test Case
	// 3 4
	// 0 1 3

	int n = arr.size();

	// Initialisation
	int dp[n+1][k+1];

	// Base Condition
	for(int i=0; i<n+1; i++){
		for(int j=0; j<k+1; j++){
			if(i==0) dp[i][j] = 0;
			if(j==0) dp[i][j]=1;
		}
	}

	// Choice Diagram
	for(int i=1; i<n+1; i++){
		for(int j=1; j<k+1; j++){
			if (arr[i-1]<=j){
				dp[i][j] = (dp[i-1][j-arr[i-1]] + dp[i-1][j])%mod;
			} else {
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	return dp[n][k];
}


int main()
{
    int n,k; cin>>n>>k;
    vector<int> arr; seev(arr, n);

    cout<<countSubset(arr, k)<<endl;;
    return 0;
}