#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double x0(double x){
    return pow(x,4)+2*pow(x,3)-x-1;
}

double x1(double x){
    return pow(x,3)+2*pow(x,2)-1;
}

double cep(double x,double y,int m){
    double num1=x,num2=y,temp;
    for(int i=0;i<m-1;i++){
        temp=num1;
        num1=num1*x-num2*y;
        num2=temp*y+num2*x;
    }
    return num1;
}

double cep1(double x,double y,int m){
    double num1=x,num2=y,temp;
    for(int i=0;i<m-1;i++){
        temp=num1;
        num1=num1*x-num2*y;
        num2=temp*y+num2*x;
    }
    return num2;
}

double a(double x,double y){
    return cep(x,y,4)+2*cep(x,y,3)-x-1;
}

double a1(double x,double y){
    return cep1(x,y,4)+2*cep1(x,y,3)-y;
}

double b(double x,double y){
    return 4*cep(x,y,3)+6*cep(x,y,2)-1;
}

double b1(double x,double y){
    return 4*cep1(x,y,3)+6*cep1(x,y,2);
}

double chu(double a1,double a2,double b1,double b2){
    double num1,num2;
    num1=(a1*b1+a2*b2)/(b1*b1+b2*b2);
    num2=(-a1*b2+a2*b1)/(b1*b1+b2*b2);
    return num1;
}

double chu1(double a1,double a2,double b1,double b2){
    double num1,num2;
    num1=(a1*b1+a2*b2)/(b1*b1+b2*b2);
    num2=(-a1*b2+a2*b1)/(b1*b1+b2*b2);
    return num2;
}

int main()
{
    double num1=0,num2=0;
    cin>>num1;
    cin>>num2;
    double temp1=num1,temp2=num2;
    int i=0;
    do{
        if(i++==10000){
            cout<<"error"<<endl;
            break;
        }
        temp1=num1;
        temp2=num2;
        if(b(temp1,temp2)*b(temp1,temp2)+b1(temp1,temp2)*b1(temp1,temp2)==0){
            cout<<"error"<<endl;
            break;
        }
        num1=num1-chu(a(temp1,temp2),a1(temp1,temp2),b(temp1,temp2),b1(temp1,temp2));
        num2=num2-chu1(a(temp1,temp2),a1(temp1,temp2),b(temp1,temp2),b1(temp1,temp2));

    }while(fabs(num1-temp1)>1e-5||fabs(num2-temp2)>1e-5);
    if(i!=10001&&b(temp1,temp2)*b(temp1,temp2)+b1(temp1,temp2)*b1(temp1,temp2)!=0){
        cout<<fixed<<setprecision(8)<<num1<<' '<<num2<<'i';
    }
    return 0;
}