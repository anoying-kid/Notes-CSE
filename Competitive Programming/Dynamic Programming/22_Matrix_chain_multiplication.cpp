#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

// int matrixMultiplication(vector<int> &arr, int N)
// {    
//     vector<vector<int>> dp(N, vector<int>(N, 0));
//     for (int i=N-1; i>=1; i--) {
//         for (int j=i+1; j<N; j++) {
//             dp[i][j] = INT_MAX;
//             for (int k=i; k<j; k++)
//                 dp[i][j] = min(dp[i][j], arr[i-1]*arr[k]*arr[j] + dp[i][k] + dp[k+1][j]);
//         }
//     }
//     return dp[1][N-1];
// }

int dp[101][101];

int MCM(int arr[], int i, int j){
        if (i>=j){
            return 0;
        }
        if (dp[i][j]!=-1){
            return dp[i][j];
        }
        int mn = INT_MAX;
        for(int k=i; k<=j-1; k++){
            int temp = MCM(arr, i, k) + MCM(arr, k+1, j) +
                        arr[i-1]*arr[k]*arr[j];
            mn = min(mn, temp);
        }
        return dp[i][j] = mn;
    }

int main()
{
    int n; cin>>n;
    int arr[n]; seea(arr, 0, n);
    memset(dp, -1, sizeof(dp));
    cout<<MCM(arr, 1, n-1)<<endl;
    return 0;
}