#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
class SegTree {
private:
        vi segtree, A;
        int size;

        int left(int p){return p<<1;}
        int right(int p){return (p<<1)+1;}

        /*Build fuction*/
        void buildSumInterval(){
                for(int i=0; i<size; i++){
                        segtree[size+i] = A[i];
                }

                for(int i=size-1; i>0; i--){
                        segtree[i] = segtree[i<<1] + segtree[i<<1 | 1];
                }
        }

        int querySumInterval(int p, int L, int R, int i, int j){
                if(i>R || j<L){return -1;}
                if(L >= i && R<= j){return segtree[p];}
                int p1 = querySumInterval(left(p), L, (L+R)/2, i, j);
                int p2 = querySumInterval(right(p), (L+R)/2 +1, R, i, j);

                if(p1 == -1) return p2;
                if(p2 == -1) return p1;

                return (A[p1] <= A[p2] ? p1 : p2);
        }

public:
        SegTree(vi _A){
                A = _A; size = _A.size();
                segtree.assign(2*size, 0);
                buildSumInterval();
        }

        //update a tree node
        void updateSumInterval(int p, int value){

                //set the value already
                segtree[p+size] = value;
                p += size;

                //move upwards and update parents
                for(int i =p; i>1; i>>=1){
                        segtree[i>>1] = segtree[i^1] + segtree[i];
                }
        }

        int querySumInterval(int l, int r){return querySumInterval(1,0, size-1, l, r);}
};
