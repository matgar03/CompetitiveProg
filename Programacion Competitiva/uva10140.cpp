#include <vector>
#include <iostream>
#include <climits>
#include <bitset>
#include <cmath>

using namespace std;

const int MAX_PRIME = 46341;
int a, b;

bitset<MAX_PRIME + 1> bs; // #include <bitset>
vector<uint> primes;      // unsigned int
void sieve()
{
    bs.set();          // De momento, todos son primos
    bs[0] = bs[1] = 0; // El 0 y el 1 no lo son.
    for (uint i = 2; i <= MAX_PRIME; ++i)
    {
        if (bs[i])
        {
            // El actual es primo. Tiramos sus m´ultiplos
            for (uint j = i * i; j <= MAX_PRIME; j += i)
                bs[j] = 0;
            primes.push_back(i);
        } // if es primo
    }     // for
} // sieve

bool isPrime(unsigned long long n)
{
    if (n <= MAX_PRIME)
        return bs[n];
    for (unsigned int i = 0;
         primes[i] * primes[i] <= n; ++i)
    {
        if (!(n % primes[i]))
            return false;
    }
    return true;
}

void prim(int primo, vector<bool> &v, int a, int b)
{
    unsigned int i; //MIRAR SI FALLA
    if (a % primo == 0)
        i = a / primo;
    else
        i = a / primo + 1;
    if (i <= 1)
        i = 2;
    i *= primo;

    while (i <= b)
    {
        v[i - a] = true;
        i += primo;
    }
}

void sol()
{
    vector<bool> v(b - a + 1, false);
    for (int i = 0; i < primes.size() && primes[i] <= b; ++i)
    {
        prim(primes[i], v, a, b);
    }
    if (a == 1)
        v[0] = true;
    int cont = 0, largo = 0, corto = INT_MAX, pri = -1, lini, cini, i = 0;
    for (i; i < v.size() && pri == -1; ++i)
    {
        if (!v[i])
            pri = i;
    }
    for (i; i < v.size(); ++i)
    {
        if (!v[i])
        {
            if (i - pri > largo)
            {
                lini = pri;
                largo = i - pri;
            }
            if (i - pri < corto)
            {
                cini = pri;
                corto = i - pri;
            }
            pri = i;
        }
    }
    if (largo == 0)
        cout << "There are no adjacent primes.\n";
    else
    {
        cout << cini + a << ',' << cini + a + corto << " are closest, " << lini + a << ',' << lini + a + largo << " are most distant.\n";
    }
}

int main()
{
    sieve();
    while (cin >> a >> b)
    {
        sol();
    }
    return 0;
}