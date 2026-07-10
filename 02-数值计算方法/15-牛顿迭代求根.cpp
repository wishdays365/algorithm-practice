#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double x0(double x){
    return exp(x)+10*x-2;
}
double x1(double x){
    return exp(x)+10;
}
int main()
{
    double num1=0,num2=0,num3;
    do{
        num2=num1;
        num1=num1-x0(num1)/x1(num1);

    }while(fabs(num1-num2)>0.5e-5);
    cout<<fixed<<setprecision(8)<<num1;
    return 0;



}
