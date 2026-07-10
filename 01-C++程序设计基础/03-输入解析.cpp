#include<iostream>
#include<string>
#include<vector>
#include <limits>
using namespace std;
int main(){
    string s;
    string t;
    int x1=0,x2=0;
    // while(x1!=2){
    //     cin>>x;
    //     if(x=='"'){
    //         x1++;
    //     }
    //     if(x1==1&&x!='"'){
    //     s.push_back(x);
    //     }
    //     if(x=='\n'||x==','){
    //         break;
    //     }
    // }
    // while(x2!=2){
    //     cin>>x;
    //     if(x=='"'){
    //         x2++;
    //     }
    //     if(x2==1&&x!='"'){
    //     t.push_back(x);
    //     }
    // }
    cin>>s;
    cin>>t;
    vector<int> next;
    int i=0,j=1;
    next.push_back(0);
    while(j<t.size()){
        if(t[i]==t[j]){
            next.push_back(i+1);
            i++;
            j++;
        }else if(i>0){
            next.push_back(0);
            i=0;
        }else{
            next.push_back(0);
            j++;
        }
    
}
int n=0,m=0;
while(m<t.size()){
        if(s[n]==t[m]){

            n++;
            m++;
            
        }
        else if(m>0){
            m=next[m-1];
        }
        else{
            n++;
        }
        if(n>s.size()){

            n=m-1;
            break;
            
        }
}
cout<<n-m<<endl;
}
