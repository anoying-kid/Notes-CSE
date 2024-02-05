#include<bits/stdc++.h>
#define ll long long
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define mod 1000000007
using namespace std;

unordered_map<string, bool> mp;

bool solve(string x, string y){
    string key = x + " " + y;
    if(mp.find(key)!=mp.end()){
        return mp[key];
    }
    if(x.compare(y)==0){
        mp[key] = true;
        return mp[key] = true;
    };
    if (x.length()<=1){
        return  mp[key] = false;
    }
    bool flag = false;
    int n = x.length();
    for(int i=1; i<=n-1; i++){
        if(( solve(x.substr(0,i), y.substr(n-i, i)) && solve(x.substr(i,n-i), y.substr(0,n-i)) )
            || (solve(x.substr(0,i), y.substr(0,i)) && solve(x.substr(i), y.substr(i)))){
                flag = true;
                break;
            }
    }
    return mp[key] = flag;
}
    
bool isScramble(string X, string Y){
	if (X.length() != Y.length())
		cout << "No\n";
	else
		solve(X, Y) ? cout << "Yes\n" : cout << "No\n";
	return 0;
}

int main()
{
    string a, b; cin>>a>>b;
    isScramble(a, b);
    return 0;
}