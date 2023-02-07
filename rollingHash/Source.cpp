#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <bits/stdc++.h>
using namespace std;
long long mod1 = 1000000007;
long long mod2 = 1e9 + 1;
long long powers1[100005] = {};
long long powers2[100005] = {};
long long initialHash1(const string& s, int len) {
    long long sum = 0;
    size_t j = 0;
    long long p = len - 1;
    for (auto i = 0; i < len; i++) {
        sum += (s[i] - 'a' + 1) * powers1[p--];
        sum = sum % mod1;
    }
    return sum;
}
long long initialHash2(const string& s, int len) {
    long long sum = 0;
    size_t j = 0;
    long long p = len - 1;
    for (auto i = 0; i < len; i++) {
        sum += (s[i] - 'a' + 1) * powers2[p--];
        sum = sum % mod2;
    }
    return sum;
}
long long rolling_hash1(long long& currentHash, char out, char in, int len) {
    currentHash = (currentHash - (out - 'a' + 1) * powers1[len - 1]) % mod1;
    if (currentHash < 0)currentHash += mod1;
    currentHash = (currentHash * 97 + (in - 'a' + 1)) % mod1;
    return currentHash;
}
long long rolling_hash2(long long& currentHash, char out, char in, int len) {
    currentHash = (currentHash - (out - 'a' + 1) * powers2[len - 1]) % mod2;
    if (currentHash < 0)currentHash += mod2;
    currentHash = (currentHash * 41 + (in - 'a' + 1)) % mod2;
    return currentHash;
}
bool contains(int len, const string& s1, const string& s2) {
    if (s1.size() < s2.size()) return contains(len, s2, s1);
    unordered_set<long long>s;
    unordered_set<long long>m;
    long long currentHash1 = initialHash1(s2, len);
    long long currentHash2 = initialHash2(s2, len);
    s.insert(currentHash1);
    m.insert(currentHash2);
    for (auto i = 0; i < s2.size() - len; i++) {
        long long rolling1 = rolling_hash1(currentHash1, s2[i], s2[i + len], len);
        long long rolling2 = rolling_hash2(currentHash2, s2[i], s2[i + len], len);
        s.insert(rolling1);
        m.insert(rolling2);
    }
    long long secondCurrentHash1 = initialHash1(s1, len);
    long long secondCurrentHash2 = initialHash2(s1, len);
    if (s.count(secondCurrentHash1) && m.count(secondCurrentHash2)) return true;
    for (auto i = 0; i < s1.size() - len; i++) {
        long long rolling1 = rolling_hash1(secondCurrentHash1, s1[i], s1[i + len], len);
        long long rolling2 = rolling_hash2(secondCurrentHash2, s1[i], s1[i + len], len);
        if (s.count(rolling1) && m.count(rolling2)) return true;
    }
    return false;
}
int main() {
    long long multiple1 = 1;
    long long multiple2 = 1;
    for (auto i = 0; i < 100005; i++) {
        powers1[i] = multiple1;
        multiple1 = (multiple1 * 97) % mod1;
    }
    for (auto i = 0; i < 100005; i++) {
        powers2[i] = multiple2;
        multiple2 = (multiple2 * 41) % mod2;
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1;
    string s2;
    cin >> s1 >> s2;
    int k = min(s1.size(), s2.size());
    size_t answer = 0;
    int i = 0;
    while (i <= k) {
        int mid = i + (k - i) / 2;
        if (contains(mid, s1, s2)) {
            answer = mid;
            i = mid + 1;
        }
        else {
            k = mid - 1;
        }
    }
    cout << answer << "\n";

    return 0;
}