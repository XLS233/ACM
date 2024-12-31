#pragma once

#include <bits/stdc++.h>

namespace HIGHP {
    void trans(std::string a, std::vector<int> &A) {
        for (int i = a.size() - 1; i >= 0; i -- ) A.push_back(a[i] - '0');
    }

    bool cmp(std::string a, std::string b) {
        if (a.size() != b.size()) return a.size() > b.size();
        for (int i = 0; i < a.size(); i ++ )
            if (a[i] != b[i])
                return a[i] > b[i];
        return true;
    }

    std::string sub(std::string a, std::string b);

    std::string add(std::string a, std::string b) {
        if (a[0] == '-' && b[0] == '-') return '-' + add(a.substr(1), b.substr(1));
        else if (a[0] == '-') return sub(b, a.substr(1));
        else if (b[0] == '-') return sub(a, b.substr(1));

        if (a.size() < b.size()) return add(b, a);

        std::vector<int> A, B;
        trans(a, A), trans(b, B);

        std::vector<int> C;
        int t = 0;
        for (int i = 0; i < A.size(); i ++ )
        {
            t += A[i];
            if (i < B.size()) t += B[i];
            C.push_back(t % 10);
            t /= 10;
        }
        if (t) C.push_back(t);

        std::string c = "";
        for (int i = C.size() - 1; i >= 0; i -- ) c += (char)C[i] + '0';
        return c;
    }

    std::string sub(std::string a, std::string b) {
        if (a[0] == '-' && b[0] == '-') return sub(b.substr(1), a.substr(1));
        else if (a[0] == '-') return '-' + add(a.substr(1), b);
        else if (b[0] == '-') return add(a, b.substr(1));

        if (!cmp(a, b)) return '-' + sub(b, a);

        std::vector<int> A, B;
        trans(a, A), trans(b, B);

        std::vector<int> C;
        for (int i = 0, t = 0; i < A.size(); i ++ )
        {
            t = A[i] - t;
            if (i < B.size()) t -= B[i];
            C.push_back((t + 10) % 10);
            if (t < 0) t = 1;
            else t = 0;
        }
        while (C.size() > 1 && C.back() == 0) C.pop_back();

        std::string s = "";
        for (int i = C.size() - 1; i >= 0; i -- ) s += (char)C[i] + '0';
        return s;
    }

    std::string mul(std::string a, std::string b) {
        if (a[0] == '-' && b[0] == '-') return mul(a.substr(1), b.substr(1));
        else if (a[0] == '-') return '-' + mul(a.substr(1), b);
        else if (b[0] == '-') return '-' + mul(a, b.substr(1));

        std::vector<int> A, B;
        trans(a, A), trans(b, B);

        int num = a.size() + b.size() - 1;
        std::vector<int> C(num + 1);
        for (int i = 0; i < num; i ++ )
        {
            for (int j = 0; j <= i; j ++ ) 
                C[i] += (j < a.size() ? A[j] : 0) * ((i - j) < b.size() ? B[i - j] : 0);

            if (C[i] >= 0)
            {
                C[i + 1] += C[i] / 10;
                C[i] %= 10;
            }
        }
        while (C.size() > 1 && C.back() == 0) C.pop_back();
        
        std::string s = "";
        for (int i = C.size() - 1; i >= 0; i -- ) s += (char)C[i] + '0';
        return s;
    }

    std::string mul(std::string a, int b) {
        if (a[0] == '-' && b < 0) return mul(a.substr(1), -b);
        else if (a[0] == '-') return '-' + mul(a.substr(1), b);
        else if (b < 0) return '-' + mul(a, -b);

        std::vector<int> A;
        trans(a, A);

        std::vector<int> C;
        int t = 0;
        for(int i = 0; i < A.size() || t; i ++ )
        {
            if(i < A.size()) t += A[i] * b;
            C.push_back(t % 10);
            t /= 10;
        }
        while(C.size() > 1 && C.back() == 0) C.pop_back();

        std::string s = "";
        for (int i = C.size() - 1; i >= 0; i -- ) 
        {
            s += C[i] % 10 + '0';
            C[i] /= 10;
            while (C[i])
            {
                s += (char)(C[i] % 10) + '0';
                C[i] /= 10;
            }
        }
        return s;
    }

    std::string div(std::string a, int b, int &r) {
        std::vector<int> A, C;
        trans(a, A);
        r = 0;
        for(int i = A.size() - 1; i >= 0; i -- )
        {
            r = r * 10 + A[i];
            C.push_back(r / b);
            r %= b;
        }
        reverse(C.begin(), C.end());
        while(C.size() > 1 && C.back() == 0) C.pop_back();

        std::string s = "";
        for (int i = C.size() - 1; i >= 0; i -- ) s += (char)C[i] + '0';
        return s;
    }
}

struct H {
    using i64 = long long;
    std::string x;
    H(int x = 0) : x(std::to_string(x)) {}
    H(std::string s) : x(s) {}
    H operator-() const {
        if (x[0] == '-') {
            return x.substr(1);
        } else {
            return "-" + x;
        }
    }
    H &operator*=(const H &rhs) {
        x = HIGHP::mul(x, rhs.x);
        return *this;
    }
    H &operator+=(const H &rhs) {
        x = HIGHP::add(x, rhs.x);
        return *this;
    }
    H &operator-=(const H &rhs) {
        x = HIGHP::sub(x, rhs.x);
        return *this;
    }
    friend H operator*(const H &lhs, const H &rhs) {
        H res = lhs;
        res *= rhs;
        return res;
    }
    friend H operator+(const H &lhs, const H &rhs) {
        H res = lhs;
        res += rhs;
        return res;
    }
    friend H operator-(const H &lhs, const H &rhs) {
        H res = lhs;
        res -= rhs;
        return res;
    }
    H &operator*=(const int &rhs) {
        x = HIGHP::mul(x, rhs);
        return *this;
    }
    H &operator/=(const int &rhs) {
        int r = 0;
        x = HIGHP::div(x, rhs, r);
        return *this;
    }
    int operator%=(const int &rhs) {
        int r = 0;
        x = HIGHP::div(x, rhs, r);
        return r;
    }
    friend H operator*(const H &lhs, const int &rhs) {
        H res = lhs;
        res *= rhs;
        return res;
    }
    friend H operator/(const H &lhs, const int &rhs) {
        H res = lhs;
        res /= rhs;
        return res;
    }
    friend int operator%(const H &lhs, const int &rhs) {
        H res = lhs;
        int r = 0;
        res.x = HIGHP::div(res.x, rhs, r);
        return r;
    }
};