#include<iostream>
#include<vector>
using namespace std;


class ST{
   
   vector<int> seg,lezy;

   public:
   ST(int n){
    seg.resize(4 * n);
    lezy.resize( 4 * n ,0);
   }

   void build( vector<int> arr,int node,int st,int en){
       
       if(st==en){
        seg[node]=arr[st];
        return;
       }

       int mid=(st+en)/2;
       build(arr,node*2,st,mid);
       build(arr,node*2+1,mid+1,en);

       seg[node]= seg[node*2] + seg[node*2+1];
   }

   void update(int node,int st,int en,int l,int r, int val){
      

      if( lezy[node]!=0 ){
          
          seg[node]= (en -st +1)*lezy[node];
         // lezy[node]=0;
          if(st!=en){
        lezy[node*2]+= lezy[node];
        lezy[node*2+1]+= lezy[node];
          }

          lezy[node]=0;
      }

      //no overlap
      if( st>r or l>en ) return;
    
    //complete overlap
      if( st<=l and en>=r){
        seg[node]+=(en-st+1)*val;

        if(st!=en){
            lezy[node*2]+=val;
            lezy[node*2+1]+=val;

        }

        return;
      }
   int mid=(st+en)/2;

   update(node*2,st,mid,l,r,val);
   update(node*2+1,mid+1,en,l,r,val);

   seg[node]=seg[node*2]+seg[node*2+1];
   }


   int query( int node,int st,int en,int l,int r){

     //update
     
      if( lezy[node]!=0 ){
          
          seg[node]+= (en -st +1)*lezy[node];
         // lezy[node]=0;
          if(st!=en){
        lezy[node*2]+= lezy[node];
        lezy[node*2+1]+= lezy[node];
          }

          lezy[node]=0;
      }


//no overlap
     if(r<st or l>en) return 0;
//full overlap
     else if(st>=l and en<=r) return seg[node];
     //partial overlap.......
     else{
        int left=query(node*2,st,(st+en)/2,l,r);
        int right=query(node*2+1,(st+en)/2 +1 , en ,l,r);

        return left+right;
     }
   }

};



void solve(){
   
   int n;
   cin>>n;

   vector<int> arr(n);

   for(int i=0;i<n;i++) cin>>arr[i];
   
   ST se(n);

   se.build(arr,1,0,n-1);

   cout<<"query update";
   int a;
   cin>>a;
  while(a--){

    char ch;
    cin>>ch;

    if(ch=='q'){
        int l,r;
        cin>>l>>r;
      cout<<se.query(1,0,n-1,l,r)<<endl;
    }
    else if(ch=='u'){
        int l,r;
        cin>>l>>r;
       int val;
       cin>>val;
        se.update(1,0,n-1,l,r,val);
    }
  }

}



int main(){

solve();

}