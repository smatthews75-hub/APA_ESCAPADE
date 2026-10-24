# Lab05: Koin Palsu

## Problem Description
Misalkan terdapat $N$ buah koin yang terlihat identik, namun 1 di antaranya adalah koin palsu dengan bobot yang sedikit lebih ringan di antara koin lainnya, katakanlah koin berindeks $X$ dengan $0 \le X < N$. Kita dapat menggunakan timbangan analog untuk membandingkan antar kelompok koin satu dengan yang lain demi mengidentifikasi koin manakah yang merupakan koin palsu. 

Rancanglah algoritma untuk mengatur cara penimbangan koin dengan jumlah penimbangan sesedikit mungkin (di setiap aksi penimbangan, algoritma perlu menetapkan koin mana saja yang diletakkan di masing-masing tangan timbangan) dalam rangka menemukan koin palsu, dengan strategi selalu membagi koin ke dalam dua kelompok saat jumlah koin genap dan membagi ke dalam tiga kelompok saat jumlah koin ganjil.

*(Note: Gambar referensi timbangan analog dihilangkan dalam ekstraksi ini)*

## Input Format
* 1 baris berisi bilangan bulat $N$ dan $X$.

## Constraints
* [Batasan nilai $N$]
* [Batasan nilai $X$]

## Output Format
* Berisi prosedur melakukan penimbangan dengan strategi Decrease and Conquer.
* Lihat contoh Input-Output untuk lebih detailnya.

## Sample Input 0
```text
20 14
```

## Sample Output 0
```text
Penimbangan #1: {kiri: 0..9, kanan: 10..19}. Hasil: Tangan kanan lebih ringan.
Penimbangan #2: {kiri: 10..14, kanan: 15..19}. Hasil: Tangan kiri lebih ringan.
Penimbangan #3: {kiri: 10..11, kanan: 12..13, dipinggirkan: 14}. Hasil: Kedua tangan seimbang.
Ketemu! Koin palsu adalah koin 14. Total penimbangan dilakukan: 3.
```

## Explanation 0
* Pada penimbangan pertama, koin berindeks 0 s.d. 9 diletakkan di tangan kiri timbangan dan koin berindeks 10 s.d. 19 di tangan kanan timbangan. Hasilnya tangan kanan timbangan yang lebih ringan.
* Pada penimbangan kedua, koin berindeks 10 s.d. 14 diletakkan di tangan kiri timbangan dan koin berindeks 15 s.d. 19 di tangan kanan timbangan. Hasilnya tangan kiri timbangan yang lebih ringan.
* Pada penimbangan ketiga, koin berindeks 10 s.d. 11 diletakkan di tangan kiri timbangan, koin berindeks 12 s.d. 13 di tangan kanan timbangan, dan koin berindeks 14 tidak ikut ditimbang. Hasilnya kedua tangan seimbang.
* Ini berarti bahwa koin palsu pastilah koin berindeks 14.