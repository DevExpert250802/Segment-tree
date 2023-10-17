#include <bits/stdc++.h>
using namespace std;

const int N =1e5+2;
int a[N] , tree [4*N];

void build (int node , int s ,int e)
    {
        if(s==e){
            tree[node] = a[s];
            return;
        }
        int mid = (s+e)/2;
        build(2*node+1,s,mid);
        build(2*node+2,mid+1,e);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }

int main ()
{
    int n;
    cin>>n;
    for(int i =0;i<n;i++)
    {
        cin>>a[i];
    }
    build(0,0,n-1);
    for (int i = 0; i < 4 * n; i++) 
    {
      cout << tree[i] << endl;
    }
    return 0;
}
