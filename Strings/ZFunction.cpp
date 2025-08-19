#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> Z(const string& S) {
    vector<ll> z(S.size());
    int l = -1, r = -1;

    for (ll i = 1; i < S.size(); i++) {
        if (i >= r)
            z[i] = 0;
        else
            z[i] = min(r - i, z[i - l]);

        while (i + z[i] < S.size() && S[i + z[i]] == S[z[i]])
            z[i]++;

        if (i + z[i] > r)
            l = i, r = i + z[i];
    }

    return z;
}