#pragma once

#include <bits/stdc++.h>

// 节点：至多有 N 个，每个节点表示一种回文串，长度为 len。
// 后继边：S(v) = ch S(u) ch，len[v] = len[u] + 2 。
// 失配边：S(v) 是 S(u) 的最大 Border，即最长回文子串。
struct PAM {
    static constexpr int ALPHABET_SIZE = 26, N = 1000010;
    struct Node {
        // basic
        int s[ALPHABET_SIZE];
        int fail, len, num; // num记录以该点为结尾的回文串的数量
        // extension
        int cnt; // 节点代表的回文串出现的次数
    }tr[N];
    int idx, last;
    std::string s;
    PAM() {
        // 1：奇数根  2：偶数根
        tr[0].fail = 1, tr[0].len = 0;
        tr[1].fail = 0, tr[1].len = -1;
        idx = 1, last = 0;
        memset(tr[0].s, 0, sizeof tr[0].s);
        memset(tr[1].s, 0, sizeof tr[1].s);
    }
    int get_fail(int x, int i) {
        while (s[i - tr[x].len - 1] != s[i]) {
            x = tr[x].fail;
        }
        return x;
    }
    int new_node(int p) {
        int q = ++ idx;
        memset(tr[q].s, 0, sizeof tr[q].s);
        tr[q].fail = tr[q].cnt = 0;
        tr[q].len = tr[p].len + 2;
        return q;
    }
    void insert(std::string &str) {
        s = str;
        for (int i = 1; i < s.size(); i ++ ) {
            int u = s[i] - 'a';
            int p = get_fail(last, i);
            if (!tr[p].s[u]) {
                int q = new_node(p);
                tr[q].fail = tr[get_fail(tr[p].fail, i)].s[u];
                tr[q].num = tr[tr[q].fail].num + 1;
                tr[p].s[u] = q;
            }
            last = tr[p].s[u];
            tr[last].cnt ++ ;
        }
    }
    // 拓扑更新cnt
    void build() {
        for (int i = idx; i >= 2; i -- ) {
            tr[tr[i].fail].cnt += tr[i].cnt;
        }
        tr[0].cnt = tr[1].cnt = 0;
    }
}pam;