# LogValCpp

[![ci](https://github.com/Blonck/LogValCpp/actions/workflows/ci.yml/badge.svg)](https://github.com/Blonck/LogValCpp/actions/workflows/ci.yml)

## About LogValCpp
Simple and unnecessary LogVal class for C++.

The LogVal class uses logarithms to express large numbers and do math with them.
Basically it is a wrapper around these identities:
```math
\displaylines{
    \log_b(xy) = log_b(x) + log_b(y) \\
    \log_b(a + c) = log_b(a) + log_b(1 + \frac{c}{a})
}
```

This leads to major mathematical inaccuracies but makes it possible to run
algorithms where fixed-width floating point numbers (`double`, `float`) are
too small and arbitrary precision floating point numbers are too slow.

Initially, I used that to implement a FFT method to estimate the density of
states of physical systems. Honestly, I found no other use-case for this class,
but reimplementing it gave me the chance to try out C++20 stuff.
