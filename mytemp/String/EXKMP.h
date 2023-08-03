#pragma once

#include <string>
#include <vector>

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