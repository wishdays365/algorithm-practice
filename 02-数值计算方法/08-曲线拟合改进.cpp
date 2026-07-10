#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include <cstdlib>
#include <climits>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int>v(n+1);
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        if(i==0){
            v[0]=x;
            v[1]=y;

        }else{
            v[i+1]=y;

        }
    }
    vector<int>num(n,1e9);
     vector<vector<int>>num1(n,vector<int>(n,INT_MAX));
     for(int i=0;i<n;i++){
        num1[i][i] = 0;  
    }
    int count;
    for(int len=2;len<=n;len++){
    for(int i=0;i+len-1<=n;i++){
       for(int j=i;j<i+len-1&&i+len-1<n;j++){
        int temp=num1[i][j]+num1[j+1][i+len-1]+v[i]*v[j+1]*v[i+len];
        num1[i][i+len-1]=min(temp,num1[i][i+len-1]);
       }

    }
}
    cout<<num1[0][n-1]<<endl;
    
}