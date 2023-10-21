/*
Input
The first line contains two integers n and m (1 ≤ n , m ≤ 100000), the size of the array and the number of operations.
The next line contains nnumbers ai, the initial state of the array (0 ≤ ai ≤ 10^9). The following lines contain the description of the operations.
The description of each operation is as follows:

. 1 i v: change the item with index i to v (0 ≤ i < n, 0 ≤ v ≤ 10^9).
. 2 x : find the minimum index j such that a[j] ≥ x. If there is no such element, print −1. Indices start from 0.
Output
For each operation of the second type, print the answer for the query.

Example

input 

5 7
1 3 2 4 6
2 2
2 5
1 2 5
2 4
2 8
1 3 7
2 6

output

1
4
2
-1
3

*/

#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N = 1e5+2, MOD = 1e9+7;


int tree[4*N], a[N];


void build(int node, int st, int en)
{
    if(st == en){
        tree[node] = a[st];
        return;
    }


    int mid = (st + en)/2;
    build(2*node+1, st, mid);
    build(2*node+2, mid+1, en);


    tree[node] = max(tree[2*node+1], tree[2*node+2]);
}


int query(int node, int st, int en, int l, int r){
    if(st>r || en<l)
        return -MOD;


    if(l<=st && en<=r)
        return tree[node];


    int mid = (st + en)/2;
    int q1 = query(2*node+1, st, mid, l, r);
    int q2 = query(2*node+2, mid+1, en, l, r);


    return max(q1, q2);
}


void update(int node, int st, int en, int ind, int val){
    if(st == en){
        a[st] = val;
        tree[node] = val;
        return;
    }


    int mid = (st+en)/2;
    if(ind <= mid){
        update(2*node+1, st, mid, ind, val);
    }
    else
    {
        update(2*node+2, mid+1, en, ind, val);
    }


    tree[node] = max(tree[2*node+1], tree[2*node+2]);
}


signed main()
{
    int n,m; cin >> n >> m;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    build(0,0,n-1);
    while(m--){
        int type;
        cin >> type;
        if(type == 1){
            int idx,val;
            cin >> idx >>val;
            update(0,0,n-1,idx,val);
        }
        else if(type == 2){
            int x;
            cin >> x;
            int lo = 0, hi = n-1;
            int ans = n;
            while(lo<=hi){
                int mid = (lo+hi)/2;
                if(query(0,0,n-1,lo,mid) < x){
                    lo = mid+1;
                }
                else {
                    hi = mid-1;
                    ans = min(ans, mid);
                }
            }


            if(ans == n){
                cout << "-1" << endl;
            }
            else{
                cout << ans << endl;
            }
        }
    }
    return 0;
}
