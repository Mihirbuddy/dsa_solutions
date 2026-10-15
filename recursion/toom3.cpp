#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int countDigits(long long number) {
    number = llabs(number);

    if (number == 0) {
        return 1;
    }

    int count = 0;

    while (number > 0) {
        count++;
        number /= 10;
    }

    return count;
}

long long powerOf10(int power) {
    long long result = 1;

    while (power--) {
        result *= 10;
    }

    return result;
}

long long  toom3(long long x, long long y) {
    // Handle negative numbers
    if (x < 0) {
        return -toom3(-x, y);
    }

    if (y < 0) {
        return -toom3(x, -y);
    }

    // Base case
    if (x < 1000 || y < 1000) {
        return x * y;
    }

    int n = max(countDigits(x), countDigits(y));

    // Divide the numbers into three parts
    int partSize = (n + 2) / 3;

    long long base = powerOf10(partSize);
    long long baseSquared = base * base;

    /*
        x = a2 * base^2 + a1 * base + a0
        y = b2 * base^2 + b1 * base + b0
    */

    long long a0 = x % base;
    long long a1 = (x / base) % base;
    long long a2 = x / baseSquared;

    long long b0 = y % base;
    long long b1 = (y / base) % base;
    long long b2 = y / baseSquared;

    // Five recursive multiplications
    long long r0 = toom3(a0, b0);

    long long r1 = toom3(
        a0 + a1 + a2,
        b0 + b1 + b2
    );

    long long rMinus1 = toom3(
        a0 - a1 + a2,
        b0 - b1 + b2
    );

    long long r2 = toom3(
        a0 + 2 * a1 + 4 * a2,
        b0 + 2 * b1 + 4 * b2
    );

    long long rInfinity = toom3(a2, b2);

    /*
        Product polynomial:

        R(t) = c0 + c1*t + c2*t^2 + c3*t^3 + c4*t^4
    */

    long long c0 = r0;
    long long c4 = rInfinity;

    long long sum1 = r1 - c0 - c4;
    long long sumMinus1 = rMinus1 - c0 - c4;

    long long c2 = (sum1 + sumMinus1) / 2;

    long long c1PlusC3 = (sum1 - sumMinus1) / 2;

    long long c1Plus4C3 =
        (r2 - c0 - 4 * c2 - 16 * c4) / 2;

    long long c3 =
        (c1Plus4C3 - c1PlusC3) / 3;

    long long c1 = c1PlusC3 - c3;

    // Substitute t = base
    return c0
         + c1 * base
         + c2 * baseSquared
         + c3 * baseSquared * base
         + c4 * baseSquared * baseSquared;
}

int main() {
    long long firstNumber;
    long long secondNumber;

    cout << "Enter first number: ";
    cin >> firstNumber;

    cout << "Enter second number: ";
    cin >> secondNumber;

    cout << "Product = "
         << toom3(firstNumber, secondNumber)
         << '\n';

    return 0;
}