/*
Para update em elementos folha de um range
*/

#include<bits/stdc++.h>
using namespace std;

class FenwickTree{
        private: vector<int> ft;
                int LSOne(int b){
                        return (b&(-b));
                }
        public:
                FenwickTree(int n){
                        ft.assign(n+1, 0);
                }
                int query(int b){
                        int sum=0;
                        for(; b; b-=LSOne(b)) sum += ft[b];
                }
                int query(int a, int b){
                        return query(b) - (a==1 ? 0: query(a-1));
                }
                void adjust(int k, int v){
                        for(; k<(int)ft.size(); k+= LSOne(k)) ft[k]+=v;
                }
};
