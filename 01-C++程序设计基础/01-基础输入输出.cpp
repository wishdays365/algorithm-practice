#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main(){
    string s;
    string t;
    cin>>s>>t;
    vector<int> next(t.size(),0);
    int i=0,j=1;
    next[0]=0;
    while(i<t.size()-1){
        if(t[i]==t[j]){
            next.push_back(i+1);
            i++;
            j++;
        }
        else if(i>0){
            next.push_back(0);
            i=0;
        }
        else{
            next.push_back(0);
            i=0;
            j++;
        }
    
}
int n=0,m=0;
while(m<t.size()-1){
        if(t[n]==t[m]){
            n++;
            m++;
        }
        else if(m>0){
            m=next[m-1];
        }
        else{
            n++;
        }
}
cout<<n-m+2<<endl;
}
