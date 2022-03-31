// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char op) {
    switch (op) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    case ' ':
        return 7;
    default:
        return 4;
    }
}

int calc(char op, int a, int b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a/b;
        default:
            return 7;
    }
}

std::string infx2pstfx(std::string inf) {
    std::string out;
    TStack <char, 100> st1;
    for (int i = 0; i < inf.length(); i++) {
        if (prior(inf[i]) == 4) {
            out.push_back(inf[i]);
            out.push_back(' ');
        } else {
            if (prior(inf[i]) == 7) {
                continue;
            } else  if (st1.isEmpty()) {
                st1.push(inf[i]);
            } else if (prior(inf[i]) > prior(st1.get())) {
                st1.push(inf[i]);
            } else if (prior(inf[i]) == 0) {
                st1.push(inf[i]);
            } else if (prior(inf[i]) == 1) {
                while (prior(st1.get()) != 0) {
                    out.push_back(st1.get());
                    out.push_back(' ');
                    st1.pop();
                }
                st1.pop();
            } else {
                while (!st1.isEmpty() && (prior(inf[i]) <= prior(st1.get()))) {
                    out.push_back(st1.get());
                    out.push_back(' ');
                    st1.pop();
                }
                st1.push(inf[i]);
            }
        }
    }
    while (!st1.isEmpty()) {
        out.push_back(st1.get());
        out.push_back(' ');
        st1.pop();
    }
    out.pop_back();
    return out;
}

int eval(std::string pref) {
    TStack <int, 100> st2;
    int ans = 0, a, b;
    for (int i = 0; i < pref.length(); i++) {
        if (prior(pref[i]) == 4) {
            st2.push(pref[i]-'0');
        } else if (prior(pref[i]) < 4) {
            b = st2.get();
            st2.pop();
            a = st2.get();
            st2.pop();
            st2.push(calc(pref[i], a, b));
        }
    }
    ans = st2.get();
    return ans;
}
