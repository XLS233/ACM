#pragma once

#include <bits/stdc++.h>

using i64 = long long;
using ULL = unsigned long long;

ULL Prime_Pool[] = {1998585857ul,23333333333ul};
ULL Seed_Pool[]={911,146527,19260817,91815541};
ULL Mod_Pool[]={29123,998244353,1000000009,4294967291ull};

constexpr int P1 = 1e9 + 7, P2 = 1e9 + 9;
struct Hashv {
    int h1, h2;
    Hashv(int base1 = 0, int base2 = 0) : h1(base1), h2(base2) {}
    i64 val() { return 1ll * h1 * P2 + h2; }
    Hashv &operator*=(const Hashv &rhs) {
        h1 = (i64)h1 * rhs.h1 % P1;
        h2 = (i64)h2 * rhs.h2 % P2;
        return *this;
    }
    Hashv &operator+=(const Hashv &rhs) {
        h1 += rhs.h1; if (h1 >= P1) h1 -= P1;
        h2 += rhs.h2; if (h2 >= P2) h2 -= P2;
        return *this;
    }
    Hashv &operator-=(const Hashv &rhs) {
        h1 -= rhs.h1; if (h1 < 0) h1 += P1;
        h2 -= rhs.h2; if (h2 < 0) h2 += P2;
        return *this;
    }
    friend Hashv operator*(const Hashv &lhs, const Hashv &rhs) {
        Hashv res = lhs;
        res *= rhs;
        return res;
    }
    friend Hashv operator+(const Hashv &lhs, const Hashv &rhs) {
        Hashv res = lhs;
        res += rhs;
        return res;
    }
    friend Hashv operator-(const Hashv &lhs, const Hashv &rhs) {
        Hashv res = lhs;
        res -= rhs;
        return res;
    }
    friend bool operator==(const Hashv &lhs, const Hashv &rhs) {
        return lhs.h1 == rhs.h1 && lhs.h2 == rhs.h2;
    }
    friend bool operator<(const Hashv &lhs, const Hashv &rhs) {
        return lhs.h1 != rhs.h1 ? lhs.h1 < rhs.h1 : lhs.h2 < rhs.h2;
    }
};

const Hashv base(131, 233);
// using Hashv = unsigned long long;
// const Hashv base = 233;

struct StringHash {
    const int n;
    std::vector<Hashv> h1, h2, power;
    StringHash(std::string &s) : n(s.size() - 1), h1(n + 2), h2(n + 2), power(n + 2) {
        for (int i = 1; i <= n; i ++ ) h1[i] = h1[i - 1] * base + s[i];
        for (int i = n; i >= 1; i -- ) h2[i] = h2[i + 1] * base + s[i];
        power[0] = Hashv(1, 1);
        // power[0] = 1;
        for (int i = 1; i <= n; i ++ ) power[i] = power[i - 1] * base;
    }
    Hashv hash1(int l, int r) {
        return h1[r] - h1[l - 1] * power[r - l + 1];
    }
    Hashv hash2(int l, int r) {
        return h2[l] - h2[r + 1] * power[r - l + 1];
    }
};