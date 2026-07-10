 #include<iostream>
 #include<string>
#include<cmath>
#include<iomanip>
 using namespace std;
 double kca(double n){
int num=1;
double add=0;
double term=n;
 if(fabs(n)<1e-3){
     return n;
 }
 else{
do{
add+=term;
term=term*n*n/((num+1)*(num+2))*(-1);
num+=2;
}while(fabs(term)>=1e-3);

return add+term;
}
 }
int main(){
    double x;
    cin>>x;
    double pi=2*acos(-1.0);
    while(x>=pi){
       x-=pi;
    }
    while(x<=-pi){
       x+=pi;
    }
    double count;
    
    count =kca(x);
    cout<<fixed<<setprecision(8)<<count<<endl;

    
}
