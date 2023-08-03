#pragma once
#include <vector>
#include <cmath>

template<class Info>
struct ST {
    int n, m;
    std::vector<std::vector<Info>> st1, st2;
    ST() {}
    ST(std::vector<Info> &w) : n(w.size()), m(ceil(log2(n))), st1(n, std::vector<Info>(m)), st2(n, std::vector<Info>(m)) {
        for (int j = 0; j < m; j ++ ) {
            for (int i = 0; i + (1 << j) - 1 < n; i ++ ) {
                if (j == 0) {
                    st1[i][j] = w[i];
                    st2[i][j] = w[i];
                } else {
                    st1[i][j] = max(st1[i][j - 1], st1[i + (1 << j - 1)][j - 1]);
                    st2[i][j] = min(st2[i][j - 1], st2[i + (1 << j - 1)][j - 1]);
                }
            }
        }
    }
    Info querymax(int l, int r) {
        assert(l <= r);
        int len = r - l + 1;
        int k = log2(len);
        return max(st1[l][k], st1[r - (1 << k) + 1][k]);
    }
    Info querymin(int l, int r) {
        assert(l <= r);
        int len = r - l + 1;
        int k = log2(len);
        return min(st2[l][k], st2[r - (1 << k) + 1][k]);
    }
};