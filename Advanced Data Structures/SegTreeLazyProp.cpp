/*
Exemplo para soma de intervalos. Necessidade de atualizar apenas o valor da diferença no range
pedido.

Adaptar para necessidades.
*/

#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Segtree{
private:
        int size;
        vector<int> tree, lazy;

        int left(int si){return 2*si+1;}
        int right(int si){return 2*si+2;}

        void build(vector<int>& arr, int L, int R, int si){

                if(L>R) return;

                if(L == R){
                        tree[si] = arr[L];
                        return;
                }

                int mid = (L+R)/2;
                build(arr, L, mid, left(si));
                build(arr, mid+1, R, right(si));
        }

        _updateRange(int si, int L, int R, int i, int j, int diff){

                if(lazy[si]!=0){

                        tree[si] = (R-L+1)*lazy[si];

                        if(L!=R){

                                lazy[left(si)] += lazy[si];
                                lazy[right(si)] += lazy[si];
                        }

                        lazy[si] = 0;
                }

                if(L>R || L>i || R<j){return;} // out of range

                if(L>=i && R<=j){
                        
                        tree[si] += (R-L+1)*diff;

                        if(L!=R){
                                lazy[left(si)] += diff;
                                lazy[right(si)] += diff;
                        }

                        return;
                }

                mid = (R+L)/2;
                _updateRange(left(si), L, mid, i, j, diff);
                _updateRange(right(si), mid+1, R, i , j, diff);

                tree[si] = tree[left(si)] + tree[right(si)];

        }

        int getSum(int si, int L, int R, int i, int j){
                if (lazy[si] != 0){ 
                      tree[si] += (R-L+1)*lazy[si]; 

                        if (L != R) 
                        { 
                                lazy[si*2+1] += lazy[si]; 
                                lazy[si*2+2] += lazy[si]; 
                        } 

                        lazy[si] = 0; 
	        }

                if (L>R || L>i || R<j) return 0; 

                if (L>=i && R<=j) return tree[si]; 

                int mid = (ss + se)/2; 
	        return getSumUtil(L, mid, i, j, left(si)) + 
		        getSumUtil(mid+1, R, i, j, right(si)); 
        }

public:
        Segtree(vector<int> arr){
                size=arr.size();
                tree.assign(3*n+1, 0);
                lazy.assign(3*n+1, 0);
                build(arr, 0, size-1, 0); // 0-indexed
        }

        void updateRange(int i, int j, int diff){
                _updateRange(0, 0, size-1, i, j, diff);
        }

        int getSum(int n, int i, int j){ 
	        if (i < 0 || j > n-1 || i > j) { 
		        printf("Invalid Input"); 
		        return -1; 
	        } 

	        return getSum(0, 0, n-1, i, j); 
        }
};
