#include <iostream>
#include <string>
using namespace std;

bool naive(string search, string target){
    for(int i =0; i<search.length(); i++){
        int j;
        if(search[i]== target[0]){
            for(j=1;j<target.length();j++){
                if(search[i+j]!=target[j]){
                    break;
                }
            }
            if(j == target.length())
                return true;
        }
    }
    return false;
}

bool BM(string search, string target){
    int table[256];
    int n = search.length();
    int m = target.length();
    int i, j;
    for(i = 0;i<255;i++){ //ascii
        table[i] = m;   //
    }
    for(i = 0; i<m;i++){
        table[target[i]] = m - 1 - i;
    }
    i = m-1;
    while(i<n){
        int jump = table[search[i]];
        if(jump == 0){
            for(j = 1; j<m; j++){
                if(search[i-j] != target[m-j-1]){
                    i=i+m;
                    break;
                }
            }
            if(j==m)
                return true;
        }
        i = i+jump;
    }
    return false;
}

int main(){
    string s = "this is my string, hello";
    string sub;
    cin>>sub;
    cout<<BM(s,sub)<<'\n';
}