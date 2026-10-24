# Lab05: Pemangkatan Efisien

Diberikan tiga buah bilangan bulat \(A\), \(B\), dan \(M\). Hitunglah nilai \(A^B \bmod M\) dengan metode *Decrease and Conquer*. Selain nilai akhir perhitungan pangkat, Anda juga perlu mencacah ada berapa kali operasi perkalian yang dilakukan oleh algoritma D&C.

## Input Format

1 baris berisi bilangan bulat \(A\), \(B\), dan \(M\).

## Constraints

- \(1 \le A, M \le 10^9\)
- \(0 \le B \le 10^{18}\)

## Output Format

1 baris berisi bilangan bulat \(A^B \bmod M\) dan \(K\), di mana \(K\) menyatakan berapa kali operasi perkalian yang dilakukan dalam pendekatan D&C.

## Sample Input 0

```text
2 10 1000
```

## Sample Output 0

```text
24 4
```

## Explanation 0

Dengan strategi D&C, sehingga diperoleh:

\[
2^{10} = 2^5 \times 2^5,\qquad
2^5 = 2^2 \times 2^2 \times 2,\qquad
2^2 = 2 \times 2
\]

Hasil modulonya terhadap \(1000\) adalah \(24\). Juga, perhitungannya melibatkan \(4\) kali perkalian.
