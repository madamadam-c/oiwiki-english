An array is a container that stores objects of the same type. The objects stored in an array do not have names; they are accessed by their positions. The size of an array is fixed, and its length cannot be changed arbitrarily.

## Defining Arrays

An array declaration has the form `a[d]`, where `a` is the array name and `d` is the number of elements in the array. At compile time, `d` should be known; in other words, `d` should be an integral constant expression.

```cpp
unsigned int d1 = 42;
const int d2 = 42;
int arr1[d1];  // Error: d1 is not a constant expression
int arr2[d2];  // Correct: arr2 is an array of length 42
```

You cannot directly assign one array to another:

```cpp
int arr1[3];
int arr2 = arr1;  // Error
arr2 = arr1;      // Error
```

Large arrays should be defined as global variables whenever possible. Local variables are created on the stack, and an array that is too large (larger than the stack size) will cause a stack overflow, leading to RE. If an array is declared in global scope, it is created in static storage.

## Accessing Array Elements

Array elements can be accessed with the subscript operator `[]`. Array indices, the values inside the square brackets, start from 0. For example, an array with 10 elements has indices from 0 to 9, not from 1 to 10. However, in OI, for convenience, we often make arrays slightly larger, do not use the first element, and start accessing array elements from index 1.

Example 1: read an integer $n$ from standard input, then read $n$ numbers and store them in an array. Here, $n\leq 1000$.

```cpp
#include <iostream>
using namespace std;

int arr[1001];  // The index range of array arr is [0, 1001)

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
  }
}
```

Example 2: continuing from Example 1, sum the elements in array `arr` and output the sum. The sum of all elements in the array is at most $2^{31} - 1$.

```cpp
#include <iostream>
using namespace std;

int arr[1001];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
  }

  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += arr[i];
  }

  printf("%d\n", sum);
  return 0;
}
```

### Out-of-Bounds Access

An array index $\mathit{idx}$ should satisfy $0\leq \mathit{idx}< \mathit{size}$. If an index is outside this range, the behavior is undefined and may cause unpredictable consequences, such as a segmentation fault or modification of unintended variables.

## Multidimensional Arrays

A multidimensional array is essentially an "array of arrays": the elements of the outer array are themselves arrays. A two-dimensional array requires two dimensions in its definition: the length of the array and the length of the elements inside it. Two indices are needed to access a two-dimensional array:

```cpp
int arr[3][4];  // An array of length 3 whose elements are
                // arrays of length 4 with int elements
arr[2][1] = 1;  // Access a two-dimensional array
```

We often use nested `for` loops to process two-dimensional arrays.

Example: read two numbers $n$ and $m$ from standard input, representing the height and width of a black-and-white image respectively, where $n,m\leq 1000$. For the next $n$ lines, each line contains $m$ space-separated numbers representing the brightness values at those positions. We read this image and store it in a two-dimensional array.

```cpp
const int MAXN = 1001;
int pic[MAXN][MAXN];
int n, m;

cin >> n >> m;
for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= m; ++j) cin >> pic[i][j];
```

Similarly, you can define three-dimensional, four-dimensional, and higher-dimensional arrays.
