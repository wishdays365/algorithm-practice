#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
int comp(vector<int>&a,vector<int>&temp,int left,int mid, int right){
    int num1=left;
    int num2=mid-1;
    int k=num1;
    int count=0;
while(num1<mid-1&&num2<=right){
    if(a[num1]<=a[num2]){
        temp[k++]=a[num1++];
    }
    else{
        temp[k++]=a[num2++];
        count+=mid-1-num1;
    }
}

    while(num2<=right){
        temp[k++]=a[num2++];
}


    while(num1<=mid-2){
       temp[k++]=a[num1++];
    }
int i=left;
while(i<=right){
    a[i]=temp[i];
    i++;
}
return count;
}

int mu(vector<int>&a,vector<int>&temp,int left,int right){ 
    if(left==right) return 0;
    int count=0;
    int mid=left+(right-left)/2;

    count+=mu(a,temp,left,mid);
    count+=mu(a,temp,mid+1,right);
    count+=comp(a,temp,left,mid+2,right);
    return count;

}
vector<string> split(string&a){
string line=a;
    string x;
   istringstream ss(line);
   vector<string>m;
while(getline(ss,x)){
    if(!x.empty()){
    m.push_back(x);
    }
}
return m;
}
int main(){
    string line;
    int x;
    vector<int> m;
    getline(cin,line);
    stringstream ss(line);
    while(ss>>x){
     m.push_back(x);
    }
    vector<int> n(m.size());
    cout<<mu(m,n,0,m.size()-1);
    
} 