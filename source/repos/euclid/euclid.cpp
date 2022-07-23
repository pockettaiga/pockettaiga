#include <iostream>

//задача 0
//алгоритм евклида (итерационный)
int euclid(int a, int b)
{
    while ((a != 0) && (b != 0))
    {
        if (a > b)
        {
            a %= b;
        }
        else
        {
            b %= a;
        }
    }
    return (a + b);
}

//алгоритм евклида (рекурсивный)
int euclid_recursive(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return euclid_recursive(b, a % b);
}


//задача 1
//алгоритм евклида (бинарный)
int euclid_binary(int x, int y)
{
    int k = 0;
    if ((x == 0) || (y == 0))
    {
        return (x + y);
    }
    while (((x & 1) == 0) && ((y & 1) == 0))
    {
        ++k;
        x >>= 1;
        y >>= 1;
    }
    while ((x != 0) && (y != 0))
    {
        if ((x & 1) == 0)
        {
            x >>= 1;
        }
        else if ((y & 1) == 0)
        {
            y >>= 1;
        }
        else
        {
            if (x > y)
            {
                x -= y;
            }
            else
            {
                y -= x;
            }
        }
    }
    return ((x + y) << k);
}

int main() {
    int a; int b;
    std::cin >> a;
    std::cin >> b;
    std::cout << euclid_binary(a, b);
    return 0;
}