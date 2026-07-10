#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
using namespace std;
double a2(int a,double b,double c){
  int m=a%2;
  if(m==1){
    return -b*sin(c);
  }
  else if(m==0){
    return b*cos(c);
  }
}
double a11(double b,double c){
    double temp=2*b*c;


return temp;
}
double a12(double b,double c){
    double temp=2*b;


return temp;
}
double kac(double a,double b,double c){
   double temp=c;
   int o=0;
   while(fabs((a11(a,temp)-a2(o,b,temp)))>=1e-5){
    temp=temp-(a11(a,temp)-a2(o,b,temp))/(a12(a,temp)-a2(o+1,b,temp));
   
   }
   return temp;
}
int main(){
    double a,b,c;
    cin>>a;
    cin>>b;
    cin>>c;
double s=kac(a,b,c);
double z=a*s*s-b*sin(s);
cout<<fixed<<setprecision(5)<<s<<' '<<z<<endl;
}
