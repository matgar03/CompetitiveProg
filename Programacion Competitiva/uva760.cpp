#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;
#define MAX_N 100010
string T;
int n;
int RA[MAX_N], tempRA[MAX_N];
int SA[MAX_N], tempSA[MAX_N];
int c[MAX_N];
int LCP[MAX_N];

void countingSort(int k)
{
    int i, sum, maxi = std::max(300, n); // up to 255 ASCII
    memset(c, 0, sizeof c);
    for (i = 0; i < n; ++i)
        ++c[i + k < n ? RA[i + k] : 0];
    for (i = sum = 0; i < maxi; ++i)
    {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; ++i)
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; ++i)
        SA[i] = tempSA[i];
}

// Construcci´on del suffix array
void constructSA()
{
    int i, k, r;
    for (i = 0; i < n; ++i)
        RA[i] = T[i];
    for (i = 0; i < n; ++i)
        SA[i] = i;
    for (k = 1; k < n; k <<= 1)
    {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; ++i)
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] &&
                 RA[SA[i] + k] == RA[SA[i - 1] + k])
                    ? r
                    : ++r;
        for (i = 0; i < n; ++i)
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break;
    }
}

void computeLCP()
{
    int Phi[MAX_N];
    int PLCP[MAX_N];
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; ++i)
        Phi[SA[i]] = SA[i - 1];
    for (i = L = 0; i < n; ++i)
    {
        if (Phi[i] == -1)
        {
            PLCP[i] = 0;
            continue;
        }
        while (T[i + L] == T[Phi[i] + L])
            ++L;
        PLCP[i] = L;
        L = std::max(L - 1, 0);
    }
    for (i = 0; i < n; ++i)
        LCP[i] = PLCP[SA[i]];
}

int main()
{
    string s, aux1, aux2;
    int casos;
    int size1;
    cin >> casos;
    for (int it = 0; it < casos; ++it)
    {
        cin >> T;
        aux1 = aux2 = "";
        size1 = T.size();

        T = T + '$' + T + '#';
        n = T.size();
        constructSA();
        computeLCP();
        vector<int> sol;
        int max = 0;
        for (int i = 1; i < n; ++i)
        {
            if (LCP[i] > max)
            {
                if ((SA[i] != (SA[i - 1] + size1 + 1)) && (SA[i - 1] != (SA[i] + size1 + 1)) && ((SA[i] < size1 && SA[i - 1] > size1) || (SA[i - 1] < size1 && SA[i] > size1)))
                    max = LCP[i];
            }
        }
        /*
        for (int i = 1; i < n; ++i)
        {
            if (LCP[i] == max)
            {
                if ((SA[i] != (SA[i - 1] + size1 + 1)) && (SA[i - 1] != (SA[i] + size1 + 1)) && ((SA[i] < size1 && SA[i - 1] > size1) || (SA[i - 1] < size1 && SA[i] > size1)))
                {
                    aux1 = "";
                    for (int j = 0; j < max; ++j)
                    {
                        aux1 += T[SA[i] + j];
                    }
                }
            }
        }
*/
        cout << max << '\n';
    }

    return 0;
}