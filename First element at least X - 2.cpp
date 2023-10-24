/*
                                       First element at least X - 2
In this task, you need to add to the segment tree the operation of finding for the given x 
and l the minimum index j such that j≥l and a[j]≥x.

Input
The first line contains two integers n and m (1 ≤ n , m ≤ 100000), the size of the array and the number of operations.
The next line contains n numbers ai, the initial state of the array (0 ≤ ai ≤ 10^9). 
The following lines contain the description of the operations. The description of each operation is as follows:
1 iv: change the item with index i to v(0 ≤ i < n, 0 ≤ v ≤ 10^9).
2 x l: find the minimum index j such that j≥l and a[j]≥x
 (0 ≤ x≤ 10^9, 0 ≤ l <n). If there is no such element, print −1. Indices start from 0.
Output
For each operation of the second type, print the answer for the query.

Example

input

5 7
1 3 2 4 3
2 3 0
2 3 2
1 2 5
2 4 1
2 5 4
1 3 7
2 6 1

output

1
3
2
-1
3

*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5, MOD = 1e9 + 7;

class SegmentTree {

public:
    vector<int> tree;

    SegmentTree(int n) {
        tree.assign(n * 4, 0);
    }

    void build(int node, int st, int en, vector<int>& a) {
        if (st == en) {
            tree[node] = a[st];
            return;
        }
        int mid = (st + en) / 2;
        build(2 * node + 1, st, mid, a);
        build(2 * node + 2, mid + 1, en, a);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    int query(int node, int st, int en, int l, int r) {
        if (st > r || en < l)
            return -MOD;
        if (l <= st && en <= r)
            return tree[node];
        int mid = (st + en) / 2;
        int q1 = query(2 * node + 1, st, mid, l, r);
        int q2 = query(2 * node + 2, mid + 1, en, l, r);
        return max(q1, q2);
    }

    void update(int node, int st, int en, int ind, int val, vector<int>& a) {
        if (st == en) {
            a[st] = val;
            tree[node] = val;
            return;
        }
        int mid = (st + en) / 2;
        if (ind <= mid) {
            update(2 * node + 1, st, mid, ind, val, a);
        }
        else {
            update(2 * node + 2, mid + 1, en, ind, val, a);
        }
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

};

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegmentTree tree(n);
    tree.build(0, 0, n - 1, a);

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx, val;
            cin >> idx >> val;
            tree.update(0, 0, n - 1, idx, val, a);
        }
        else if (type == 2) {
            int x, l;
            cin >> x >> l;
            int lo = l, hi = n - 1;
            int ans = n;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (tree.query(0, 0, n - 1, lo, mid) < x) {
                    lo = mid + 1;
                }
                else {
                    hi = mid - 1;
                    ans = min(ans, mid);
                }
            }
            if (ans == n) {
                cout << "-1" << endl;
            }
            else {
                cout << ans << endl;
            }
        }
    }
    return 0;
}
