#include <stdio.h>
#include <string.h>

long long power(long long a, long long b, long long p)
{
    long long result = 1;
    a %= p;

    while (b > 0)
    {
        if (b % 2)
            result = (result * a) % p;

        a = (a * a) % p;
        b /= 2;
    }

    return result;
}

long long inverse(long long a, long long m)
{
    long long t = 0, newt = 1;
    long long r = m, newr = a % m;

    while (newr != 0)
    {
        long long q = r / newr;
        long long temp;

        temp = t - q * newt;
        t = newt;
        newt = temp;

        temp = r - q * newr;
        r = newr;
        newr = temp;
    }

    if (r > 1)
        return -1;
    if (t < 0)
        t += m;

    return t;
}

int isPrime(long long n)
{
    long long i;
    if (n < 2)
        return 0;
    for (i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int isPrimitiveRoot(long long g, long long p)
{
    long long i;
    for (i = 1; i < p - 1; i++)
        if (power(g, i, p) == 1)
            return 0;
    return power(g, p - 1, p) == 1;
}

int main()
{
    long long p, g, x, m, k;
    long long y, r, s, kInv;
    long long rm, rr, rs;

    printf("Enter prime p: ");
    if (scanf("%lld", &p) != 1 || !isPrime(p))
    {
        printf("Error: p must be a prime number.\n");
        return 0;
    }

    printf("Enter primitive root g: ");
    if (scanf("%lld", &g) != 1 || g < 2 || g >= p || !isPrimitiveRoot(g, p))
    {
        printf("Error: g must be a primitive root modulo p.\n");
        return 0;
    }

    printf("Enter private key x (1 to p-2): ");
    if (scanf("%lld", &x) != 1 || x < 1 || x > p - 2)
    {
        printf("Invalid private key.\n");
        return 0;
    }

    printf("Enter message hash m (non-negative): ");
    if (scanf("%lld", &m) != 1 || m < 0)
    {
        printf("Invalid message hash.\n");
        return 0;
    }

    printf("Enter random number k (coprime to p-1): ");
    if (scanf("%lld", &k) != 1 || k < 1 || k > p - 2 || inverse(k, p - 1) == -1)
    {
        printf("Invalid k. Choose a number coprime to p-1.\n");
        return 0;
    }

    y = power(g, x, p);
    r = power(g, k, p);
    kInv = inverse(k, p - 1);
    s = ((((m % (p - 1)) - (x * r) % (p - 1)) + (p - 1)) % (p - 1) * kInv) % (p - 1);

    printf("\nPublic key y = %lld\n", y);
    printf("Signature (r, s) = (%lld, %lld)\n", r, s);

    printf("\nEnter received message hash: ");
    if (scanf("%lld", &rm) != 1 || rm < 0)
    {
        printf("Invalid message hash.\n");
        return 0;
    }
    printf("Enter received r: ");
    if (scanf("%lld", &rr) != 1)
    {
        printf("Invalid signature.\n");
        return 0;
    }
    printf("Enter received s: ");
    if (scanf("%lld", &rs) != 1)
    {
        printf("Invalid signature.\n");
        return 0;
    }

    if (rr < 1 || rr >= p || rs < 0 || rs >= p - 1)
    {
        printf("Signature is INVALID\n");
        return 0;
    }

    if (power(g, rm % (p - 1), p) == (power(y, rr, p) * power(rr, rs, p)) % p)
        printf("Signature is VALID\n");
    else
        printf("Signature is INVALID\n");

    return 0;
}
