#pragma once

#include <bits/stdc++.h>

using i64 = long long;

#define RIGHT

#ifdef RIGHT
struct Chairman_Tree {
    static constexpr int ALPHABET_SIZE = 26, N = 1000010;
    struct Node { int l, r, val; }tr[N * 30];
    int root[N * 2];
    int idx = 0;
    void init() {
        memset(root, 0, sizeof root);
        idx = 0;
    }
    int build(int l, int r) {
        int q = ++ idx;
        tr[q].val = 0;
        if (l == r) return q;
        int mid = l + r >> 1;
        tr[q].l = build(l, mid), tr[q].r = build(mid + 1, r);
        return q;
    }
    int update(int p, int l, int r, int x, int v) {
        assert(idx < N * 50);
        int q = ++ idx;
        tr[q].val = tr[p].val + v;
        if (l == r) return q;
        int mid = l + r >> 1;
        if (x <= mid) {
            tr[q].l = update(tr[p].l, l, mid, x, v);
            tr[q].r = tr[p].r;
        } else {
            tr[q].l = tr[p].l;
            tr[q].r = update(tr[p].r, mid + 1, r, x, v);
        }
        return q;
    }
    int query(int p, int q, int l, int r, int L, int R) {
        if (l > R || r < L) return 0;
        if (L <= l && R >= r) return tr[q].val - tr[p].val;
        int mid = l + r >> 1;
        return query(tr[p].l, tr[q].l, l, mid, L, R) + query(tr[p].r, tr[q].r, mid + 1, r, L, R);
    }
}tree;
#endif
struct SuffixAutomaton {
    static constexpr int ALPHABET_SIZE = 26, N = 1000010;
    int ans[N]; // ans表示长度为len的串的最大数量
    // basic
    int n;
    std::string s;
    struct Node {
        int s[ALPHABET_SIZE];
        int fa, len;
    }tr[2 * N];
    int last, idx;
    // extension
    int cntA[N * 2], A[N * 2];
    int num[N * 2]; // 记录right集合的大小
#ifdef RIGHT
    std::vector<int> g[N * 2];
    int L[N * 2], R[N * 2], dfn;
    int pos[N * 2]; // 记录dfs序映射的点
    int end_pos[N * 2];
#endif
    SuffixAutomaton(){ clear(); }
    void clear() {
        last = idx = 1;
        tr[1].fa = tr[1].len = 0;
        std::fill(tr[1].s, tr[1].s + 26, 0);
    }
    void init(std::string &str) {
        n = str.size();
        s = str;
        for (auto c : s) extend(c - 'a');
    }
    void extend(int c) {
        int p = last;
        int np = last = ++ idx;
        tr[np].len = tr[p].len + 1;
        memset(tr[np].s, 0, sizeof tr[np].s);
        while (p && !tr[p].s[c]) tr[p].s[c] = np, p = tr[p].fa;
        if (!p) {
            tr[np].fa = 1;
        } else {
            int q = tr[p].s[c];
            if (tr[q].len == tr[p].len + 1) {
                tr[np].fa = q;
            } else {
                int nq = ++ idx;
                tr[nq] = tr[q];
                tr[nq].len = tr[p].len + 1;
                tr[q].fa = tr[np].fa = nq;
                while (tr[p].s[c] == q) tr[p].s[c] = nq, p = tr[p].fa;
            }
        }
    }
    void build() {
        memset(cntA, 0, sizeof cntA);
        memset(num, 0, sizeof num);
        for (int i = 1; i <= idx; i ++ ) cntA[tr[i].len] ++ ;
        for (int i = 1; i <= idx; i ++ ) cntA[i] += cntA[i - 1];
        for (int i = idx; i >= 1; i -- ) A[cntA[tr[i].len] -- ] = i;
        // 更行主串节点
        int temp = 1;
        for (int i = 0; i < n; i ++ ){
            num[temp = tr[temp].s[s[i] - 'a']] = 1;
        }
        /*拓扑更新*/
        for (int i = idx; i >= 1; i -- ){
            //basic
            int x = A[i];
            num[tr[x].fa] += num[x];
            //special
            ans[tr[x].len] = std::max(ans[tr[x].len], num[x]);
        }
        //special
        for (int i = tr[last].len; i > 1; i -- ){
            ans[i - 1] = std::max(ans[i - 1], ans[i]);
        }
    }
#ifdef RIGHT
    int get_right_between(int u, int l, int r) {
        return tree.query(tree.root[L[u] - 1], tree.root[R[u]], 1, n, l, r);
    }
    void dfs(int u, int father) {
        L[u] = ++ dfn;
        pos[dfn] = u;
        for (auto v : g[u]) {
            dfs(v, u);
            num[u] += num[v];
        }
        R[u] = dfn;
    }
    void build_sc_tree() {
        int temp = 1;
        for (int i = 0; i < n; i ++ ) {
            temp = tr[temp].s[s[i] - 'a'];
            end_pos[temp] = i + 1;
            num[temp] = 1;
        }
        for (int i = 2; i <= idx; i ++ ) {
            g[tr[i].fa].push_back(i);
        }
    }
    void build_chairman_tree() {
        tree.root[0] = tree.build(1, n);
        for (int i = 1; i <= idx; i ++ ) {
            int u = pos[i];
            if (end_pos[u]) {
                int x = end_pos[u];
                tree.root[i] = tree.update(tree.root[i - 1], 1, n, x, 1);
            } else {
                tree.root[i] = tree.root[i - 1];
            }
        }
    }
    void extract_right() {
        build_sc_tree();
        dfn = 0;
        dfs(1, 0);
        build_chairman_tree();
    }
#endif
}sam;