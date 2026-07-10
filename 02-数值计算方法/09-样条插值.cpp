#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include <cstdlib>
#include <climits>
using namespace std;
struct hosm{
    int r,c;//上一个哨兵位置
    int count;//当前覆盖的哨兵数量
    vector<bool> row;//当前行覆盖情况
    vector<bool> col;//当前列覆盖情况
    
    hosm(int rr, int cc, int cnt, const vector<bool>& rvec, const vector<bool>& cvec)
        : r(rr), c(cc), count(cnt), row(rvec), col(cvec) {}
};
bool isallcover(const hosm& a,int m,int n){
for(int i=0;i<m;i++){
   for(int j=0;j<n;j++){
    if(!a.col[j]&&!a.row[i]) return false;
   }
}
return true;
}
int badd(const vector<bool>&a){
    int ct=0;
    for(int i=0;i<a.size();i++){
        if(a[i]) ct++;
    }
    return ct;
}
int mincover(int m,int n){
    int k=min(m,n);
    vector<hosm> a;
    vector<bool> srow(m,false);
    vector<bool> scol(n,false);
    int ct=0;
    a.emplace_back(-1,-1,0, srow, scol);
    while(!a.empty()){
         hosm cur = a[0];
         a.erase(a.begin());
         if(cur.count>k) continue;
         else if(cur.count==k){
            if(isallcover(cur,m,n)){
                ct++;
            }
            continue;
         }
         cur.r=cur.r==-1?0:cur.r;
         for(int i=cur.r;i<m;i++){
           
             if(m==k&&m-badd(cur.row)+cur.count>k) break;
            int startj=(cur.r==i)?cur.c+1:0;
            if(i==0&&startj==0) startj=1;
           if(cur.count+1>k) break;
            for(int j=startj;j<n;j++){
                 if(cur.count+1>k) break;
                vector<bool>nrow=cur.row;
                vector<bool>ncol=cur.col;
                nrow[i]=true;
                ncol[j]=true;
                if(n==k&&n-badd(ncol)+cur.count+1>k) break;
                a.emplace_back(i,j,cur.count+1,nrow,ncol);
                
         }
         }
    }
    return ct;
}

int main(){
    int m,n;
cin>>m;
cin>>n;
int count=mincover(m,n);
cout<<count<<endl;

}
