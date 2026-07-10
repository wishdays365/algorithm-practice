#include <iostream>
#include<cmath>
#include<iomanip>
#include<vector>
#include <algorithm>
using namespace std;
int gcd(int a,int b){
    int temp;
    while(b!=0){
    temp=b;
    b=a%b;
    a=temp;
    }
    return a;
}
int gcds(vector<int>a){
    int i=a.size();
    int count=a[0];
    for(int x=0;x<i;x++){
       count=gcd(count,a[i]);
     if(count==1){
        break;
     }
    }
    return count;
}
int main()
{
    vector<int>a;
    int x;
    cin>>x;
    int m;
    int c1=0;
    for(int i=0;i<x;i++){
        cin>>m;
        a.push_back(m);
        if(m==1){
            c1++;
        }
    }
    if(c1!=0){
        cout<<a.size()-1;
        return 0;
    }
    int n=a.size();
    int mini=a.size()+1;
     vector<int> o;
     vector<int>q;
     int num1,num2,count=n+1,temp;
     o.push_back(a[0]);
     q.push_back(1);

for(int i=1;i<n;i++){
  o.insert(o.begin(),a[i]);
  q.insert(q.begin(), 1);
  
  for(int j=1;j<q.size();j++){
  o[j]=gcd(o[j],a[i]);
  q[j]+=1;
  if(o[j]==1){
    count=min(count,q[j]);
  }
  }
  for(int j=0;j<q.size()-1;j++){
  if(o[j]==o[j+1]){
    o.erase(o.begin()+j+1);
    q.erase(q.begin()+j+1);
    j--;
  }
  }
}
if(count==n+1){
cout<<-1;
}
else cout<<count+a.size()-2;
    
}
