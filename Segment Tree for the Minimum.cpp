/*
Input
The first line contains two integers n and m (1≤n,m≤100000), the size of the array and the number of operations. The next line
contains n numbers ai, the initial state of the array (0 ≤ ai ≤ 10^9). The following lines contain the description of the operations.
The description of each operation is as follows:

. 1 i v: set the element with index ito v(0 ≤i< n, 0 ≤v ≤ 10^9).
. 2 l r: calculate the minimum of elements with indices from lto r−1 (0≤l<r≤n).
Output
For each operation of the second type print the corresponding minimum.

Example
input
5 5
5 4 2 3 5
2 0 3
1 2 6
2 0 3
1 3 1
2 0 5
output
2
4
1

*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;
int a[N], tree[4 * N];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node + 1, start, mid);
    build(2 * node + 2, mid + 1, end);
    tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
}

int query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) {
        return INT_MAX;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int q1 = query(2 * node + 1, start, mid, l, r);
    int q2 = query(2 * node + 2, mid + 1, end, l, r);
    return min(q1, q2);
}

void update(int node, int start, int end, int ind, int val) {
    if (start == end) {
        a[start] = val;
        tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;

    if (ind <= mid) {
        update(2 * node + 1, start, mid, ind, val);
    } else {
        update(2 * node + 2, mid + 1, end, ind, val);
    }

    tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(0, 0, n - 1);

    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {
            int ind, val;
            cin >> ind >> val;
            update(0, 0, n - 1, ind, val);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            int ans = query(0, 0, n - 1, l, r -1);
            cout << ans << endl;
        }
    }
    return 0;
}



