#include <iostream>
#include<cmath>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;
vector<long long> cit(vector<long long>&a,long long n0,long long n1){
    if(n1<=n0) return a;
    long long x=n0;
    long long temp;
    long long i0=0,i1=0,c=0;
    
while(n0+i0<=n1-i1){
if(c==0){
if(a[x]>a[n1-i1]&&x<n1-i1){
temp=a[x];
a[x]=a[n1-i1];
a[n1-i1]=temp;
x=n1-i1;
c=1;
}
i1++;
}else if(c==1){
if(a[x]<a[i0+n0]&&x>i0+n0){
temp=a[x];
a[x]=a[n0+i0];
a[i0+n0]=temp;
x=i0+n0;
c=0;
}
i0++;
}
}
cit(a,n0,x-1);
cit(a,x+1,n1);
return a;
}
int main(){
long long num,m;
cin>>num;
vector<long long> a(num),b(num-1);
for(long long i=0;i<num;i++){
    cin>>a[i];
    
}
cit(a,0,num-1);
for(long long i=1;i<num;i++){
    b[i-1]=a[i]-a[i-1];
}
cit(b,0,num-2);
cout<<b[0];
}