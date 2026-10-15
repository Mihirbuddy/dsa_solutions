#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

// Counts the number of digits
int countDigits(long long number) {
    number = llabs(number);

    if (number == 0) {
        return 1;
    }

    int digits = 0;

    while (number > 0) {
        digits++;
        number /= 10;
    }

    return digits;
}

// Calculates 10^power
long long powerOf10(int power) {
    long long result = 1;

    for (int i = 0; i < power; i++) {
        result *= 10;
    }

    return result;
}

long long karatsuba(long long x, long long y) {
    // Handle negative numbers
    if (x < 0) {
        return -karatsuba(-x, y);
    }

    if (y < 0) {
        return -karatsuba(x, -y);
    }

    // Base case: directly multiply single-digit numbers
    if (x < 10 || y < 10) {
        return x * y;
    }

    int digitsX = countDigits(x);
    int digitsY = countDigits(y);

    int n = max(digitsX, digitsY);

    // Number of digits in the right half
    int half = n / 2;

    long long base = powerOf10(half);

    /*
        x = a * base + b
        y = c * base + d
    */

    long long a = x / base;
    long long b = x % base;

    long long c = y / base;
    long long d = y % base;

    // Three recursive multiplications
    long long ac = karatsuba(a, c);
    long long bd = karatsuba(b, d);

    long long sumProduct = karatsuba(a + b, c + d);

    // ad + bc
    long long middle = sumProduct - ac - bd;

    // ac * base^2 + (ad + bc) * base + bd
    return ac * base * base + middle * base + bd;
}

int main() {
    long long firstNumber, secondNumber;

    cout << "Enter first number: ";
    cin >> firstNumber;

    cout << "Enter second number: ";
    cin >> secondNumber;

    cout << "Product = "
         << karatsuba(firstNumber, secondNumber)
         << '\n';

    return 0;
}