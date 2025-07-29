#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> pi(const string& s) {
    vector<ll> p(s.size());
    for (ll i = 1; i < s.size(); i++) {
        ll g = p[i - 1];
        while (g && s[i] != s[g])
            g = p[g - 1];

        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

vector<ll> match(const string& s, const string& pat) {
    vector<ll> p = pi(pat + '\0' + s), res;
    for (ll i = p.size() - s.size(); i < p.size(); i++) {
        if (p[i] == pat.size())
            res.push_back(i - 2 * pat.size());
    }
    return res;
}