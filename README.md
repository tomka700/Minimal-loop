# Minimal loop to touch every square in an n by n grid

### Results
`? = unproven`
| n  | Length | # (0,1)s | # (1,1)s | # (1,2)s | # Unique Solutions | # Solutions |
| -- | ------ | -------- | -------- | -------- | ------------------ | ----------- |
| 0  | 0      | 0        | 0        | 0        | 1                  | 1           |
| 1  | 0      | 0        | 0        | 0        | 1                  | infinite    |
| 2  | 0      | 0        | 0        | 0        | 1                  | 1           |
| 3  | 4      | 4        | 0        | 0        | 1                  | 1           |
| 4  | 8      | 8        | 0        | 0        | 1                  | 1           |
| 5  | 12     | 10       | 2        | 0        | 1                  | 8           |
| 6  | 16     | 12       | 4        | 0        | 1                  | 2           |
| 7  | 22     | 15       | 5        | 1        | 1                  | 8           |
| 8  | 28     | 20       | 8        | 0        | 2                  | 6           |
| 9  | 35     | 24       | 11       | 0        | 3                  | 24          |
| 10 | 42     | 26       | 16       | 0        | 18                 | 128         |
| 11 | 49?    | 26?      | 23?      | 0?       | 24?                | 192?        |
| 12 | 56?    | 24?      | 32?      | 0?       | 3?                 | 12?         |
| 13 | 67?    | 32?      | 35?      | 0?       | 7?                 | 56?         |
| 14 | 78?    | 38?      | 40?      | 0?       | 69?                | 552?        |
| 15 | 86?    | 36?      | 51?      | 0?       | 8?                 | 64?         |
| 16 | 98?    | 38?      | 60?      | 0?       | 84?                | 672?        |
| 17 |        |          |          | 0?       |                    |             |
| 18 | 132?   | 36?      | 84?      | 0?       | 8?                 | 40?         |
||||||||
| 24 | 206?   | 48?      | 158?     | 0?       | 23?                | 144?        |
||||||||
| 0 mod 6 | $\frac{n(n+2)}{3}\text{?}$ | 2n? | $\frac{n(n-4)}{3}\text{?}$ | 0? | $\left(4^{\frac{n}{6}-2}+2^{\frac{n}{6}-2}\right) + \binom{\frac{n}{6}-1}{\lfloor\frac{\frac{n}{6}-1}{2}\rfloor}\text{?}$ | $\frac{4^{\frac{n}{6}}}{2}+2^{\frac{n}{6}}\text{?}$ |

---

### Running
- Set `n` and `MAX_LEN`
```ps
g++ -std=c++23 -O3 -march=native -flto loop.cpp -o loop
```

---

### Notes
- Chebyshev distance is used as it is equivalent in the case of only using `(1,1)` and `(0,1)` moves and it is faster
  - `n = 5` is a special case, where false positives would arise, they are filtered out manually
  - `n = 7` is the only known case, where a `(1,2)` move is necessary
- All moves of optimal solutions for `5 < n < 9` are zero waste, this is enforced as a general rule, see `added.count()`
- `n = 8, 9` are good for testing as they run in human time

---

### Todo
- parallelization
- calc `MAX_LEN` using an upper bound
- better exit check
- prune by symmetry somehow?
