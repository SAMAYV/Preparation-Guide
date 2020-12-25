long long p = 1;
while (n % 2 == 0)
{
    p = 2;
    n /= 2;
}
for (int i = 3; i <= sqrt(n); i += 2)
{
    while (n % i == 0)
    {
        p = i;
        n = n / i;
    }
}
if (n > 2)
//n is prime
{
    p = n;
}
cout << p << endl;
