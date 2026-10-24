# Lab05: Rata-Rata IPK

## Deskripsi

Mahasiswa IBDA terdiri dari $N$ orang yang masing-masing memiliki IPK sebesar $a_0, a_1, \ldots, a_{N-1}$. Sebuah tim yang beranggotakan mahasiswa IBDA perlu dibuat untuk menjadi pengurus inti organisasi Himpunan Mahasiswa IBDA. Tim yang terbentuk diharapkan memiliki rata-rata IPK **tepat** sebesar $R$, dengan suatu $R$ bilangan real positif. Bagaimana memilih anggota tim yang terbaik? Jika seandainya tidak memungkinkan untuk menjadikan tim yang rata-ratanya persis $R$, upayakan agar rata-ratanya sedekat mungkin dengan $R$.

## Input Format

- Baris pertama berisi bilangan bulat $N$.
- Baris kedua berisi bilangan real $R$.
- Baris ketiga berisi $N$ buah bilangan real positif $a_0, a_1, \ldots, a_{N-1}$.

## Constraints

- $1 \le N \le 20$.
- $0.00 \le a_0, a_1, \ldots, a_{N-1}, R \le 4.00$.

## Output Format

$k$ buah indeks $b_0, b_1, \ldots, b_{k-1}$ yang menyatakan bahwa rata-rata IPK mahasiswa dengan indeks $b_0, b_1, \ldots, b_{k-1}$ adalah yang paling dekat dengan nilai $R$. $k$ indeks dioutputkan secara terurut naik dan dipisahkan spasi. Jika terdapat lebih dari 1 solusi, outputkan subhimpunan dengan ukuran paling kecil dan urutan indeks leksikografis pertama.

## Sample Input 0

```text
4
3.000000
2.700000 3.690000 3.270000 2.610000
```

## Sample Output 0

```text
0 1 3
```

## Explanation 0

Setiap subhimpunan mahasiswa dalam instance di atas dapat dikaitkan dengan string biner dengan panjang $4$, sebagai berikut.

| Kemungkinan | Subhimpunan | Kode Biner | IPK anggota subhimpunan | Rata-rata |
|---:|---|---|---|---:|
| 1 | $\{a_0\}$ | `1000` | 2,7 | 2,7 |
| 2 | $\{a_1\}$ | `0100` | 3,69 | 3,69 |
| 3 | $\{a_2\}$ | `0010` | 3,27 | 3,27 |
| 4 | $\{a_3\}$ | `0001` | 2,61 | 2,61 |
| 5 | $\{a_0,a_1\}$ | `1100` | 2,7; 3,69 | 3,195 |
| 6 | $\{a_0,a_2\}$ | `1010` | 2,7; 3,27 | 2,985 |
| 7 | $\{a_0,a_3\}$ | `1001` | 2,7; 2,61 | 2,655 |
| 8 | $\{a_1,a_2\}$ | `0110` | 3,69; 3,27 | 3,48 |
| 9 | $\{a_1,a_3\}$ | `0101` | 3,69; 2,61 | 3,15 |
| 10 | $\{a_2,a_3\}$ | `0011` | 3,27; 2,61 | 2,94 |
| 11 | $\{a_0,a_1,a_2\}$ | `1110` | 2,7; 3,69; 3,27 | 3,22 |
| 12 | $\{a_0,a_2,a_3\}$ | `1011` | 2,7; 3,27; 2,61 | 2,86 |
| 13 | $\{a_0,a_1,a_3\}$ | `1101` | 2,7; 3,69; 2,61 | 3 |
| 14 | $\{a_0,a_1,a_2\}$ | `1110` | 2,7; 3,69; 3,27 | 3,22 |
| 15 | $\{a_0,a_1,a_2,a_3\}$ | `1111` | 2,7; 3,69; 3,27; 2,61 | 3,0675 |

Perhatikan bahwa tim yang sebaiknya dipilih adalah mahasiswa dengan urutan $\{0,1,3\}$ karena memiliki rata-rata yang persis sebesar $3.00$.
