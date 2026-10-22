# Lab08: TopDownParentalDominance - Min Heap

Implementasikan prosedur `TopDownParentalDominance(i)`, yaitu memastikan kualitas Parental Dominance tercapai pada titik berindeks $i$ pada sebuah Min Heap, yaitu suatu heap dengan definisi 'parental dominance' sebagai berikut: value dari suatu parent haruslah yang paling kecil di antara semua anak-anaknya.

*Catatan: Indeks heap dimulai dari 1.*

### Input Format

* Baris pertama berisi bilangan bulat $N$ dan $i$, menandadakan panjang heap dan indeks $i$ yang akan dijalankan prosedur `TopDownParentalDominance(i)`.
* Baris kedua berisi $N$ bilangan bulat terpisahkan oleh spasi (dijamin semuanya berbeda) $A_i$ yang menandakan elemen-elemen heap sebelum prosedur `TopDownParentalDominance(i)` dijalankan.

### Constraints

* $1 \le N \le 10^5$
* $1 \le i \le N$
* Dijamin bahwa semua nilai-nilai $A_i$ untuk $1 \le i \le N$ bersifat unik.

### Output Format

Satu baris berisi $N$ bilangan bulat terpisahkan oleh spasi $A_i$ yang menandakan elemen-elemen heap **setelah** prosedur `TopDownParentalDominance(i)` dijalankan.

### Sample Input 0
```text
8 2
2 15 3 8 7 6 9 10
```

### Sample Output 0
```text
2 7 3 8 15 6 9 10
```