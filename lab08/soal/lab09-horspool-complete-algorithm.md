# Lab09: Horspool - Complete Algorithm

Diberikan dua buang string `pattern` dan `text`, implementasikan secara lengkap algoritma Horspool untuk masalah string matching.

Anda diminta untuk mengoutputkan **semua** indeks dari `text` yang memuat persis substring `pattern`. Selain itu, Anda juga diminta untuk membandingkan tingkat efisiensi algoritma Horspool dengan algoritma naif dengan meninjau banyaknya shifting yang dilakukan dalam keseluruhan iterasi.

## Input Format

- Baris pertama berisi 2 buah string `text` dan `pattern` masing-masing dipisahkan oleh tanda spasi.

## Constraints

- $1 \le |pattern| \le |text| \le 10000000$.
- Setiap karakter pada string berupa alfabet uppercase and lowercase pada ASCII.

## Output Format

- Jika string $pattern$ muncul sebanyak $k$ kali di $text$, maka baris pertama berisi semua indeks $i_1, i_2, \ldots, i_k$ yang dioutputkan secara terurut naik dan dipisahkan spasi, di mana $pattern$ muncul pada indeks-indeks tersebut pada $text$. Jika ternyata $k = 0$, outputkan `not found` pada baris ini.
- Baris kedua berisi persentase peningkatan performa Horspool dibandingkan algoritma naif. Persentase dibulatkan dalam ketelitian 2 digit di belakang koma.
- Misalkan shifting yang dibutuhkan Horspool dan naif adalah sebesar $H$ dan $N$, secara berturut-turut. Maka, persentase peningkatan performa diukur dengan metrik berikut:

$$\text{Improvement} = \frac{N - H}{N}$$

## Sample Input 0

```
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL JEANCHAUVIN
```

## Sample Output 0

```
20 37
83.33%
```

## Explanation 0

Berikut merupakan aplikasi algoritma Horspool pada instance di atas:

```
Pemeriksaan awal:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
JEANCHAUVIN

Shift #1:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
_______JEANCHAUVIN

Shift #2:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
________JEANCHAUVIN

Shift #3:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
___________________JEANCHAUVIN

Shift #4:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
____________________JEANCHAUVIN

String ditemukan pada indeks ke 20.

Shift #5:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
__________________________JEANCHAUVIN

Shift #6:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
_____________________________________JEANCHAUVIN

String ditemukan pada indeks ke 37.

Shift #7:
SHDOKOSPJANHHAUVIISDJEANCHAUVINPOSLBSJEANCHAUVINSKFL
____________________________________________JEANCHAUVIN
```

Jadi:

- Dengan exhaustive search, diperlukan 42 iterasi.
- Dengan Horspool, diperlukan 7 iterasi.
- Jadi peningkatan efisiensinya sebesar:
