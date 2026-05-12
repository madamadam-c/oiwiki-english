#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const double PI = acos(-1.0);

struct Complex {
  double x, y;

  Complex(double _x = 0.0, double _y = 0.0) {
    x = _x;
    y = _y;
  }

  Complex operator-(const Complex &b) const {
    return Complex(x - b.x, y - b.y);
  }

  Complex operator+(const Complex &b) const {
    return Complex(x + b.x, y + b.y);
  }

  Complex operator*(const Complex &b) const {
    return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
  }
};

/*
 * Bit-reversal transform before FFT and IFFT
 * Swap position i with the position of the bit-reversal of i
 *len must be a power of 2
 */
void change(Complex y[], int len) {
  int i, j, k;
  for (int i = 1, j = len / 2; i < len - 1; i++) {
    if (i < j) swap(y[i], y[j]);
    // Swap elements whose indices are bit-reversals; i<j ensures one swap
    // i increments normally, while j increments in bit-reversed order, keeping i and j reversed
    k = len / 2;
    while (j >= k) {
      j = j - k;
      k = k / 2;
    }
    if (j < k) j += k;
  }
}

/*
 * Perform FFT
 *len must be of the form 2^k
 *on == 1 means DFT, on == -1 means IDFT
 */
void fft(Complex y[], int len, int on) {
  change(y, len);
  for (int h = 2; h <= len; h <<= 1) {
    Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
    for (int j = 0; j < len; j += h) {
      Complex w(1, 0);
      for (int k = j; k < j + h / 2; k++) {
        Complex u = y[k];
        Complex t = w * y[k + h / 2];
        y[k] = u + t;
        y[k + h / 2] = u - t;
        w = w * wn;
      }
    }
  }
  if (on == -1) {
    for (int i = 0; i < len; i++) {
      y[i].x /= len;
    }
  }
}

constexpr int MAXN = 200020;
Complex x1[MAXN], x2[MAXN];
char str1[MAXN / 2], str2[MAXN / 2];
int sum[MAXN];

int main() {
  while (cin >> str1 >> str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = 1;
    while (len < len1 * 2 || len < len2 * 2) len *= 2;
    // a * b optimization from three transforms to two
    // Applies when reducing three FFTs in two-polynomial multiplication to two
    // Principle: (a+bi)^2= (a^2-b^2) + 2abi
    // After FFT coefficient-to-point multiplication and converting back to coefficients,
    // divide the imaginary part by 2 (multiply by 0.5/len) to get the result
    for (int i = 0; i < len1 && i < len2; i++)
      x1[i] = Complex(str1[len1 - 1 - i] - '0', str2[len2 - 1 - i] - '0');
    if (len1 >= len2)
      for (int i = len2; i < len1; i++)
        x1[i] = Complex(str1[len1 - 1 - i] - '0', 0);
    else
      for (int i = len1; i < len2; i++)
        x1[i] = Complex(0, str2[len2 - 1 - i] - '0');
    for (int i = max(len1, len2); i < len; i++) x1[i] = Complex(0, 0);
    fft(x1, len, 1);
    for (int i = 0; i < len; i++) x1[i] = x1[i] * x1[i];
    fft(x1, len, -1);
    double ilen = 0.5 / len;
    // Divide by len because IDFT (line 64) did not process the imaginary part
    for (int i = 0; i < len; i++) sum[i] = int(x1[i].y * ilen + 0.5);
    for (int i = 0; i < len; i++) {
      sum[i + 1] += sum[i] / 10;
      sum[i] %= 10;
    }
    len = len1 + len2 - 1;
    while (sum[len] == 0 && len > 0) len--;
    for (int i = len; i >= 0; i--) cout << char(sum[i] + '0');
    cout << '\n';
  }
  return 0;
}

// Keep going!
