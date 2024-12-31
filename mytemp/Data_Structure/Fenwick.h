#pragma once

#include <bits/stdc++.h>

template <typename T> 
struct Fenwick {
    const int n;
    std::vector<T> tr;
    Fenwick(int n = 0) : n(n), tr(n) {}
    int lowbit(int x) { return x & -x; }
    void add(int x, T v) {
        assert((x > 0, "树状数组下标必须大于0"));
        for (int i = x; i < n; i += lowbit(i)) tr[i] += v; 
    }
    void sub(int x, T v) {
        assert((x > 0, "树状数组下标必须大于0"));
        for (int i = x; i < n; i += lowbit(i)) tr[i] -= v;
    }
    T query(int x) { 
        T res = T();
        for (int i = x; i; i -= lowbit(i)) res += tr[i];
        return res;
    }
    T rangeSum(int l, int r) { 
        return query(r) - query(l - 1);
    }
};