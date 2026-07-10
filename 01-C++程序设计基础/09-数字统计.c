#include<stdio.h>
int main(){
long long count[10]={0};
    long long a,b;
    scanf("%lld",&a);
    scanf("%lld",&b);
    //count[x]
    long long higha=0,highb=0;
    long long lowa=0,lowb=0;
    long long cura=0,curb=0;
    long long c=1;
    higha=a/10,highb=b/10;
    lowa=0,lowb=0;
    cura=a%10,curb=b%10;
    long long i=0;
   long long x,xb;
    while(!(c>b)){
    while(i<10){
        if(i==0){
        lowa=a%c;
        lowb=b%c;
       }else {
        lowb=c-1;
        lowa=a%c;
       }
       x=curb-i;
       xb=highb;
    if(curb-i<0){
            xb=highb-1;
            x=curb-i+10;
        }
        if(cura==0&&x==0&&higha==0&&c>1){
             lowa=c;
        }
        if(xb<0||b-i*c+c<a||(xb==0&&x==0&&c>1)){
            break;
        }
        if(x>cura){
            count[x]+=(xb-higha-1)*c+lowb+1+c;

        }
        else if(x==cura){
            count[x]+=(xb-higha-1)*c+c-lowa+lowb+1;

        }else if(x<cura){
            count[x]+=(xb-higha-1)*c+lowb+1;

        }

       i++;
    }
    c*=10;
    i=0;
    higha=a/c/10,highb=b/c/10;
    lowa=a%c,lowb=b%c;
    cura=a/c%10,curb=b/c%10;
}

    for(int i=0;i<10;i++) {
        printf("%lld ",count[i]);
    }
}