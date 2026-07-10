#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<algorithm>
using namespace std;
int main(){
    vector<int>v, w;
    int y;
    while(cin.peek()!='\n'&&cin>>y){
        v.push_back(y);
    }
    cin.ignore();
    while(cin.peek()!='\n'&&cin>>y){
        w.push_back(y);
    }
    cin.ignore();
     int count;
    cin>>count;
   int n = v.size();
vector<pair<int, int>> coins;
for (int i = 0; i < n; i++) {
    coins.emplace_back(v[i], w[i]);
}
sort(coins.begin(), coins.end()); 
vector<int>ws(count+1,1e9);
ws[0]=0;
vector<vector<int>>coinct(count+1,vector<int>(n,0));
for(int i=1;i<=count;i++){
    int temp=-1;
    for(int j=0;j<n;j++){
        if(coins[j].first<=i&&ws[i-coins[j].first]!=1e9){
            if(ws[i]>ws[i-coins[j].first]+coins[j].second){
            ws[i]=ws[i-coins[j].first]+coins[j].second;
            temp=j;
            } 
        }
        }
        if(temp!=-1){
            coinct[i]=coinct[i-coins[temp].first];
             coinct[i][temp]++;
        }
    }
cout<<ws[count]<<endl;
for(int i=0;i<n;i++){
    cout<<coinct[count][i]<<' ';
}

    return 0;
}
