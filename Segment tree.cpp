#include <bits/stdc++.h>
using namespace std;

const int N =1e5+2;
int a[N] , tree [4*N];

void build (int node , int start ,int end)
    {
       if(s==e){
            tree[node] = a[start];
            return;
        }
        int mid = (start+end)/2;
        build(2*node+1,start,mid);
        build(2*node+2,mid+1,end);
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
