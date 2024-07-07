#include<iostream>
#include<vector>

using namespace std;

class FWT{
  vector<int> tree;
  int n;

  public:
   FWT(int size){
    this->n=size;
    tree.resize(n,0);
   }

   void update(int val,int id){
       while(id<=n){
          tree[id]+=val;
          id+=(id&(-id));
       }
   }

   int query(int id){
    int sum=0;

    while(id>0){
        sum+=tree[id];

        id-=(id&(-id));
    }
    return sum;
   }

};

  void solve(){

    int n;
    cin>>n;
    n++;
    vector<int> arr(n);
    FWT T(n);
    for(int i=1;i<n;i++){
        cin>>arr[i];
       T.update(arr[i],i);
    } 

    int q;
    cin>>q;
    while(q--){
        int a,b;
        cin>>a>>b;
        a--;

        cout<<T.query(b)-T.query(a)<<endl;

    }
  }

int main(){
  solve();
}