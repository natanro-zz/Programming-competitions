/*COIN PROBLEM --> minimum num of coins to sum a target M
tested*/

#include <bits/stdc++.h>
using namespace std;
int func(int m, vector<int>& coins, vector<int>& values){
        values[0] = 0;
        for(int i=1; i<=m; i++){
                for(auto c : coins){
                        if(i-c >= 0){
                                values[i] = min(values[i], values[i-c]+1);
                        }
                }
        }
        return values[m];
}

int main(){
        int t;
        cin >> t;
        for(int i=0; i<t; i++){
                int n, m;
                cin >> n >> m;
                vector<int> coins;
                vector<int> values(m+1, 2*m);
                for(int j=0; j<n; j++){
                        int a;
                        cin >> a;
                        coins.push_back(a);
                }
                cout << func(m, coins, values) << endl;
        }
        return 0;
}

