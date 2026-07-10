#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include <cstdlib>
using namespace std;
int Quickfind(vector<int> &x,int left,int right,int k){
    while(true){
        int l=left,r=right;
        int pv=x[l+rand()%(r-l+1)];
        for(int i=l;i<=r;){
            if(x[i]<pv){
                swap(x[i++],x[l++]);
            }else if(x[i]>pv){
                swap(x[i],x[r--]);
            }else{
                i++;
            }

        }
        if(l<=k&&k<=r){
            return x[k];
        }else if(k<l){
            right=l-1;
        }else{
            left=r+1;
        }
    }
}
int main(){
int a,b;
cin>>a;
cin>>b;
vector<int>m(a);
for(int i=0;i<a;i++){
    cin>>m[i];
}
 int x=Quickfind(m,0,a-1,b-1);
 cout<<x<<endl;
 return 0;
}