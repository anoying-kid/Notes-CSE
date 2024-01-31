#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	// Intialisation
	int dp[n+1][maxWeight+1];

	// Base Condition
	for(int i=0; i<n+1; i++){
		for(int j=0; j<maxWeight+1; j++){
			if (i==0 || j==0) dp[i][j] = 0;
		}
	}

	// Choice Diagram
	for(int i=1; i<n+1; i++){
		for(int j=1; j<maxWeight+1; j++){
			if(weight[i-1] <= j){
				dp[i][j] = max(value[i-1] + dp[i-1][j-weight[i-1]], dp[i-1][j]);
			} else {
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	return dp[n][maxWeight];
}

int main()
{
    int n, w; cin>>n>>w;
    vector<int> weights, values;
    seev(weights, n);
    seev(values, n);
    
    cout<<knapsack(weights, values, n, w);

    return 0;
}