#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

// Not optimised
// int solve(string str, int i, int j){
//         if (i>=j || isPalindrome(str, i, j)){
//             dp[i][j] = 0;
//             return 0;
//         }
//         if (dp[i][j]!=-1){
//             return dp[i][j];
//         }
        
//         int mn = INT_MAX;
//         for(int k=i; k<=j-1; k++){
//             int temp = solve(str, i, k)+solve(str, k+1, j) + 1;
//             mn = min(temp, mn);
//         }
//         return dp[i][j] = mn;
//     }

// A little optimized by checking subproblem in loop in dp
// int solve(string s, int i, int j){
//         if (i>=j || isPalindrome(s, i, j)){
//             dp[i][j] = 0;
//             return 0;
//         }
//         if (dp[i][j]!=-1){
//             return dp[i][j];
//         }
        
//         int mn = INT_MAX;
//         for(int k=i; k<=j-1; k++){
//             int left, right;
//             if (dp[i][k]!=-1){
//                 left = dp[i][k];
//             } else {
//                 left = solve(s, i, k);
//                 dp[i][k] = left;
//             }
//             if (dp[k+1][j]!=-1){
//                 right = dp[k+1][j];
//             } else {
//                 right = solve(s, k+1, j);
//                 dp[k+1][j] = right;
//             }
//             int temp = left + right + 1;
//             mn = min(temp, mn);
//         }
//         return dp[i][j] = mn;
//     }
int dp[101][101];

bool isPalindrome(string str, int i, int j) {
        while (i <= j) {
            if (str[i] != str[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }

int solve(string s, int i, int j){
    if (i>=j || isPalindrome(s, i, j)){
        dp[i][j] = 0;
        return 0;
    }
    if (dp[i][j]!=-1){
        return dp[i][j];
    }
    
    int mn = INT_MAX;
    for(int k=j-1; k>=i; k--){
        if (isPalindrome(s, i, k)){
            int right = solve(s, k+1, j);
            int temp = right + 1;
            mn = min(temp, mn);
        }
    }
    return dp[i][j] = mn;
}

int palindromicPartition(string str)
{
    // code here
    int n = str.length();
    memset(dp, -1, sizeof(dp));
    return solve(str, 0, n-1);
}

int main()
{
    string s; cin>>s;
    cout<<palindromicPartition(s)<<endl;
    return 0;
}