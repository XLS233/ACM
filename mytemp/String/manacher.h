#pragma once

#include <vector>
#include <string>

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