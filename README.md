# Prime Finder

A compact C++ implementation for finding the **n-th prime number** using a brute-force trial division algorithm.

The algorithm deliberately avoids more sophisticated approaches such as the Sieve of Eratosthenes. Instead, it focuses on reducing the brute-force search space through a few simple mathematical observations:

- Only odd candidates are tested.
- Only previously discovered prime numbers are used as divisors.
- Trial division stops when the square of the divisor exceeds the candidate.
- The divisor index is advanced directly inside the loop control expression.
- Candidate numbers and divisor progression are handled with a compact nested-loop structure.

The result is a deliberately small implementation that keeps the entire prime-generation process visible in only two nested `for` loops.

## Project Structure

```text
.
├── CMakeLists.txt
├── README.md
├── LICENSE
├── .gitignore
└── src/
    └── main.cpp
```

## Overview

The program generates prime numbers sequentially and stores the primes it has already discovered in an array.

The first two primes are initialized directly:

```cpp
int* p = new int[k];
p[0] = 2;
p[1] = 3;
```

Every subsequent candidate is odd, and each candidate is tested only against previously discovered primes.

The core of the algorithm is:

```cpp
for (n = 2; m += 2, n < k; p[n] = m, n++, l = 1)
    for (o = 3; o * o <= m;
         (m % o == 0 ? m += 2, l = 1 : l++),
         o = p[l]);
```

Despite its compact form, the algorithm performs several operations simultaneously.

## Algorithm

### 1. Skip Even Numbers

After initializing `m` to `3`, every new candidate is generated using:

```cpp
m += 2
```

Therefore, even numbers are never tested.

Instead of examining:

```text
4, 5, 6, 7, 8, 9, 10, ...
```

the algorithm only considers:

```text
3, 5, 7, 9, 11, 13, 15, ...
```

This immediately removes half of the candidate space.

### 2. Use Previously Discovered Primes as Divisors

The array `p[]` contains the prime numbers already discovered.

The divisor is obtained using:

```cpp
o = p[l];
```

Consequently, the algorithm does not waste time testing composite divisors.

For example, when testing a candidate, it will try:

```text
3, 5, 7, 11, 13, ...
```

rather than:

```text
3, 4, 5, 6, 7, 8, 9, 10, 11, ...
```

This is still trial division, but the divisor set is restricted to primes.

## 3. Stop at the Square Root

A candidate number only needs to be tested against divisors up to its square root.

Instead of explicitly calculating:

```cpp
sqrt(m)
```

the algorithm uses:

```cpp
o * o <= m
```

This avoids a library square-root operation and expresses the mathematical condition directly.

If:

```text
o² > m
```

then no larger divisor needs to be tested, and the candidate is prime.

The expression also keeps the termination condition directly inside the loop, rather than calculating a separate limit.

## 4. Advancing the Divisor Index

One of the more compact parts of the algorithm is:

```cpp
o = p[l]
```

combined with:

```cpp
m % o == 0 ? m += 2, l = 1 : l++
```

If the candidate is not divisible by the current prime divisor, the divisor index advances:

```cpp
l++
```

and the next previously discovered prime is selected.

If the candidate is divisible by the current divisor, it is composite. The candidate is immediately advanced to the next odd number:

```cpp
m += 2
```

and the divisor index is reset:

```cpp
l = 1
```

The next candidate therefore begins its trial division again from the smallest prime divisor.

This allows the entire candidate-generation and divisor-progression mechanism to remain inside the `for` loop expressions.

## Core Idea

Conceptually, the algorithm behaves like this:

```text
Generate odd candidate
        │
        ▼
Try the next known prime divisor
        │
        ├── divisible ──► discard candidate
        │                  generate next odd candidate
        │
        └── not divisible
                │
                ▼
          Try next prime
                │
                ▼
          divisor² > candidate?
                │
                ├── no ──► continue
                │
                └── yes ──► candidate is prime
```

The implementation compresses this entire flow into the update expressions of two nested loops.

## Complexity

This is a brute-force trial division algorithm and is **not intended to compete with highly optimized prime-generation algorithms** such as the Sieve of Eratosthenes or segmented sieves.

For each candidate, the algorithm may perform trial divisions by previously discovered primes up to approximately:

$$
\sqrt{m}
$$

The number of candidate values is also reduced by skipping all even numbers.

The practical performance therefore depends heavily on the requested value of `k`.

## Why Not Use a Sieve?

A sieve would be substantially faster for generating large ranges of prime numbers.

That is not the purpose of this implementation.

The goal is to explore how much structure can be extracted from a simple brute-force approach while keeping the implementation extremely compact.

The algorithm deliberately keeps the underlying mechanism visible:

```text
candidate → divisor → test → advance → repeat
```

Rather than replacing the search with a fundamentally different algorithm.

## Example

Running the program:

```text
Input nth prime: 1000000
```

produces the millionth prime:

```text
1000000. prime is: 15485863
```

The program also reports the elapsed execution time:

```text
Time elapsed 0.XXX seconds
```

Actual execution time depends on the compiler, optimization settings, processor, and operating system.

## Implementation Notes

The program uses a dynamically allocated integer array to store previously discovered primes:

```cpp
int* p = new int[k];
```

The array is released after each calculation:

```cpp
delete[] p;
```

The program then returns to the input prompt and allows another value of `k` to be tested.

The `goto INPUT` construct is intentionally retained as part of the compact original implementation. It allows the complete allocation → calculation → output → cleanup cycle to repeat without wrapping the entire program in another loop.

## Limitations

- Uses brute-force trial division.
- Requires memory proportional to the number of requested primes.
- Uses `int` for the stored prime values, limiting the representable prime range.
- The multiplication `o * o` can overflow for sufficiently large integer values.
- The algorithm is primarily intended as an exploration of compact brute-force computation rather than a production-grade prime-generation library.

## License

See [LICENSE](LICENSE) for details.
