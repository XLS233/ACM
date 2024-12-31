#pragma once

#include <bits/stdc++.h>

// 不同回文串的个数有 O(n)个。
// 回文串 S 的回文前缀（后缀）等价于 Border 。
std::vector<int> manacher(std::string &s) {
    std::string b = "$|";
    for (auto c : s) {
        b += c;
        b += '|';
    }
 
    std::vector<int> len(b.size());
    int maxright = 1, mid = 1;
    int ans = 0;
    for (int i = 1; i < b.size(); i ++ ) {
        if (i < maxright) {
            len[i] = std::min(len[2 * mid - i], maxright - i);
        } else {
            len[i] = 1;
        }
        if (i < maxright && i - len[i] < mid) {
            ans = std::max(ans, (i - mid) * 2);
        }
        while (b[i - len[i]] == b[i + len[i]]) {
            len[i] ++ ;
        }
        if (i + len[i] > maxright) {
            maxright = i + len[i];
            mid = i;
        }
    }

    return len;
}