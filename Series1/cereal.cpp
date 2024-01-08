#include <iostream>
#include <vector>

using namespace std;

bool pos(vector<int> v,int n, int k,int mid){
    vector<int> pre;
    for(int i = 0; i<n; ++i){
        if(v[i]>=mid) pre.push_back(1);
        else pre.push_back(-1);
        if(i>0) pre[i]+=pre[i-1];
    }

    int mx = pre[k-1];
    int mn = 0;

    for(int i = k; i<n; ++i){
        mn = min(mn,pre[i-k]);
        mx = max(mx,pre[i]-mn);   
    }
    if (mx>0) return true;
    return false;
}

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> v;
    for(int i = 0; i<n; ++i){
        int input;
        cin >> input;
        v.push_back(input);
    }
    int l = 1, r = n+1;
    int mm = -1; //max median
    while (l<=r)
    {
        int mid = (l+r)/2;
        if (pos(v,n,k,mid)){
            mm = mid;
            l = mid+1;
        }
        else r = r-1;
    }
    cout << mm << "\n";
}