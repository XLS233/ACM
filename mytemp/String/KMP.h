#pragma once

#include <string>
#include <vector>

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