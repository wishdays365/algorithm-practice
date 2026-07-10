#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
using namespace std;
double comp(vector<double>&a,vector<double>&b,int k,int n,int m){
    int num1,num2;
    int count=a.size()+b.size();
    
    while(1){
        if(n==a.size()){
    
    return b[m+k-1];

}
if(m==b.size()){
    
    return a[n+k-1];
    
}
if(k==1){
    
        return a[n]<b[m]?a[n]:b[m];
    
}

if(k%2==0){//ab验证数
    num1=k/2;
    num2=k/2;
}
else{
    num1=(k+1)/2;
    num2=k-num1;
}
//ab验证数特殊
if(num1>a.size()-n||num2>b.size()-m){
if(a.size()-n<b.size()-m){ 
    num1=a.size()-n;
    num2=k-num1;

}
else{
    num2=b.size()-m;
    num1=k-num2;
}
}

//
if(a[n+num1-1]<b[m+num2-1]){
    k=k-num1;
    n=n+num1;
}else{
    k=k-num2;
    m=m+num2;
}

}
}
void splitLineToVector(const string& line, vector<double>& vec) {
    stringstream ss(line);
    double num;
    while (ss >> num) { 
        vec.push_back(num);
    }
}

int main(){
    vector<double> a;
    vector<double> b;
string line1,line2;
getline(cin,line1);
splitLineToVector(line1,a);

getline(cin,line2);
splitLineToVector(line2,b);
    
int x=a.size(),y=b.size();
if((x+y)%2==0){
    cout<<fixed<<setprecision(1)<<(comp(a,b,(x+y)/2,0,0)+comp(a,b,(x+y)/2+1,0,0))/2<<endl;
}
else{
    cout<<fixed<<setprecision(1)<<comp(a,b,(x+y+1)/2,0,0)<<endl;
}

}

