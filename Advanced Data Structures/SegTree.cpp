/*tested
1-based segtree
minimum, maximum or sum range queries
search interval 0 to n-1
*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

typedef enum qType {MIN, MAX, SUM} QTYPE;

class SegTree {
        vi st, A;
        int n;
        QTYPE type;
        int left (int p) { return p << 1;}
        int right (int p) { return (p << 1) + 1;}
        int mid (int l, int r) { return (l+r)/2;}
        int parent (int p) {return p >> 1;}

        void buildMinQuery(int p, int L, int R){
                if(L==R) st[p] = L;
                else{
                        buildMinQuery(left(p), L, mid(L, R));
                        buildMinQuery(right(p), mid(L, R) + 1, R);
                        int p1 = st[left(p)], p2 = st[right(p)];
                        st[p] = (A[p1] <= A[p2]) ? p1:p2;
                }
        }

        void buildMaxQuery(int p, int L, int R){
                if(L==R) st[p] = L;
                else{
                        buildMaxQuery(left(p), L, mid(L,R));
                        buildMaxQuery(right(p), mid(L,R) + 1, R);
                        int p1 = st[left(p)], p2 = st[right(p)];
                        st[p] = (A[p1] >= A[p2]) ? p1:p2;
                }
        }

        void buildSumQuery(int p, int L, int R){
                if(L==R) st[p] = A[L];
                else{
                        buildSumQuery(left(p), L, mid(L,R));
                        buildSumQuery(right(p), mid(L,R) + 1, R);
                        int p1 = st[left(p)], p2 = st[right(p)];
                        st[p] = p1 + p2;
                }
        }

        int minQuery(int p, int L, int R, int i, int j){
                if(i>R || j<L) return -1;
                if(L >= i && R <= j) return st[p];
                int p1 = minQuery(left(p), L, mid(L,R) , i , j);
                int p2 = minQuery(right(p), mid(L,R) +1, R, i, j);
                if(p1 == -1) return p2;
                if(p2 == -1) return p1;
                return A[p1] <= A[p2] ? p1:p2;
        }

        int maxQuery(int p, int L, int R, int i, int j){
                if(i>R || j<L) return -1;
                if(L >= i && R <= j) return st[p];
                int p1 = maxQuery(left(p), L, mid(L,R) , i , j);
                int p2 = maxQuery(right(p), mid(L,R) +1, R, i, j);
                if(p1 == -1) return p2;
                if(p2 == -1) return p1;
                return A[p1] >= A[p2] ? p1:p2;
        }

        int sumQuery(int p, int L, int R, int i, int j){
                if(i>R || j<L) return -1;
                if(L >= i && R <= j) return st[p];
                int p1 = sumQuery(left(p), L, mid(L,R) , i , j);
                int p2 = sumQuery(right(p), mid(L,R) +1, R, i, j);
                if(p1 == -1) return p2;
                if(p2 == -1) return p1;
                return p1 + p2;
        }

        void updateTree(int p) {
                int parent_p = parent(p);
                if (parent_p >= 1) {
                        if (type == MIN) {
                                int p1 = st[left(parent_p)], p2 = st[right(parent_p)];
                                st[parent_p] = (A[p1] <= A[p2]) ? p1:p2;
                        } else if (type == MAX) {
                                int p1 = st[left(parent_p)], p2 = st[right(parent_p)];
                                st[parent_p] = (A[p1] >= A[p2]) ? p1:p2;
                        } else {
                                int p1 = st[left(parent_p)], p2 = st[right(parent_p)];
                                st[parent_p] = p1 + p2;
                        }
                        updateTree(parent_p);
                }
        }

        void updateValue(int p, int L, int R, int i, int value) {
                if (L == R) {
                        if (type == SUM) st[p] = value;
                        A[L] = value;
                        updateTree(p);
                }
                else if (i <= mid(L,R)) updateValue(left(p), L, mid(L,R), i, value);
                else updateValue(right(p), mid(L,R)+1, R, i, value);
        }

public:
        SegTree(const vi& _A, QTYPE type){
                A = _A; n = (int) A.size();
                st.assign(4*n, 0);
                this->type = type;
                if (type == MIN) buildMinQuery(1, 0, n-1);
                else if (type == MAX) buildMaxQuery(1, 0, n-1);
                else if (type == SUM) buildSumQuery(1, 0, n-1);
        }

        int query(int i, int j) {
                if (type == MIN) return minQuery(1,0,n-1,i,j);
                else if (type == MAX) return maxQuery(1,0,n-1,i,j);
                else if (type == SUM) return sumQuery(1,0,n-1,i,j);
                return -1;
        }

        void update(int i, int value) {updateValue(1, 0, n-1, i, value);}

        void print_st() {
                for (int i = 0; i < (int)st.size(); i++) {
                        printf("%d ", st[i]);
                }
                printf("\n");
        }
};