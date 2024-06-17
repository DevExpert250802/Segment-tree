/*
input :  
8 3
1 2 1 4 2 3 1 1
2 1 5
1 2 10
2 1 5

output :
12
21

*/

/* Segment Tree Standard Code (Without Lazy) */


#include <bits/stdc++.h>
using namespace std;

/* Segment Tree Standard Code (Without Lazy) */
class SegTree {
public:
    int N;
    vector<int> tree;

    SegTree() {}
    SegTree(int l) {
        N = l;
        tree.resize(4 * N);
    }
    
    

    // Build Segment Tree -- build(arr, 1, 0, N-1); 
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1]; // Sum after backtracking
    }
    
    

    // Query input question is = [l, r] included -- query(1, 0, len-1, l, r)
    int query(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0; // no overlap
        if (l <= start && end <= r) return tree[node]; // Full overlap
        
        // Partial Overlap
        int mid = (start + end) / 2;
        int q1 = query(2 * node, start, mid, l, r);
        int q2 = query(2 * node + 1, mid + 1, end, l, r);
        return q1 + q2;
    }



    // Update at index(ind) of array(tree) to a value(val)
    void update(int node, int start, int end, int ind, int val) {
        if (start == ind && end == ind) {
            tree[node] = val;
            return;
        }
        if (ind > end || ind < start) return; // out of range

        int mid = (start + end) / 2;
        update(2 * node, start, mid, ind, val);
        update(2 * node + 1, mid + 1, end, ind, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }



    // Overridden functions
    void build(vector<int>& arr) {
        build(arr, 1, 0, N - 1);
    }
    int query(int l, int r) {
        return query(1, 0, N - 1, l, r);
    }
    void update(int ind, int val) {
        update(1, 0, N - 1, ind, val);
    }
    
};



int main() {
    int n, m;
    cin >>n>>m;  // read n and m

    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Create Object 
    SegTree segTree(n);
    segTree.build(arr);    // Accessing member functions

    while (m--) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int ind, val;
            cin >> ind >> val;
            segTree.update(ind, val);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            int ans = segTree.query(l, r);
            cout << ans << endl;
        }
    }

    return 0;
}
