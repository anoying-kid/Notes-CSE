#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int minDifference(int arr[], int n)  { 

    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }

    int target = total / 2;

    int dp[n+1][target+1];
    
    for(int i=0; i<n+1; i++){
        for(int j=0; j<target+1; j++){
            if (i==0 || j==0) dp[i][j] = 0;
        }
    }

    for (int i = 1; i < n+1; i++) {
        for (int j = 0; j < target+1; j++) {
            if (arr[i - 1] <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - arr[i - 1]] + arr[i - 1]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int sum1 = dp[n][target];
    int sum2 = total - sum1;

    return abs(sum2 - sum1);
} 

int main()
{
    int n; cin>>n;
    int arr[n]; seea(arr, 0, n);
    
    cout<<minDifference(arr, n)<<endl;

    return 0;
}