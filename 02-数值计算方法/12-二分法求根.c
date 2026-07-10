#include<stdio.h>
#include<string.h>
#include<math.h>
double kta(){

    double x=0,y=0;
    do{
        x=y;
        y=(2-exp(x))/10;
    }while(fabs(y-x)>=0.5e-3);
    return y;

}
int main(){
double x=kta();

printf("%.5f, %.9f",x,exp(x)+10*x-2);

}
