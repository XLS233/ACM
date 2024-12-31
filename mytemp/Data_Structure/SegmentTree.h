#pragma once

#include <bits/stdc++.h>

template<class Info>
struct SegmentTree {
    const int n;
    std::vector<Info> tr;
    void pushup(int u) {
        tr[u] = tr[u << 1] + tr[u << 1 | 1];
    }
    void modify(int u, int l, int r, int x, const Info &v) {
        if (l == r) {
            tr[u] = v;
            return;
        }
        int mid = ((l + r)) >> 1;
        if (x <= mid) modify(u << 1, l, mid, x, v);
        else modify(u << 1 | 1, mid + 1, r, x, v);
        pushup(u);
    }
    Info rangeQuery(int u, int l, int r, int L, int R) {
        if (r < L || l > R) return Info();
        if (l >= L && r <= R) return tr[u];
        int mid = ((l + r)) >> 1;
        return rangeQuery(u << 1, l, mid, L, R) + rangeQuery(u << 1 | 1, mid + 1, r, L, R);
    }
    SegmentTree(int _n) : n(_n), tr(_n * 4) {}
    SegmentTree(std::vector<Info> init) : SegmentTree(init.size()) {
        auto build = [&](auto build, int u, int l, int r) -> void {
            if (l == r) { tr[u] = init[r]; return; }
            int mid = (l + r) >> 1;
            build(build, u << 1, l, mid), build(build, u << 1 | 1, mid + 1, r);
            pushup(u);
        };
        build(build, 1, 0, n - 1);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n - 1, x, v);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
    Info query(int x) {
        return rangeQuery(x, x);
    }
};

template<class Info, class Tag>
struct LazySegmentTree {
    const int n;
    std::vector<Info> tr;
    std::vector<Tag> tag;
    void pushup(int u) {
        tr[u] = tr[u << 1] + tr[u << 1 | 1];
    }
    void apply(int u, const Tag &v) {
        tr[u] += v;
        tag[u] += v;
    }
    void pushdown(int u) {
        if (tag[u] == Tag()) { return; }
        apply(u << 1, tag[u]);
        apply(u << 1 | 1, tag[u]);
        tag[u] = Tag();
    }
    void modify(int u, int l, int r, int x, const Info &v) {
        if (l == r) {
            tr[u] = v;
            return;
        }
        pushdown(u);
        int mid = (l + r) >> 1;
        if (x <= mid) modify(u << 1, l, mid, x, v);
        else modify(u << 1 | 1, mid + 1, r, x, v);
        pushup(u);
    }
    void rangeApply(int u, int l, int r, int L, int R, const Tag &v) {
        if (l > R || r < L) return;
        if (l >= L && r <= R) {
            apply(u, v);
            return;
        }
        pushdown(u);
        int mid = (l + r) >> 1;
        rangeApply(u << 1, l, mid, L, R, v);
        rangeApply(u << 1 | 1, mid + 1, r, L, R, v);
        pushup(u);
    }
    Info rangeQuery(int u, int l, int r, int L, int R) {
        if (l > R || r < L) return Info();
        if (l >= L && r <= R) return tr[u];
        pushdown(u);
        int mid = (l + r) >> 1;
        auto res = rangeQuery(u << 1, l, mid, L, R) + rangeQuery(u << 1 | 1, mid + 1, r, L, R);
        pushup(u);
        return res;
    }
    LazySegmentTree(int _n) : n(_n), tr(_n * 4), tag(_n * 4) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
        auto build = [&](auto build, int u, int l, int r) -> void {
            if (l == r) { tr[u] = init[r]; return; }
            int mid = (l + r) >> 1;
            build(build, u << 1, l, mid), build(build, u << 1 | 1, mid + 1, r);
            pushup(u);
        };
        build(build, 1, 0, n - 1);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n - 1, x, v);
    }
    void rangeApply(int l, int r, const Tag &v) {
        rangeApply(1, 0, n - 1, l, r, v);
    }
    Info query(int x) {
        return rangeQuery(1, 0, n - 1, x, x);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
};