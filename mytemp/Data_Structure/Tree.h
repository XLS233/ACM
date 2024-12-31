#pragma once

#include <bits/stdc++.h>

// LCA、dfs序
struct Tree {
    std::vector<int> dep, fa, sz;
    std::vector<int> L, R, top, son;
    int dfn;
    Tree(std::vector<std::vector<int>> &tree, int root = 0) : dep(tree.size()), fa(tree.size()), sz(tree.size()), 
    L(tree.size()), R(tree.size()), top(tree.size()), son(tree.size(), -1), dfn(-1) {
        auto dfs1 = [&](auto dfs1, int u, int father, int depth) -> int {
            dep[u] = depth, fa[u] = father, sz[u] = 1;
            for (auto v : tree[u]) {
                if (v == father) { continue; }
                sz[u] += dfs1(dfs1, v, u, depth + 1);
                if (son[u] == -1 || sz[v] > sz[son[u]]) { son[u] = v; }
            }
            return sz[u];
        };
        dfs1(dfs1, root, -1, 1);
        auto dfs2 = [&](auto dfs2, int u, int t) -> void {
            L[u] = ++ dfn, top[u] = t;
            if (son[u] != -1) { dfs2(dfs2, son[u], t); }
            for (auto v : tree[u]) {
                if (v == fa[u] || v == son[u]) { continue; }
                dfs2(dfs2, v, v);
            }
            R[u] = dfn;
        };
        dfs2(dfs2, root, root);
    }
    int lca(int a, int b) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) { std::swap(a, b); }
            a = fa[top[a]];
        }
        return dep[a] < dep[b] ? a : b;
    }
};

template<class Info, class Tag>
class TreeDecomposition : Tree, LazySegmentTree<Info, Tag> {
    std::vector<Info> get_nw(std::vector<Info> &w) {
        std::vector<Info> nw(w.size());
        for (int i = 0; i < w.size(); i ++ ) {
            nw[L[i]] = w[i];
        }
        return nw;
    }
public:
    TreeDecomposition(std::vector<std::vector<int>> &tree, std::vector<Info> &w) : 
        Tree(tree), LazySegmentTree<Info, Tag>(std::vector<Info>(get_nw(w))) { }
    void update_path(int u, int v, const Tag &k) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) { std::swap(u, v); }
            LazySegmentTree<Info, Tag>::rangeApply(L[top[u]], L[u], k);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) { std::swap(u, v); }
        LazySegmentTree<Info, Tag>::rangeApply(L[v], L[u], k);
    }
    Info query_path(int u, int v) {
        Info res = Info();
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) { std::swap(u, v); }
            res = res + LazySegmentTree<Info, Tag>::rangeQuery(L[top[u]], L[u]);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) { std::swap(u, v); }
        res = res + LazySegmentTree<Info, Tag>::rangeQuery(L[v], L[u]);
        return res;
    }
    void update_tree(int u, const Tag &k) {
        LazySegmentTree<Info, Tag>::rangeApply(L[u], R[u], k);
    }
    Info query_tree(int u) {
        return LazySegmentTree<Info, Tag>::rangeQuery(L[u], R[u]);
    }
};