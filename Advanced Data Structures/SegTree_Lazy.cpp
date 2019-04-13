/*not tested*/

#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
class SegTree_Lazy {
private:
        vi segtree, A, lazy;
        int n;

        int left(int p){return p<<1;}
        int right(int p){return (p<<1)+1;}

        void build(){
                for(int i=0; i<n; i++){
                        segtree[size+i] = A[i];
                }

                for(int i=size-1; i>0; i--){
                        segtree[i] = segtree[i<<1] + segtree[i<<1 | 1];
                }
        }

        void updateRange(int node, int start, int end, int l, int r, int val){
            if(lazy[node] != 0)
            {
                // This node needs to be updated
                segtree[node] += (end - start + 1) * lazy[node];    // Update it
                if(start != end)
                {
                    lazy[node*2] += lazy[node];                  // Mark child as lazy
                    lazy[node*2+1] += lazy[node];                // Mark child as lazy
                }
                lazy[node] = 0;                                  // Reset it
            }
            if(start > end or start > r or end < l)              // Current segment is not within range [l, r]
                return;
            if(start >= l and end <= r)
            {
                // Segment is fully within range
                segtree[node] += (end - start + 1) * val;
                if(start != end)
                {
                    // Not leaf node
                    lazy[node*2] += val;
                    lazy[node*2+1] += val;
                }
                return;
            }
            int mid = (start + end) / 2;
            updateRange(node*2, start, mid, l, r, val);        // Updating left child
            updateRange(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
            segtree[node] = segtree[node*2] + segtree[node*2+1];        // Updating root with max value
        }

        int queryRange(int node, int start, int end, int l, int r){
            if(start > end or start > r or end < l)
                return 0;         // Out of range
            if(lazy[node] != 0)
            {
                // This node needs to be updated
                segtree[node] += (end - start + 1) * lazy[node];            // Update it
                if(start != end)
                {
                    lazy[node*2] += lazy[node];         // Mark child as lazy
                    lazy[node*2+1] += lazy[node];    // Mark child as lazy
                }
                lazy[node] = 0;                 // Reset it
            }
            if(start >= l and end <= r)             // Current segment is totally within range [l, r]
                return segtree[node];
            int mid = (start + end) / 2;
            int p1 = queryRange(node*2, start, mid, l, r);         // Query left child
            int p2 = queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
            return (p1 + p2);
        }

public:
        SegTree_Lazy(vi _A){
                A= _A; n=A.size();
                segtree.assign(2*n, 0);
                lazy.assign(2*n,0);
        }

        void updateRange(int i, int j, int val){updateRange(1,0, n-1, i, j, val);}

        int queryRange(int i, int j){return queryRange(1, 0, n-1, i,j);}
};
