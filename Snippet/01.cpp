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
};

int main() {
    int n;
    cin >> n;

    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Create Object 
    SegTree segTree(n);
    segTree.build(arr, 1, 0, n - 1);    // Accessing member functions

    // Build - View Build Data
    for (int i = 1; i <  2*n; i++) {  // Printing only the relevant part of the segment tree
        cout << segTree.tree[i] << " ";
    }
    cout << endl;

    return 0;
}

