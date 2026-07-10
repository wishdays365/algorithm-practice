#include<iostream>
#include<string>
#include<vector>
using namespace std;
double comp(vector<int>&a,vector<int>&b){
    int num1=a.size();
    int num2=b.size();
    int i=0,j=0;
    vector<int> c;
while(i<num1&&j<num2){
if(a[i]<b[j]){
    c.push_back(a[i]);
    i++;
}
else if(a[i]==b[j]){
    c.push_back(b[j]);
    c.push_back(a[i]);
    j++;
    i++;
}
else{
    c.push_back(b[j]);
    j++;
}

}
while(j<num2){
   c.push_back(b[j]);
   j++;
}
while(i<num1){
   c.push_back(a[i]);
   i++;
}
int num3=c.size();
if (num3%2==0){
    double e=(static_cast<double>(c[num3/2])+static_cast<double>(c[num3/2-1])/2;
return e;
}
else{
     double e=c[(num3+1)/2-1];
return e;
}
}