/*
Input

The first line contains two numbers n and m (1 ≤ n , m ≤ 100000), the size of the array and the number of operations.
The next line contains n numbers ai, the initial state of the array (ai ∈ {0,1} ). The following lines contain the description of the operations. 
The description of each operation is as follows:

. 1 i: change the element with index i to the opposite.
. 2 k: find the k-th one (ones are numbered from 0, it is guaranteed that there are enough ones in the array).
Output
For each operation of the second type, print the index of the corresponding one (all indices in this problem are from 0).

Example
input

5 7
1 1 0 1 0
2 0
2 1
2 2
1 2
2 3
1 0
2 0

output

0
1
3
3
1

*/

#include <bits/stdc++.h>
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

    int mid = (st + en) / 2;
    build(2 * node+1, st, mid);
    build(2 * node + 2, mid + 1, en);

    tree[node] = tree[2 * node+1] + tree[2 * node + 2];
}
//query
int kthOne(int node, int st, int en, int k){
    if(st == en){
        return st;
    }

    int mid = (st + en) / 2;
    if(k < tree[2 * node+1]){
        return kthOne(2 * node+1, st, mid, k);
    }
    else{
        return kthOne(2 * node + 2, mid + 1, en, k - tree[2 * node+1]);
    }
}

void update(int node, int st, int en, int idx){
    if(st == en){
        if(a[st] == 1){
            a[st] = 0;
            tree[node] = a[st];
        }
        else {
            a[st] = 1;
            tree[node] = a[st];
        }
        return;
    }

    int mid = (st + en) / 2;
    if(idx <= mid){
        update(2 * node+1, st, mid, idx);
    }
    else
    {
        update(2 * node + 2, mid + 1, en, idx);
    }

    tree[node] = tree[2 * node+1] + tree[2 * node + 2];
}

signed main()
{
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; i++)
        cin >> a[i];

    build(0, 0, n - 1);

    while(m--){
        int type;
        cin >> type;
        if(type == 1){
            int idx;
            cin >> idx;
            update(0, 0, n - 1, idx);
        }
        else if(type == 2){
            int k;
            cin >> k;

            int ans = kthOne(0, 0, n - 1, k);
            cout << ans << endl;
        }
    }
    return 0;
}
