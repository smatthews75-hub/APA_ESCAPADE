# Lab08: BottomUpParentalDominance - Min Heap

Implementasikan prosedur `BottomUpParentalDominance(i)`, yaitu memastikan kualitas Parental Dominance tercapai pada titik berindeks $i$ pada sebuah Min Heap, yaitu suatu heap dengan definisi 'parental dominance' sebagai berikut: value dari suatu parent haruslah yang paling kecil di antara semua anak-anaknya.

*Catatan: Indeks heap dimulai dari 1.*

## Input Format

* Baris pertama berisi bilangan bulat $N$ dan $i$, menandadakan panjang heap dan indeks $i$ yang akan dijalankan prosedur `BottomUpParentalDominance(i)`.
* Baris kedua berisi $N$ bilangan bulat terpisahkan oleh spasi (dijamin semuanya berbeda) $A$ yang menandakan elemen-elemen heap sebelum prosedur `BottomUpParentalDominance(i)` dijalankan.

## Constraints

* $1 \leq i \leq N \leq 100$ *(Note: Exact bounds were encoded in SVG images, standard lab constraints assumed)*
* Nilai-nilai elemen $A$ berada dalam rentang bilangan bulat standar (misal: $-10^5 \leq A_i \leq 10^5$).
* Dijamin bahwa semua nilai-nilai $A$ bersifat unik.

## Output Format

Satu baris berisi $N$ bilangan bulat terpisahkan oleh spasi $A$ yang menandakan elemen-elemen heap **setelah** prosedur `BottomUpParentalDominance(i)` dijalankan.

## Sample Input 0
```text
8 7
2 5 3 8 7 6 1 10
```

## Sample Output 0
```text
1 5 2 8 7 6 3 10
```