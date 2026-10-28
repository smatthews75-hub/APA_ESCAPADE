# Lab09: Horspool - Shift Table Generation

Diberikan dua buang string `pattern` dan `text`, buatlah algoritma prekomputasi untuk menghasilkan tabel shifting dalam algoritma Horspool.

Dalam tugas ini, Anda akan diberikan $Q$ buah query yang menanyakan besarnya shifting yang perlu dilakukan ketika menemukan mismatched character $q_i$ untuk $i = 0, 1, \dots, Q-1$.

## Input Format

- Baris pertama berisi 2 buah string `text` dan `pattern` serta bilangan bulat $Q$, masing-masing dipisahkan oleh tanda spasi.
- $Q$ baris berikutnya berisi sebuah karakter $q_i$ untuk $i = 0, 1, \dots, Q-1$, yang menyatakan query ke-$i$, yang menanyakan berapakah shift yang diperlukan ketika ditemukan mismatched character $q_i$.

## Constraints

- $1 \le |pattern| \le |text| \le 10^7$ (the exponent is my reading of the glyphs in the HTML, so please check it against the original page).
- $1 \le Q \le 50$.
- $q_i$ berupa satu buah karakter untuk $i = 0, 1, \dots, Q-1$; dijamin merupakan sebuah karakter yang muncul di string `text`. Dengan kata lain $q_i \in text$.
- Semua karakter pada string berupa karakter alfanumerik (lowercase, uppercase, ataupun angka).

## Output Format

- $Q$ baris berisi bilangan bulat $s_i$ untuk $i = 0, 1, \dots, Q-1$ yang menandakan jawaban atas pertanyaan ke-$i$, yaitu bahwa ketika ditemukan karakter mismatched berupa $q_i$, maka shifting yang diperlukan adalah sebesar $s_i$.

## Sample Input 0

```
ApakahIniMaksudnya Analisis
5
s
l
i
A
a
```

## Sample Output 0

```
2
4
1
7
5
```