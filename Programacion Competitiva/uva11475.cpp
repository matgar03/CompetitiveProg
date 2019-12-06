#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
string P;
vector<int> b;
int n;
void kmpPreprocess()
{
    int i = 0, j = -1;
    b[0] = -1;
    while (i < n)
    {
        while (j >= 0 && P[i] != P[j])
            j = b[j];
        ++i;
        ++j;
        b[i] = j;
    }
}

int main()
{
    string s;
    while (cin >> s)
    {
        string rv = s;
        reverse(s.begin(), s.end());
        P = s + '#' + rv;
        n = P.length();
        b.resize(n);
        kmpPreprocess();
        int l = b[n - 1];
        string sub = s.substr(l + 1);
        reverse(sub.begin(), sub.end());
        s = sub + s;
        cout << s << '\n';
    }

    return 0;
}