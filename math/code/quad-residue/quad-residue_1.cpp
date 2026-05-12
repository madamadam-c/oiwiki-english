#include <iostream>
#include <random>

long long p, v;  // Modulus and the value of r^2 - a, respectively

struct Poly {
  long long a, b;

  Poly(long long _a = 0, long long _b = 0) : a(_a), b(_b) {}
};

Poly operator*(const Poly& x, const Poly& y) {
  // Overloaded multiplication; see the explanation above for the operation properties
  return Poly((x.a * y.a + v * (x.b * y.b % p)) % p,
              (x.a * y.b + x.b * y.a) % p);
}

// Fast exponentiation of polynomials, used to compute the answer
Poly modpow(Poly a, long long b) {
  Poly res(1, 0);
  while (b) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}

// Ordinary fast exponentiation, used to test quadratic non-residues
long long modpow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1) res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}

// Used to generate random numbers
std::mt19937 rng(std::random_device{}());

long long cipolla(long long a, long long _p) {
  p = _p;
  if (a == 0)
    return 0;  // Special case for 0
  else if (modpow(a, (p - 1) / 2) == p - 1)
    return -1;  // Quadratic non-residue detected, so there is no solution
  else {
    // Randomize r so that r^2 - a is a quadratic non-residue
    long long r;
    for (r = rng() % p;; r = rng() % p) {
      if (modpow((r * r - a + p) % p, (p - 1) / 2) == p - 1) break;
    }
    v = (r * r - a + p) % p;
    return modpow(Poly(r, 1), (p + 1) / 2).a;  // Compute the result from the conclusion formula
  }
}

int main() {
  int t, a, p;
  std::cin >> t;
  while (t--) {
    std::cin >> a >> p;
    int ans = cipolla(a, p);
    if (ans == -1)
      std::cout << "Hola!" << std::endl;
    else if (ans == 0)
      std::cout << 0 << std::endl;
    else {
      // The opposite number is the other solution
      int ans2 = (p - ans) % p;
      if (ans2 < ans) std::swap(ans, ans2);
      std::cout << ans << " " << ans2 << std::endl;
    }
  }
  return 0;
}
