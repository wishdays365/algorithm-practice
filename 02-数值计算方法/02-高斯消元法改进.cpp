#include<iostream>
#include<vector>
#include <algorithm>
#include <cmath>
#include<iomanip>
using namespace std;

void mgy(vector<long long>&a,long long m,long long mid ,long long n){
    vector<long long> temp;
    long long i=m,j=mid+1;
    while(i<=mid&&j<=n){
        if(a[i]<=a[j]){
        temp.push_back(a[i++]);  
        }else{
        temp.push_back(a[j++]); 
        }
    }
    while(i<=mid){
        temp.push_back(a[i++]);  
    }
    while(j<=n){
        temp.push_back(a[j++]); 
    }
    for(int o=0;m+o<=n;o++){
    a[m+o]=temp[o];
    }
}
void mgsx(vector<long long>&a,long long m,long long n){
    long long mid=(m+n)/2;
    long long temp1;
    if(m>=n){return;}
    
    else if(m+1==n){
        if(a[m]>a[n]){
            temp1=a[m];
            a[m]=a[n];
            a[n]=temp1;
        }
    }else{
       mgsx(a,m,mid);
       mgsx(a,mid+1,n);
       vector<long long> temp;
       long long i=0 ,j=0;
    while(i<mid-m+1&&j<n-mid){
        if(a[m+i]<=a[mid+1+j]){
        temp.push_back(a[m+i]);  
        i++;
        }else{
        temp.push_back(a[mid+1+j]);
        j++; 
        }
    }
    while(i<mid-m+1){
        temp.push_back(a[m+i]);  
        i++;
    }
    while(j<n-mid){
        temp.push_back(a[mid+1+j]); 
        j++;
    }
    for(long long o=0;o<=n-m;o++){
        a[m+o]=temp[o];
    }
    }
    return;
}
int main(){

long long num;
cin>>num;
vector<long long>a(num),b(num-1);
for(long long i=0;i<num;i++){
cin >> a[i];
}
mgsx(a,0,num-1);
for(long long i=0;i<num-1;i++){
b[i]=a[i+1]-a[i];
}
mgsx(b,0,num-2);
cout<<b[0];
}