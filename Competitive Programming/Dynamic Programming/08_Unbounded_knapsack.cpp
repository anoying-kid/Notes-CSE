#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight){
    // Write Your Code Here.

    // Inititalisation
    vector<vector<int>> dp(n+1, vector<int>(w+1, 0));

    // // // Base condition is not needed as we already filled dp with 0;

    // // Base condition
    // for (int i=0; i<n+1; i++){
    //     for(int j=0; j<w+1; j++){
    //         if (i==0 || j==0){
    //             dp[i][j] = 0;
    //         }
    //     }
    // }

    // Choice Diagram
    for(int i=1; i<n+1; i++){
        for(int j=1; j<w+1; j++){
            if(weight[i-1] <= j){
                dp[i][j] = max(profit[i-1] + dp[i][j-weight[i-1]], 
                                dp[i-1][j]);  
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][w];

}

int main()
{
    int n,w; cin>>n>>w;
    vector<int> profits, weights;
    seev(profits, n);
    seev(weights, n);
    
    cout<< unboundedKnapsack(n, w, profits, weights)<< endl;

    return 0;
}