#pragma once

#include <bits/stdc++.h>

struct KMP {
    int n;
    std::string p;
    std::vector<int> nxt;
    KMP(std::string &s) : n(s.size() - 1), p(s), nxt(n + 1) {
        for (int i = 2, j = 0; i <= n; i ++ ) {
            while (j && p[i] != p[j + 1]) j = nxt[j];
            if (p[i] == p[j + 1]) j ++ ;
            nxt[i] = j;
        }
    }
    int board(int x) {
        return nxt[x];
    }
    std::vector<int> match(std::string &s, bool first_only = false) {
        std::vector<int> start_pos;
        for (int i = 1, j = 0; i < s.size(); i ++ ) {
            while (j && s[i] != p[j + 1]) j = nxt[j];
            if (s[i] == p[j + 1]) j ++ ;
            if (j == n) {
                start_pos.push_back(i - j + 1);
                if (first_only) return start_pos;
                j = nxt[j];
            }
        }
        return start_pos;
    }
    // 循环周期
    std::vector<int> periodic() {
        std::vector<int> ret;
        int now = n;
        while (now) {
            now = nxt[now];
            ret.push_back(n - now);
        }
        return ret;
    }
    // 循环节
    std::vector<int> periodic_loop() {
        std::vector<int> ret;
        for (int x : periodic()) {
            if (n % x == 0) {
                ret.push_back(x);
            }
        }
        return ret;
    }
    int min_periodic_loop() {
        return periodic_loop()[0];
    }
};

// nxt[i] = LCP(T[i,lent],T)
// extend[i] = LCP(S[i,lens],T)
struct EXKMP {
    int n;
    std::string p;
    std::vector<int> nxt;
    EXKMP(std::string &str) : n(str.size() - 1), p(str), nxt(exkmp(p)) {}
    std::vector<int> exkmp(std::string &s) {
        std::vector<int> extend(s.size());
        extend[0] = 0;
        for (int i = 1, st = 0, ed = 0; i < s.size(); i ++ ) {
            extend[i] = i <= ed ? std::min(nxt[i - st + 1], ed - i + 1) : 0;
            while (i + extend[i] < s.size() && extend[i] < n && s[i + extend[i]] == p[extend[i] + 1]) {
                extend[i] ++ ;
            }
            if (i + extend[i] - 1 >= ed && i != 1) {
                st = i, ed = i + extend[i] - 1;
            }
        }
        return extend;
    }
};

// 二维循环周期
int KMP2(std::vector<std::string> &s) {
    int n = s.size(), m = s[0].size();
    int p = n, q = m;
    std::vector<int> row(m + 1);
    for (int k = 1; k <= n; k ++ ) {
        std::vector<int> ne(m + 1);
        for (int i = 2, j = 0; i <= m; i ++ ) {
            while (j && s[k][i] != s[k][j + 1]) j = ne[j];
            if (s[k][i] == s[k][j + 1]) j ++ ;
            ne[i] = j;
        }
        for (int j = ne[m]; j; j = ne[j]) {
            row[m - j] ++ ;
        }
    }
    for (int i = 1; i <= m; i ++ ) {
        if (row[i] == n) {
            q = i;
            break;
        }
    }

    std::vector<int> col(n + 1);
    for (int k = 1; k <= m; k ++ ) {
        std::vector<int> ne(n + 1);
        for (int i = 2, j = 0; i <= n; i ++ ) {
            while (j && s[i][k] != s[j + 1][k]) j = ne[j];
            if (s[i][k] == s[j + 1][k]) j ++ ;
            ne[i] = j;
        }
        for (int j = ne[n]; j; j = ne[j]) {
            col[n - j] ++ ;
        }
    }
    for (int i = 1; i <= n; i ++ ) {
        if (col[i] == m) {
            p = i;
            break;
        }
    }

    return p * q;
}