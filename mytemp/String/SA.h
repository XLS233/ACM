#pragma once

#include <bits/stdc++.h>

#include "D:\Code\ACM_LAB\mytemp\DataStructure\ST.h"

using i64 = long long;

constexpr int maxm = 127;
struct SA {
    int n, m;
    std::string s;
    std::vector<int> sa, rk, height;
    std::vector<int> x, y, c;
    ST<int> st;
    void get_sa() {
        for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i >= 1; i -- ) sa[c[x[i]] -- ] = i;
        for (int k = 1; k <= n; k *= 2) {
            int num = 0;
            for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
            for (int i = 1; i <= n; i ++ ) { // 此处按顺序枚举所有后缀
                if (sa[i] > k) { // 第i个后缀的第二关键字为第i+k个后缀的第一关键字
                    y[ ++ num] = sa[i] - k; // y记录的是按照第二关键字排序的结果
                }
            }
            for (int i = 1; i <= m; i ++ ) c[i] = 0;
            for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
            for (int i = 1; i <= m; i ++ ) c[i] += c[i - 1];
            for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
            swap(x, y); // 此处y记录的为x的信息
            x[sa[1]] = 1, num = 1;
            for (int i = 2; i <= n; i ++ ) {
                x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
            }
            if (num == n) break;
            m = num;
        }
    }
    void get_height() { // 表示为排名为i和排名为i-1的后缀的最长公共前缀
        for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
        for (int i = 1, k = 0; i <= n; i ++ ) { // 按rank枚举
            if (rk[i] == 1) continue;
            // h[i] = height[rk[i]]，即位与第i个的后缀与排名在它之前的第一个后缀的最长公共前缀
            if (k) k -- ; // 由于h[i]>=h[i-1]-1，因此从k-1开始枚举
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
            height[rk[i]] = k;
        }
    }
    SA(std::string &str) : s(str), n(str.size() - 1), m(maxm), sa(n + m), rk(n + m), height(n + m), x(n + m), y(n + m), c(n + m) {
        get_sa();
        get_height();
        st = ST(height);
    }
    int lcp(int x, int y) { // 得到两个后缀的lcp
        int rkx = rk[x];
        int rky = rk[y];
        if (rkx > rky) std::swap(rkx, rky);
        rkx ++ ;
        int lcp = st.querymax(rkx, rky);
        return lcp;
    }
    i64 get_distinct_substrings() { // sum(n - sa[i] + 1 - height[i])
        i64 ans = 0;
        for (int i = 1; i <= n; i ++ ) {
            ans += n - sa[i] + 1 - height[i];
        }
        return ans;
    }
};