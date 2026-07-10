#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double y0(double x,double y,double m){
    return x*pow(m,3)+y;
}

double y1(double x,double y,double m){
double k=y0(x,y,m);
return x*pow(k,3)+y;
}
double x1(double x,double y,double m){
double k1=y0(x,y,m);
double k2=y0(x,y,k1);
return m-pow(k1-m,2)/(k2-2*k1+m);
}
int main()
{
    double num1=0,num2=0,num3;
    cin>>num1;
    cin>>num2;
    cin>>num3;
    double temp=num3;
    int i=0;
    do{
        
      temp=num3;
      num3=x1(num1,num2,num3);

    }while(fabs(num3-temp)>1e-5);
    cout<<fixed<<setprecision(6)<<y0(num1,num2,temp)<<", "<<y1(num1,num2,temp)<<", "<<num3<<endl;
    return 0;
}