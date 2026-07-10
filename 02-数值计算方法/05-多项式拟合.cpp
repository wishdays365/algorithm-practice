#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;
int fun(int m,int n){
    if(m==1||n==1){
        return 1;
    }
    else if(m<n){
        return fun(m,m);
    }
    else if(m==n){
        return 1+fun(m,n-1);
    }
    else{
        return fun(m,n-1)+fun(m-n,n);
    }
}
int main() {
    cout<<fun(100,50)<<endl;
    return 0;
}