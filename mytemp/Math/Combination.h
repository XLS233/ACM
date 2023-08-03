#pragma once

#include <vector>

using i64 = long long;

struct Combination1 {
    std::vector<std::vector<i64>> c;
    Combination1(int N) : c(N, std::vector<i64>(N)) {
        assert(N <= 70);
        for (int i = 0; i < N; i ++ ) {
            for (int j = 0; j <= i; j ++ ) {
                if (!j) c[i][j] = 1;
                else c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
            }
        }
    }
    i64 operator()(int a, int b) {
        return c[a][b];
    }
};

template<typename Z>
struct Combination2 {
    std::vector<Z> fact, infact;
    Combination2(int N) : fact(N), infact(N) {
        fact[0] = infact[0] = 1;
        for(int i = 1; i < N; i ++ ) {
            fact[i] = fact[i - 1] * i;
        }
        infact[N - 1] = (Z)1 / fact[N - 1];
        for(int i = N - 2; i >= 1; i -- ) {
            infact[i] = infact[i + 1] * (i + 1);
        }
    }
    Z operator()(int a, int b) {
        if (b < 0 || b > a) return Z(0);
        return fact[a] * infact[b] * infact[a - b];
    }
};