#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

const int M = 500;

int a[505], b[505], t[505];

// Big integer multiplication
void mult(int x[], int y[]) {
  memset(t, 0, sizeof(t));
  for (int i = 1; i <= x[0]; i++) {
    for (int j = 1; j <= y[0]; j++) {
      if (i + j - 1 > M) continue;
      t[i + j - 1] += x[i] * y[j];
      t[i + j] += t[i + j - 1] / 10;
      t[i + j - 1] %= 10;
      t[0] = i + j;
    }
  }
  memcpy(b, t, sizeof(b));
}

// Fast exponentiation
void binpow(int p) {
  if (p == 1) {
    memcpy(b, a, sizeof(b));
    return;
  }
  binpow(p / 2);  // (2^(p/2))^2=2^p
  mult(b, b);     // Square b
  if (p % 2 == 1) mult(b, a);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int p;
  cin >> p;
  a[0] = 1;  // Store the number of digits in array a
  a[1] = 2;  // Square 2
  b[0] = 1;  // Store the number of digits in array b
  b[1] = 1;  // Answer array
  binpow(p);
  cout << (int)(log10(2) * p) + 1 << '\n';
  b[1] -= 1;  // Subtract 1 from the last digit
  for (int i = M; i >= 1; i--) {
    cout << b[i];
    if ((i - 1) % 50 == 0) {
      cout << '\n';
    }
  }
}
