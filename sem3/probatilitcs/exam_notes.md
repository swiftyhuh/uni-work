# Exam notes (things the teacher said will be on the final exam)

## Notation: combinations

In these notes **C(n, k) works exactly like Python's `comb(n, k)`**: combinations of n taken k = n! / (k! (n−k)!). First number = the total n, second number = how many you choose k.

- C(5, 3) = `comb(5, 3)` = 10 (choose 3 out of 5)
- The lecture writes the same thing as C_n^k (n at the bottom, k at the top).

## Conditional probability with `comb` — Lab 3, problem 1

Urn: 5 red, 3 blue, 2 green (10 balls). 3 balls drawn **without replacement**.

- A: "at least 1 red ball was extracted"
- B: "all 3 extracted balls have the same colour"

`prob_cond(5000)` estimates P(B | A) (answer options given: approx 0.10, 0.09, 0.08).

### Method
1. P(B | A) = P(B ∩ A) / P(A)
2. B ∩ A = "all 3 extracted balls are red" (same colour AND at least one red ⇒ all red)
   - P(B ∩ A) = C(5, 3) / C(10, 3)
3. P(A) = 1 − P(Ā), where Ā = "no red ball extracted" = all 3 balls come from the 5 non-red balls
   - P(A) = 1 − C(5, 3) / C(10, 3)

### Solution
- C(5, 3) = 10, C(10, 3) = 120
- P(B ∩ A) = 10/120 = 1/12
- P(A) = 1 − 10/120 = 110/120 = 11/12
- P(B | A) = (1/12) / (11/12) = **1/11 ≈ 0.0909** (≈ 0.09)

Check: simulation with 500000 runs gave 0.0906.

```python
from math import comb
p_BA = comb(5, 3) / comb(10, 3)
p_A = 1 - comb(5, 3) / comb(10, 3)
print(p_BA / p_A)      # 0.0909...
```

### Pattern to remember
- "At least one ..." ⇒ use the complement: P(A) = 1 − P("none").
- Same-colour intersection with "at least one red" collapses to the single colour case.
- Without replacement, equally likely outcomes ⇒ ratio of combinations C(total favourable group, picked) / C(total, picked).

## `randint` vs `randrange` — Lab 3, problem 2

- `randint(a, b)` picks from the closed interval **[a, b]** (b included)
- `randrange(a, b)` picks from the half-open interval **[a, b)** (b excluded)

Problem 2 uses `randrange` (die: `randrange(1, 7)` gives 1..6).

## Bernoulli and binomial distributions (teacher's board)

### Bernoulli
X ~ Bern(p), p = probability of success

| X | 0 | 1 |
|---|---|---|
| P | 1 − p | p |

### Binomial
X = number of successes in n Bernoulli trials. X ~ Bino(n, p):
- n = number of trials
- p = probability of success in a single trial

| X | 0 | 1 | 2 | ... | k | ... | n |
|---|---|---|---|---|---|---|---|
| P | | | | | C(n, k) · p^k · (1 − p)^(n−k) | | |

- pmf: P(X = k) = C(n, k) · p^k · (1 − p)^(n−k)  →  Python: `binom.pmf(k, n, p)`
- cdf: P(X ≤ k) = `binom.cdf(k, n, p)`

**Confirmed in the lecture PDF (page 14):** X ~ Bino(n, p) has P(X = k) = C_n^k · p^k · (1 − p)^(n−k), k ∈ {0, ..., n}, with Python `scipy.stats.binom`. C_n^k in the lecture is the same as C(n, k) here. So the board copy `p(k, II)` is p^k, and `(1-p)^p-k` is (1 − p)^(n−k).

Urn link (lecture Example 12, page 14): urn with n1 white and n2 black marbles, n draws **with replacement** ⇒ X1 = number of white ~ Bino(n, p1) with p1 = n1 / (n1 + n2); X2 = number of black ~ Bino(n, p2) with p2 = n2 / (n1 + n2). With r > 2 colours: multinomial, P(X1 = k1, ..., Xr = kr) = n! / (k1! ... kr!) · p1^k1 ... pr^kr.

### Applied: Lab 3, problem 3
Urn with 6 balls "1" and 4 balls "0", 5 draws with replacement, X = sum of the numbers = number of "1" balls:
- X ~ Bino(5, 0.6), values 0..5
- P(1 < X ≤ 4) = P(X ∈ {2, 3, 4}) = `binom.cdf(4, 5, 0.6) − binom.cdf(1, 5, 0.6)` (not `cdf(4) − cdf(2)`: that would drop X = 2)
- 1000 values of X: `binom.rvs(5, 0.6, size=1000)`
