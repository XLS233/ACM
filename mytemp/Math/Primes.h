#pragma once

#include <bits/stdc++.h>

struct Primes {
    std::vector<int> primes, leaf;
    int cnt;
    Primes(int n = 2e7 + 10) : primes(n), leaf(n), cnt(0) {
        for (int i = 2; i < n; i ++ ) {
            if (leaf[i] == 0) {
                primes[leaf[i] = ++ cnt] = i;
            }
            for (int j = 1; primes[j] * i < n; j ++ ) {
                leaf[primes[j] * i] = j;
                if (i % primes[j] == 0) break;
            }
        }
    }
    bool is_primes(int x) { return x == primes[leaf[x]]; }
    std::map<int, int> divide(int x) {
        std::map<int, int> mp;
        for (int i = leaf[x]; i; i = leaf[x]) {
            while (x % primes[i] == 0) {
                x /= primes[i];
                mp[primes[i]] ++ ;
            }
        }
        return mp;
    }
};

std::map<int, int> divide(int x) {
    std::map<int, int> mp;
    for (int i = 2; i <= x / i; i ++ ) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                cnt ++ ;
                x /= i;
            }
            mp[i] += cnt;
        }
    }
    if (x > 1) {
        mp[x] += 1;
    }
    return mp;
}