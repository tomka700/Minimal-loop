# Minimal loop to touch every square in an n by n grid

### Results
`? = unproven`
| n  | Length | # (0,1)s | # (1,1)s | # (1,2)s | # Unique Solutions | # Solutions | Area  |
| -- | ------ | -------- | -------- | -------- | ------------------ | ----------- | ----- |
| 0  | 0      | 0        | 0        | 0        | 1                  | 1           | 0     |
| 1  | 0      | 0        | 0        | 0        | 1                  | infinite    | 0     |
| 2  | 0      | 0        | 0        | 0        | 1                  | 1           | 0     |
| 3  | 4      | 4        | 0        | 0        | 1                  | 1           | 1     |
| 4  | 8      | 8        | 0        | 0        | 1                  | 1           | 4     |
| 5  | 12     | 10       | 2        | 0        | 1                  | 8           | 8     |
| 6  | 16     | 12       | 4        | 0        | 1                  | 2           | 14    |
| 7  | 22     | 15       | 5        | 1        | 1                  | 8           | 20.5  |
| 8  | 28     | 20       | 8        | 0        | 2                  | 6           | 28    |
| 9  | 35     | 24       | 11       | 0        | 3                  | 24          | 36.5  |
| 10 | 42     | 26       | 16       | 0        | 18                 | 128         | 46    |
| 11 | 49?    | 26?      | 23?      | 0?       | 24?                | 192?        | 56.5? |
| 12 | 56?    | 24?      | 32?      | 0?       | 3?                 | 12?         | 68?   |
| 13 | 67?    | 32?      | 35?      | 0?       | 15?                | 120?        | 80.5? |
| 14 | 78?    | 38?      | 40?      | 0?       | 150+?              | 1000+?      | 94?   |
| 15 | 87?    | 36?      | 51?      | 0?       | 8?                 | 64?         | 108.5?|
| 16 | 98?    | 38?      | 60?      | 0?       | 92?                | 736?        | 124?  |
| 17 | 109?   | 38?      | 71?      | 0?       |                    |             | 140.5?|
| 18 | 120?   | 36?      | 84?      | 0?       |                    |             | 158?  |
| n $\ge$ 6 ||||||| $\frac{n^2}{2}-4\text{?}$ |
| 0 mod 6 | $\le\frac{n(n+2)}{3}$ | $\le2n$ | $\ge\frac{n(n-4)}{3}$ | 0? ||||
| 1 mod 6 $\ge$ 13 | $\le\frac{n(n+2)+6}{3}$ | $\le2n+6$ | $\ge\frac{n(n-4)-12}{3}$ | 0? ||||
| 2 mod 6 $\ge$ 14 | $\le\frac{n(n+2)+10}{3}$ | $\le2n+10$ | $\ge\frac{n(n-4)-20}{3}$ | 0? ||||
| 3 mod 6 $\ge$ 9 | $\le\frac{n(n+2)+6}{3}$ | $\le2n+6$ | $\ge\frac{n(n-4)-12}{3}$ | 0? ||||
| 4 mod 6 $\ge$ 10 | $\le\frac{n(n+2)+6}{3}$ | $\le2n+6$ | $\ge\frac{n(n-4)-12}{3}$ | 0? ||||
| 5 mod 6 $\ge$ 11 | $\le\frac{n(n+2)+4}{3}$ | $\le2n+4$ | $\ge\frac{n(n-4)-8}{3}$ | 0? ||||

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
