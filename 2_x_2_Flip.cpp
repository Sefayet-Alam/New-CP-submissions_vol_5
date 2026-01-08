#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Modulo constant
long long MOD = 998244353;

// Constants for array sizes
// MAX_K needs to be large enough for factorials. 
// Polynomials go up to K/2. Precomputation needs access to invFact up to 2*(K/2)+1.
const int MAX_K = 10100; 
const int MAX_K_HALF = 5050;

long long fact[MAX_K];
long long invFact[MAX_K];
long long inv[MAX_K];

// Modular Exponentiation
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// Precompute factorials and inverses
void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    inv[1] = 1;
    // Linear inverse precomputation
    for (int i = 2; i < MAX_K; i++)
        inv[i] = (MOD - (MOD / i) * inv[i % MOD] % MOD) % MOD;
    
    for (int i = 1; i < MAX_K; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}

// Compute ln(P(z)) where P(z) = 1 + c_1 z + ...
// Returns C(z) such that P(z) = exp(C(z)) and C(0) = 0
// Complexity: O(n^2)
vector<long long> poly_ln(const vector<long long>& P, int n) {
    vector<long long> C(n);
    C[0] = 0; 
    for (int m = 1; m < n; m++) {
        long long sum = 0;
        // Formula derived from P' = P * C'
        for (int j = 1; j < m; j++) {
            sum = (sum + (long long)j * C[j] % MOD * P[m - j]) % MOD;
        }
        // c_m = p_m - (1/m) * sum_{j=1}^{m-1} j * c_j * p_{m-j}
        long long term = (P[m] - sum * inv[m] % MOD + MOD) % MOD;
        C[m] = term;
    }
    return C;
}

// Compute exp(Q(z)) where Q(0) = 0
// Complexity: O(n^2)
vector<long long> poly_exp(const vector<long long>& Q, int n) {
    vector<long long> P(n);
    P[0] = 1; 
    for (int m = 1; m < n; m++) {
        long long sum = 0;
        // Formula derived from P' = P * Q'
        for (int j = 1; j <= m; j++) {
            sum = (sum + (long long)j * Q[j] % MOD * P[m - j]) % MOD;
        }
        P[m] = (sum * inv[m]) % MOD;
    }
    return P;
}

// Global precomputed logs of base functions
vector<long long> LS_poly, LC_poly;

void precompute_polys() {
    int max_deg = MAX_K_HALF;
    vector<long long> S(max_deg), C(max_deg);
    
    // S(z) corresponds to sinh(x)/x = sum x^2i / (2i+1)! 
    // In z-domain (z=x^2), coeff of z^i is 1/(2i+1)!
    for (int i = 0; i < max_deg; i++) {
        if (2 * i + 1 < MAX_K)
            S[i] = invFact[2 * i + 1];
        else
            S[i] = 0; 
    }
    
    // C(z) corresponds to cosh(x) = sum x^2i / (2i)!
    // In z-domain, coeff of z^i is 1/(2i)!
    for (int i = 0; i < max_deg; i++) {
        if (2 * i < MAX_K)
            C[i] = invFact[2 * i];
        else
            C[i] = 0;
    }
    
    // Compute log of these series once
    LS_poly = poly_ln(S, max_deg);
    LC_poly = poly_ln(C, max_deg);
}

void solve(int t) {
    int m, n, K, b;
    if (!(cin >> m >> n >> K >> b)) return;
    
    vector<int> rows(b), cols(b);
    for(int i=0; i<b; i++) {
        cin >> rows[i] >> cols[i];
    }
    
    // Count rows with odd number of 1s
    sort(rows.begin(), rows.end());
    int cnt_r = 0;
    if (b > 0) {
        int curr = rows[0];
        int count = 1;
        for (int i = 1; i < b; i++) {
            if (rows[i] == curr) count++;
            else {
                if (count % 2 != 0) cnt_r++;
                curr = rows[i];
                count = 1;
            }
        }
        if (count % 2 != 0) cnt_r++;
    }
    
    // Count cols with odd number of 1s
    sort(cols.begin(), cols.end());
    int cnt_c = 0;
    if (b > 0) {
        int curr = cols[0];
        int count = 1;
        for (int i = 1; i < b; i++) {
            if (cols[i] == curr) count++;
            else {
                if (count % 2 != 0) cnt_c++;
                curr = cols[i];
                count = 1;
            }
        }
        if (count % 2 != 0) cnt_c++;
    }
    
    // We work with polynomials up to degree K/2
    int limit_deg = K / 2 + 1;
    vector<long long> T_R(limit_deg), T_C(limit_deg);
    
    // Generating function for rows: (sinh x)^cnt_r * (cosh x)^(m - cnt_r)
    // In logs: cnt_r * ln(sinh x) + (m - cnt_r) * ln(cosh x)
    // Note: sinh(x) = x * (sinh x / x). ln(sinh x) = ln x + ln(sinh x / x)
    // The x^cnt_r factor shifts the powers. We compute the rest using z = x^2.
    
    long long A = cnt_r;
    long long B = (m - cnt_r) % MOD;
    
    for(int i=0; i<limit_deg; i++) {
        // Use precomputed logs of S(z) and C(z)
        T_R[i] = (A * LS_poly[i] + B * LC_poly[i]) % MOD;
    }
    
    long long A_c = cnt_c;
    long long B_c = (n - cnt_c) % MOD;
    for(int i=0; i<limit_deg; i++) {
        T_C[i] = (A_c * LS_poly[i] + B_c * LC_poly[i]) % MOD;
    }
    
    // Exponentiate to get coefficients
    vector<long long> E_R = poly_exp(T_R, limit_deg);
    vector<long long> E_C = poly_exp(T_C, limit_deg);
    
    long long ans = 0;
    
    for (int k = 0; k <= K; k++) {
        long long ways_r = 0;
        // For rows: we extracted x^cnt_r. The remaining part is a function of x^2.
        // So we have terms x^cnt_r * x^2j = x^(cnt_r + 2j).
        // A valid length k must satisfy k >= cnt_r and parity match.
        if (k >= cnt_r && (k - cnt_r) % 2 == 0) {
            int idx = (k - cnt_r) / 2;
            if (idx < limit_deg) {
                ways_r = (E_R[idx] * fact[k]) % MOD;
            }
        }
        
        long long ways_c = 0;
        if (k >= cnt_c && (k - cnt_c) % 2 == 0) {
            int idx = (k - cnt_c) / 2;
            if (idx < limit_deg) {
                ways_c = (E_C[idx] * fact[k]) % MOD;
            }
        }
        
        ans = (ans + ways_r * ways_c) % MOD;
    }
    
    cout << "Case " << t << ": " << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    precompute_polys();
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; i++) {
            solve(i);
        }
    }
    return 0;
}