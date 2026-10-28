# Lab09: Kode Genetik Alien

Di sebuah planet di galaksi Calvinmeda, terdapat kehidupan di mana makhluk hidupnya memiliki struktur kode genetika yang berbeda dengan makhluk hidup di bumi, yaitu memiliki $k$ buah jenis basa berbeda yang dapat menyusun kode genetik tersebut.

Dr. Calvin sedang meneliti struktur genetika makhluk hidup di planet tersebut. Untuk membantu tugas berat Dr. Calvin ini, Anda diminta untuk membuat algoritma pencocokan subsequence. Diberikan dua buang string `pattern` dan `text` yang merupakan sebuah genome sequence, Anda diminta untuk menemukan posisi mana saja `pattern` muncul dalam string `text`.

Selain itu, setiap substring kode genetik juga dapat dikodekan menjadi bentuk angka dalam sistem bilangan basis $k$, sesuai arahan Algoritma Rabin-Karp. Dengan mengasosiasikan setiap basa sesuai urutan leksikografis dengan bilangan $\{0, 1, \ldots, k - 1\}$, Anda dapat membuat fungsi hash untuk menerjemahkan substring menjadi kode bilangan.

Selain diminta untuk mengoutputkan posisi substring `pattern`, Anda juga diminta mengoutputkan kode dari semua substring yang ditelusuri oleh algoritma. Gunakan bilangan prima $1000000007$ untuk melakukan hashing.

## Input Format

- Baris pertama berupa bilangan bulat positif $k$.
- Baris kedua berisi $k$ buah karakter alfabet uppercase dipisahkan oleh spasi, yang menandakan simbol basa penyusun kode genetik, ditulis dalam urutan leksikografis.
- Baris ketiga berisi 2 buah string `text` dan `pattern` dipisahkan oleh tanda spasi.

## Constraints

- $2 \le k \le 9$.
- $1 \le |pattern| \le |text| \le 10000000$.
- Karakter basa penyusun kode genetik selalu merupakan karakter uppercase ASCII.
- `text` dan `pattern` selalu tersusun oleh karakter-karakter yang muncul pada baris kedua input.

## Output Format

- Jika string $pattern$ muncul sebanyak $K$ kali di $text$, maka baris pertama berisi semua indeks $i_1, i_2, \ldots, i_K$ yang dioutputkan secara terurut naik dan dipisahkan spasi, di mana $pattern$ muncul pada indeks-indeks tersebut pada $text$. Jika ternyata $K = 0$, outputkan `not found` pada baris ini.
- $|text| - |pattern| + 1$ baris berikutnya berisi bilangan bulat kode basa penyusun dari substring yang dijelajahi dalam algoritma pencocokan, dinyatakan dalam modulo $1000000007$.

## Sample Input 0

```
4
A C G T
AGTCGTTAGAT CGTTA
```

## Sample Output 0

```
3
182
731
879
444
754
968
803
```
