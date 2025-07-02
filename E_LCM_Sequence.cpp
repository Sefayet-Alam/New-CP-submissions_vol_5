#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<long long> sieve(long long limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<long long> primes;
    for (long long i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

bool is_prime_power(long long n, const vector<long long>& primes) {
    if (n < 2) return false;
    for (long long p : primes) {
        if (p * p > n) break;
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            return n == 1;
        }
    }
    return true;
}

int main() {
    long long L, R;
    cin >> L >> R;

    long long max_prime = sqrt(R);
    vector<long long> primes = sieve(max_prime);

    int count = 0;
    for (long long n = L; n <= R; ++n) {
        if (is_prime_power(n, primes)) {
            ++count;
        }
    }

    cout << count << endl;

    return 0;
}