#include <bits/stdc++.h>
using namespace std;

#define L(x) (x)<<1
#define R(x) (x)<<1|1

using ll = long long int;

ll const IDENTITY = 0;

int const N = 2e5 + 10;
ll t[4*N];
ll a[N];

ll merge(ll l, ll r){
    return l + r;
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

void update(int p, int l, int r, int ul, int ur, ll val){
    if (l > ur || r < ul) return;
    if (ul <= l && r <= ur) {
        t[p] += val;
        return;
    }
    int mid = (l+r)/2;
    update(L(p), l, mid, ul, ur, val);
    update(R(p), mid+1, r, ul, ur, val);

    t[p] = merge(t[L(p)], t[R(p)]);
}

ll Q(int p, int l, int r, int ql, int qr){
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
        int l, r;
        cin >> l >> r;
        cout << Q(1, 1, n, l, r) << '\n';
    }
    return 0;
}