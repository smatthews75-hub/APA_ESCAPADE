# Lab09: Urutan Indeks Akhir Mata Kuliah

Dr. Calvin hendak meranking $N$ orang mahasiswanya berdasarkan indeks nilai akhir mata kuliah yang diajarnya. Sistem penilaian Dr. Calvin cukup unik, yaitu memiliki $M$ jenis indeks yang berbeda. Walaupun nilai akhir mata kuliah tiap mahasiswa tetap berada dalam rentang 0 s.d. 100, nilai tersebut akan dikonversi menjadi indeks (dalam praktik normal biasanya berupa A, A-, B+, dst.) Misalkan saat ini Dr. Calvin ingin memiliki $M$ jenis indeks, yaitu $L_0, L_1, \dots, L_{M-1}$. Masing-masing indeks memiliki batas nilai sebagai berikut:

| Range Nilai | Indeks Nilai |
|---|---|
| $0 \le x < b_1$ | $L_0$ |
| $b_1 \le x < b_2$ | $L_1$ |
| $b_2 \le x < b_3$ | $L_2$ |
| … | … |
| $b_{M-2} \le x < b_{M-1}$ | $L_{M-2}$ |
| $b_{M-1} \le x \le 100$ | $L_{M-1}$ |

dengan $b_1, b_2, \dots, b_{M-1}$ merupakan suatu bilangan real yang memenuhi $0 \le b_1 < b_2 < \cdots < b_{M-1} \le 100$, masing-masing menyatakan batas interval dari masing-masing indeks.

Dr. Calvin meminta Anda membuatkan program, karena ia akan mengajukan $Q$ buah pertanyaan yang akan menanyakan berapakah indeks nilai dari mahasiswa ranking ke-$q_i$ untuk $i = 0, 1, \dots, Q-1$. Catatan: ranking dimulai dari ranking 1, yaitu mahasiswa dengan nilai indeks tertinggi, hingga ranking ke $N$, yaitu mahasiswa dengan nilai indeks terendah.

## Input Format

- Baris pertama berisi tiga buah bilangan bulat $N, M, Q$.
- $N$ baris berikutnya berisi bilangan real $r_i$ untuk $i = 0, 1, \dots, N-1$, yaitu nilai akhir dari mahasiswa ke $i$.
- $M-1$ baris berikutnya berisi bilangan real $b_i$ untuk $i = 1, 2, \dots, M-1$, yang menyatakan batas konversi nilai akhir menjadi indeks.
- $M$ baris berikutnya berisi string indeks $L_i$ untuk $i = 0, 1, \dots, M-1$, yang menyatakan label indeks nilai akhir yang ditentukan oleh Dr. Calvin.
- $Q$ baris berikutnya berisi bilangan real $q_i$ untuk $i = 0, 1, \dots, Q-1$, yaitu pertanyaan ke-$i$ dari Dr. Calvin, yaitu "Berapakah indeks nilai akhir dari mahasiswa dengan ranking $q_i$?" untuk $i = 0, 1, \dots, Q-1$.
- Semua bilangan real dalam input selalu ditulis dalam ketelitian 2 digit di belakang koma.

## Constraints

- $1 \le N \le 10^7$
- $1 \le M \le 100$
- $1 \le Q \le 1000$
- $0.00 \le r_i \le 100.00$ untuk $i = 0, 1, \dots, N-1$.
- $0.00 \le b_1 < b_2 < \cdots < b_{M-1} \le 100.00$.
- Indeks nilai $L_i$ untuk $i = 0, 1, \dots, M-1$ berupa string dengan maksimal 3 karakter berisi karakter-karakter ASCII kecuali tanda spasi.
- $1 \le q_i \le N$ untuk $i = 0, 1, \dots, Q-1$.
- Tidak ada jaminan bahwa input $r_i$ dan $q_i$ dalam keadaan terurut.

## Output Format

- $Q$ baris yang berisi string $H_i$ untuk $i = 0, 1, \dots, Q-1$, yang menyatakan jawaban pertanyaan ke $i$, yaitu bahwa mahasiswa ranking ke $q_i$ memiliki indeks nilai $H_i$.

## Sample Input 0

```
8 10 5
91.87
72.22
91.00
87.67
43.76
85.46
75.63
82.00
41.00
46.00
51.00
61.00
71.00
76.00
81.00
86.00
91.00
F
D
C-
C
C+
B-
B
B+
A-
A
1
6
2
3
7
```

## Sample Output 0

```
A
B-
A
A-
B-
```