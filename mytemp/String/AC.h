#pragma once

#include <bits/stdc++.h>

struct ACAM {
    static constexpr int ALPHABET_SIZE = 26, N = 1000010;
    struct Node {
        int s[ALPHABET_SIZE], fail;
    }tr[N];
    int idx, root;
    ACAM() { clear(); }
    void clear() {
        memset(tr[0].s, 0, sizeof tr[0].s);
        tr[0].fail = root = idx = 0;
    }
    int new_node() {
        idx ++ ;
        memset(tr[idx].s, 0, sizeof tr[idx].s);
        tr[idx].fail = 0;
        return idx;
    }
    void insert(std::string &s, int i) {
        int p = root;
        for (auto c : s) {
            int u = c - 'a';
            if (!tr[p].s[u]) tr[p].s[u] = new_node();
            p = tr[p].s[u];
        }
    }
    void build() {
        std::queue<int> q;
        for (int i = 0; i < 26; i ++ ) {
            if (tr[0].s[i]) {
                q.push(tr[0].s[i]);
            }
        }
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i ++ ) {
                int v = tr[u].s[i];
                if (v == 0) {
                    tr[u].s[i] = tr[tr[u].fail].s[i];
                } else {
                    tr[v].fail = tr[tr[u].fail].s[i];
                    q.push(v);
                }
            }
        }
    }
}AC;