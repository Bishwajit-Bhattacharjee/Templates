#include <bits/stdc++.h>
using namespace std;
 
#define L(x) (x)<<1
#define R(x) (x)<<1|1
 
using ll = long long int;
 
ll const IDENTITY = 0; //  change

struct Node{    // change
    int type; // 1 -> inc, 2 -> set
    ll val;

    Node(){
        type = 1, val = 0;
    }
    Node(int t, ll v):type(t), val(v){}
};
 
int const N = 2e5 + 10;
ll t[4*N]; 
ll a[N];

Node lazy[4*N];

 
ll merge(ll l, ll r){ // change
    return l + r;
}

/**
 * Given the lazy in the node, and a new operation,
 * update the lazy value.
 **/
void assignOp(int p, Node op) {  // change

    if (op.type == 1){
        lazy[p].val += op.val;
    }
    else if (op.type == 2){
        lazy[p] = op;
    }
}
/**
 *  Given the lazy in for a node, calculate its value,
 *  and push the lazy down to the childs
 **/

void push(int p, int l, int r){  // change

    if (!(lazy[p].type == 1 && lazy[p].val == 0)){
        // assert(lazy[p].size() <= 1);

        auto last = lazy[p];

        if (l != r){

            for (auto ch : {L(p), R(p)}){
                assignOp(ch, last);
            }
        }

        ll add = 1LL * (r - l + 1) * last.val;

        if (last.type == 2) t[p] = add;
        else t[p] += add;


    }
    lazy[p] = Node();
}
 
void build(int p, int l, int r){
    if (l == r) {
        t[p] = a[l]; return;
    }
    int mid = (l+r)/2;
    build(L(p), l, mid);
    build(R(p), mid+1, r);
 
    t[p] = merge(t[L(p)], t[R(p)]);
}
 
 
void update(int p, int l, int r, int ul, int ur, Node op){
    
    push(p, l, r); // The order matters

    if (l > ur || r < ul) return;
 
    if (ul <= l && r <= ur) {
        
        assignOp(p, op);
        push(p, l, r);
        return;
    }
 
    int mid = (l+r)/2;
    update(L(p), l, mid, ul, ur, op);
    update(R(p), mid+1, r, ul, ur, op);
 
    t[p] = merge(t[L(p)], t[R(p)]);
}
 
ll Q(int p, int l, int r, int ql, int qr){
    push(p, l, r); // The order matters

    if (l > qr || r < ql) return IDENTITY;
    
    if (ql <= l && r <= qr) return t[p];
 
    int mid = (l+r)/2;
 
    return merge(
        Q(L(p), l, mid, ql, qr),
        Q(R(p), mid+1, r, ql, qr)
    );
}
 
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
 
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
 
    while (q--){
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1){
            int x;
            cin >> x;
            update(1, 1, n, l, r, Node(t, x));
        }
        else if (t == 2){
            int x;
            cin >> x;
            update(1, 1, n, l, r, Node(t, x));
        }
        else {
            cout << Q(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}