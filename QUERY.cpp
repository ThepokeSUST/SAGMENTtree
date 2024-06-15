#include<iostream>
#include<vector>

using namespace std;

void build(vector<int> &arr,vector<int> &seg,int node,int st,int en){

  if(st==en){
    seg[node]=arr[st];
    return;
  }

  int mid=(st+en)/2;
  build(arr,seg,node*2,st,mid);
  build(arr,seg,node*2+1,mid+1,en);

  seg[node]=seg[node*2]+seg[node*2+1];
}


int query(vector<int> &seg,int node,int a,int b,int st,int en){
  
  if(b<st or a>en){
    return 0;
  }
  else if(a<=st and en<=b){
    return seg[node];
  }
  else{
    
    int mid=(st+en)/2;
    int left=query(seg,node*2,a,b,st,mid);
    int right=query(seg,node*2+1,a,b,mid+1,en);

    return left+right;
  }
}


 

int main(){
  int n;
  cin>>n;

  vector<int> arr(n);

  for(int i=0;i<n;i++) cin>>arr[i];

  vector<int> seg(4*n);

  build(arr,seg,1,0,n-1);

  cout<<"Query ";
  int a,b;

  cin>>a>>b;
  cout<<query(seg,1,a,b,0,n-1);

}