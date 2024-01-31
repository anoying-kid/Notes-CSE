#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

bool subSetSum(vector<int> &arr, int sum){
	int n = arr.size();

	// Initialisation
	bool dp[n+1][sum+1];

	// Base Condition
	for(int i=0; i<n+1; i++){
		for(int j=0; j<sum+1; j++){
			if(i==0) dp[i][j] = false;
			if(j==0) dp[i][j] = true;
		}
	}

	// Choice Diagram
	for(int i=1; i<n+1; i++){
		for(int j=1; j<sum+1; j++){
			if(arr[i-1]<=j){
				dp[i][j] = dp[i-1][j-arr[i-1]] || dp[i-1][j];
			} else {
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	return dp[n][sum];
}

bool canPartition(vector<int> &arr, int n)
{
	// Write your code here.
	int sum = 0;
	for(auto num: arr){
		sum+=num;
	}

	// Base Condition
	if (sum%2!=0){
		return false;
	}else {
		return subSetSum(arr, sum/2);
	}
}


int main()
{
    int n; cin>>n;
    vector<int> arr; seev(arr, n);
    bool ans = canPartition(arr, n);
    // 0 = false, 1 = true;
    cout << ans << endl;
    return 0;
}