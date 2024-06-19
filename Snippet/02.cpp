/*
input:
8 3
1 1 1 1 1 1 1 1
2 1 5
1 1 5 10
2 1 5

Output : 
5    
50
*/

/* Segment Tree Lazy Propogation Code (Not Generic Code) */


#include <bits/stdc++.h>
using namespace std;

class SegTree {
public:
    int N;
    vector<int> tree, unpropUpd; // the actual val of un-propagated updates to be processed
    vector<bool> isLazy; // tells if a certain node is storing un-propagated updates or not

    // Constructor to initialize the segment tree
    SegTree(int len) {
        N = len;
        tree.resize(4 * len);
        isLazy.resize(4 * len);
        unpropUpd.resize(4 * len);
    }



    // Asking node to remember that it has 'val' update for its range
    void apply(int node, int start, int end, int val) { // [start, end] is node range
        if (start != end) { // leaf nodes can't be lazy, as they have no one to propagate to
            isLazy[node] = true;
            unpropUpd[node] = val; // stacking up the un-propagated value, which I'll propagate down
        }
        tree[node] = (end - start + 1) * val; // this "= shows assign update", "+= shows range add update" 
    }



    // Assigning the value whatsoever we had on 'node' to its children ('2*v' & '2*v+1')
    void pushDown(int node, int start, int end) {
        if (!isLazy[node]) return; // if not lazy then no push-down required
        isLazy[node] = false; // no more lazy
        int mid = (start + end) / 2;
        apply(2 * node, start, mid, unpropUpd[node]); // propagates to left child
        apply(2 * node + 1, mid + 1, end, unpropUpd[node]); // propagates to right child
        unpropUpd[node] = 0; // identity-transformation -- updated the children (job done)
    }



    // Building the segment tree
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
        
        //partial overlap
        pushDown(node, start, end); // propagate any pending updates before querying
        int mid = (start + end) / 2;
        int q1 = query(2 * node, start, mid, l, r);
        int q2 = query(2 * node + 1, mid + 1, end, l, r);
        return q1 + q2;
    }



    // Update at index(ind) of array(tree) to a value(val)
    void updateRange(int node, int start, int end, int l, int r, int val) {
      // reachead the leaf node 
        if (l <= start && end <= r) { // full overlap
            apply(node, start, end, val);
            return;
        }
        if (start > r || end < l) return; // no overlap
         
         //partial overlap
        pushDown(node, start, end); // propagate any pending updates before updating
        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, l, r, val);
        updateRange(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }



    // Overridden functions for convenience
    void build(vector<int>& arr) {
        build(arr, 1, 0, N - 1);
    }

    int query(int l, int r) {
        return query(1, 0, N - 1, l, r);
    }

    void updateRange(int l, int r, int val) {
        updateRange(1, 0, N - 1, l, r, val);
    }
};



int main() {
    int n, m;
    cin >> n >> m;  // read n and m

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Create Object 
    SegTree segTree(n);
    segTree.build(arr); // Accessing member functions

    while (m--) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int l, r, val;
            cin >> l >> r >> val;
            segTree.updateRange(l, r, val);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            int ans = segTree.query(l, r);
            cout << ans << endl;
        }
    }

    return 0;
}
