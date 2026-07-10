#include<stdio.h>
#include<string.h>
#include<math.h>
double kta(){

    double x0=0,x2=1;
    do{
        if(((exp((x0+x2)/2))+10*(x0+x2)/2-2)>0){
          x2=(x0+x2)/2;
        }
        else{x0=(x0+x2)/2;}
    }while(fabs(x0-x2)>=0.5e-3);
    
    return (x0+x2)/2;

}
int main(){
double x=kta();

printf("%.5f, %.9f",x,exp(x)+10*x-2);

}
