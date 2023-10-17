#include <bits/stdc++.h>
using namespace std;

const int N =1e5+2;
int a[N] , tree [4*N];

void build (int node , int start ,int end)
    {
        if(start==end){
            tree[node] = a[start];
            return;
        }
        int mid = (start+end)/2;
        build(2*node+1,start,mid);
        build(2*node+2,mid+1,end);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
int query(int node,int start ,int end , int l ,int r){
// l....r  start ....end  or  start ....end  l....r   (no overlap)
    if(start>r || end<l)
    {
        return 0;
    }
 //    l...start...end....right  (complete overlap)
    if(l<=start && end<= r){
        return tree[node];
    }
//    start..l....end....right   or  l...start....right...end (partial overlap)
    int mid  = (start+end)/2;

    int q1 = query(2*node+1,start,mid,l,r);
    int q2 = query(2*node+2,mid+1,end,l,r);
    return q1+q2;
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
    while(1){                               //infinite while loop
         int type;
         cin>>type;
         if(type== -1)
         {
            break;
         }

         if(type==1)
         {
              int l,r;
              cin>>l>>r;

              int ans=query(0,0,n-1,l,r);
              cout<<ans<<endl;
         }
    }                             
    return 0;
}





//input   :                                                                                      // output : 24
 
8
5 3 2 4 1 8 6 10
1 1 6
-1
