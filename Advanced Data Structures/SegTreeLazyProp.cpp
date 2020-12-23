/*tested
1-based segtree
sum range queries and sum range udpdates (considering a diff update)
search interval 0 to n-1
*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

typedef enum qType {MIN, MAX, SUM} QTYPE;
typedef enum lazy {YES, NO} LAZY;

class SegTree {
        vi st, A, lazy;
        int n;
        QTYPE type;
        LAZY isLazy;
        int left (int p) { return p << 1;}
        int right (int p) { return (p << 1) + 1;}
        int mid (int l, int r) { return (l+r)/2;}
        int parent (int p) {return p >> 1;}

        void buildMinQuery(int p, int L, int R){
                if(L==R) st[p] = A[L];
                else{
                        buildMinQuery(left(p), L, mid(L, R));
                        buildMinQuery(right(p), mid(L, R) + 1, R);
                        int p1 = st[left(p)], p2 = st[right(p)];
                        st[p] = (p1 <= p2) ? p1:p2;
                }
        }

        void buildMaxQuery(int p, int L, int R){
                if(L==R) st[p] = A[L];
                else{
                        buildMaxQuery(left(p), L, mid(L,R));
                        buildMaxQuery(right(p), mid(L,R) + 1, R);
                        int p1 = st[left(p)], p2 = st[right(p)];
                        st[p] = (p1 >= p2) ? p1:p2;
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
                return p1 <= p2 ? p1:p2;
        }

        int maxQuery(int p, int L, int R, int i, int j){
                if(i>R || j<L) return -1;
                if(L >= i && R <= j) return st[p];
                int p1 = maxQuery(left(p), L, mid(L,R) , i , j);
                int p2 = maxQuery(right(p), mid(L,R) +1, R, i, j);
                if(p1 == -1) return p2;
                if(p2 == -1) return p1;
                return (p1 >= p2) ? p1:p2;
        }

        int sumQuery(int p, int L, int R, int i, int j){
                if (lazy[p] != 0) {
                        st[p] += lazy[p];
                        if (L != R) {
                                lazy[left(p)] += lazy[p];
                                lazy[right(p)] += lazy[p];
                        }
                        lazy[p] = 0;
                }
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
                        int p1 = st[left(parent_p)], p2 = st[right(parent_p)];
                        if (type == MIN) {
                                st[parent_p] = (p1 <= p2) ? p1:p2;
                        } else if (type == MAX) {
                                st[parent_p] = (p1 >= p2) ? p1:p2;
                        } else {
                                st[parent_p] = p1 + p2;
                        }
                        updateTree(parent_p);
                }
        }

        void updateValue(int p, int L, int R, int i, int value) {
                if (L == R) {
                        st[p] = value;
                        A[L] = value;
                        updateTree(p);
                }
                else if (i <= mid(L,R)) updateValue(left(p), L, mid(L,R), i, value);
                else updateValue(right(p), mid(L,R)+1, R, i, value);
        }

        void updateRange(int p, int L, int R, int i, int j, int diff) {
                if (lazy[p] != 0) {
                        st[p] += lazy[p];
                        if (L != R) {
                                lazy[left(p)] += diff;
                                lazy[right(p)] += diff;
                        }
                        lazy[p] = 0;
                }

                // out of range
                if (L > R || L > j || R < i) return;

                // current interval IN search interval (not strict)
                if (L >= i && R <= j) {
                        st[p] += diff;
                        if (L != R) {
                                lazy[left(p)] += diff;
                                lazy[right(p)] += diff;
                        }
                        return ;
                }

                updateRange(left(p), L, mid(L,R), i, j, diff);
                updateRange(right(p), mid(L,R)+1, R, i, j, diff);

                st[p] = st[left(p)] + st[right(p)];
        }

public:
        SegTree(const vi& _A, QTYPE type, LAZY isLazy){
                A = _A; n = (int) A.size();
                st.assign(4*n, 0);
                this->type = type;
                this->isLazy = isLazy;
                if (isLazy == YES) lazy.assign(4*n, 0);

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

        void updateValue(int i, int value) {
                updateValue(1, 0, n-1, i, value);
        }

        void updateRange(int i, int j, int diff) {updateRange(1, 0, n-1, i, j, diff);}

        void print_st() {
                for (int i = 0; i < (int)st.size(); i++) {
                        printf("%d ", st[i]);
                }
                printf("\n");
        }
};