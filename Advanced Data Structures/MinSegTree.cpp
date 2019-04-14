/*tested
0-based segtree
minimum range queries*/

/*falta implementar atualização de elementos*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class SegTree {
        vi st, A;
        int n;
        int left (int p) { return p << 1;}
        int right (int p) { return (p << 1) + 1;}

        void buildMinQuery(int p, int L, int R){
                if(L==R) st[p] = L;
                else{
                        buildMinQuery(left(p), L, (L+R)/2);
                        buildMinQuery(right(p), (L+R)/2 + 1, R);
                        int p1 = st[left(p)], p2 = st[right(p)];
                        st[p] = (A[p1] <= A[p2]) ? p1:p2;
                }
        }

        int minQuery(int p, int L, int R, int i, int j){
                if(i>R || j<L) return -1;
                if(L >= i && R <= j) return st[p];
                int p1 = minQuery(left(p), L, (L+R)/2 , i , j);
                int p2 = minQuery(right(p), (L+R)/2 +1, R, i, j);
                if(p1 == -1) return p2;
                if(p2 == -1) return p1;
                return A[p1] <= A[p2] ? p1:p2;
        }

public:
        SegTree(const vi& _A){
                A = _A; n = (int) A.size();
                st.assign(4*n, 0);
                buildMinQuery(1,0,n-1);
        }

        int minQuery(int i, int j) {return minQuery(1,0,n-1,i,j);}
};
