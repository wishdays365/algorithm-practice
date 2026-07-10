#include<iostream>
#include<vector>
#include <algorithm>
#include <cmath>
#include<iomanip>
using namespace std;
struct xy{
    long long x,y;
   
};
bool camp(const xy&a,const xy&b){
    return a.x<b.x;
}
bool campy(const xy&a,const xy&b){
    return a.y<b.y;
}
void mgy(vector<xy>&a,long long m,long long mid ,long long n){
    vector<xy> temp;
    long long i=m,j=mid+1;
    while(i<=mid&&j<=n){
        if(a[i].y<=a[j].y){
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
void mgsx(vector<xy>&a,long long m,long long n){
    long long mid=(m+n)/2;
    xy temp1;
    if(m>=n){return;}
    
    else if(m+1==n){
        if(a[m].x>a[n].x){
            temp1=a[m];
            a[m]=a[n];
            a[n]=temp1;
        }
    }else{
       mgsx(a,m,mid);
       mgsx(a,mid+1,n);
       vector<xy> temp;
       long long i=0 ,j=0;
    while(i<mid-m+1&&j<n-mid){
        if(a[m+i].x<=a[mid+1+j].x){
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
long long order(vector<xy>&m,vector<xy>&n,long long a,long long b){
    long long count=1000000000000000000LL,x;
  
    if(b==a){
        count=1000000000000000000LL;
    }
    else if(b-a==1){
    count=(m[a].x- m[a+1].x)*(m[a].x-m[a+1].x)+(m[a].y-m[a+1].y)*(m[a].y-m[a+1].y);
        xy temp1;
        
     if(n[a].y>n[b].y){
            temp1=n[a];
            n[a]=n[b];
            n[b]=temp1;
        }
    }
     else if(b-a==2){
    x=(m[a].x- m[a+1].x)*(m[a].x-m[a+1].x)+(m[a].y-m[a+1].y)*(m[a].y-m[a+1].y);
    count=min(count,x);
    x=(m[a+2].x-m[a+1].x)*(m[a+2].x-m[a+1].x)+(m[a+2].y-m[a+1].y)*(m[a+2].y-m[a+1].y);
    count=min(count,x);
    x=(m[a+2].x-m[a].x)*(m[a+2].x-m[a].x)+(m[a+2].y-m[a].y)*(m[a+2].y-m[a].y);
    count=min(count,x);
   order(m,n,a,(a+b)/2);
   order(m,n,(a+b)/2+1,b);
    mgy(n,a,(a+b)/2,b);
    }
    else{  
        vector<xy> temp;
       long long count1=order(m,n,a,(a+b)/2);
       long long count2=order(m,n,(a+b)/2+1,b);
       mgy(n,a,(a+b)/2,b);
       count=min(count1,count2);

    for(long long i=a;i<=b;i++){
        if((n[i].x-m[(a+b)/2].x)*(n[i].x-m[(a+b)/2].x)<=count){
        temp.push_back(n[i]); 
        }
    }
    
//================================================================//
long long temp2;
for(long long i=0;i<temp.size();i++){  
   for(long long j=i+1;j<temp.size();j++){  
    temp2=(temp[i].y-temp[j].y)*(temp[i].y-temp[j].y);
         if(temp2>=count){
            break;
         }
    
    count=min(count,temp2+(temp[i].x-temp[j].x)*(temp[i].x-temp[j].x));
}
    }
}
return count;
}

int main(){

long long num;
cin>>num;
vector<xy>a(num);
for(long long i=0;i<num;i++){
cin >> a[i].x >> a[i].y;
}
mgsx(a,0,num-1);
vector<xy>b=a;

long long count=order(a,b,0,a.size()-1);
double an=sqrt(count);
cout<<fixed<<setprecision(2)<<an;
}