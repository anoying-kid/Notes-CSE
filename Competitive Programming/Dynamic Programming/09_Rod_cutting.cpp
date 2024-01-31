#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
using namespace std;

int cutRod(vector<int> &price, int n)
{
	// Write your code here.
	 int t[n+1][n+1];
        
        for(int i=0; i<n+1; i++){
            for(int j=0; j<n+1; j++){
                if (i==0 || j==0) t[i][j]=0;
            }
        }
        
        for(int i=1; i<n+1; i++){
            for(int j=1; j<n+1; j++){
                if(i<=j){
                    t[i][j] = max(price[i-1]+t[i][j-i], t[i-1][j]);
                } else{
                    t[i][j] = t[i-1][j];
                }
            }
        }
        
        return t[n][n];
}

int main()
{
    int n; cin>>n;
    vector<int> price; seev(price, n);

    cout<< cutRod(price, n);
    return 0;
}