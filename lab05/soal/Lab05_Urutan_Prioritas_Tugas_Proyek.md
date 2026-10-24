# Lab05: Urutan Prioritas Tugas Proyek

## Problem Statement

Dr. Calvin adalah seorang manajer dari sebuah megaproyek pembangunan universitas di BSD. Jika didetailkan, terdapat \(N\) buah pekerjaan yang perlu diselesaikan untuk merampungkan megaproyek tersebut. Selain itu, Dr. Calvin juga sudah menelaah pekerjaan-pekerjaan tersebut dan didapati bahwa terdapat \(M\) buah restriksi prasyarat pengerjaan masing-masing pekerjaan.

Untuk \(i = 0, 1, \ldots, M-1\), restriksi ke-\(i\) mengatakan bahwa pekerjaan ke-\(A_i\) harus dilakukan terlebih dahulu agar pekerjaan \(B_i\) dapat dilakukan dengan \(0 \le A_i, B_i \le N-1\). Dr. Calvin perlu untuk mengurutkan semua pekerjaan tersebut secara linear agar setiap pekerjaan dapat dikerjakan mengikuti semua restriksi yang tersedia.

Jika terdapat lebih dari 1 solusi, maka Anda diminta untuk mengoutputkan solusi dengan urutan leksikografis yang paling awal.

## Input Format

- Baris pertama berisi bilangan bulat \(N\) dan \(M\).
- \(M\) baris berikutnya berisi dua bilangan bulat \(A_i\) dan \(B_i\), yang menunjukkan bahwa pekerjaan ke-\(A_i\) harus dilakukan terlebih dahulu agar pekerjaan \(B_i\) dapat dilakukan; untuk \(i = 1, 2, \ldots, N\).

## Constraints

- \(1 \le N \le 1000\)
- \(0 \le M \le \frac{N(N-1)}{2}\)
- \(0 \le A_i, B_i \le N-1\)
- Dijamin tidak ada sisi berganda (*multiple edges*) ataupun loop dalam baris yang diberikan.

## Output Format

Sebuah urutan indeks pekerjaan yang memenuhi batasan prasyarat yang telah diberikan. Jika urutan yang demikian tidak dapat ditemukan, outputkan `MUSTAHIL` (tanpa tanda kutip).

Jika terdapat lebih dari 1 solusi, maka Anda diminta untuk mengoutputkan solusi dengan urutan leksikografis yang paling awal.

## Sample Input 0

```text
5 5
0 2
1 2
2 3
2 4
3 4
```

## Sample Output 0

```text
0 1 2 3 4
```

## Explanation 0

Urutan prioritas mengikuti bentuk seperti berikut:

Dari semua solusi yang ada, yang memiliki urutan leksikografis pertama adalah `0, 1, 2, 3, 4`.

## Sample Input 1

```text
3 3
0 1
1 2
2 0
```

## Sample Output 1

```text
MUSTAHIL
```

## Explanation 1

Relasi prasyarat membentuk siklus, sehingga urutan macam apapun akan selalu menyalahi aturan prasyarat.

---

## Catatan ekstraksi

Teks di atas mempertahankan isi berbahasa Indonesia dari HTML dan menuliskan rumus sebagai teks matematika. Beberapa bagian rumus pada HTML tampak salah tempat atau tidak konsisten: pada kalimat soal, batas \(0 \le A_i, B_i \le N-1\) muncul setelah frasa “dapat dilakukan dengan”; rentang indeks di Input Format dirender sebagai \(i = 1, 2, \ldots, N\); dan Constraints menampilkan rumus rentang itu diikuti simbol \(M\) yang terpisah. Bagian-bagian tersebut tidak dapat dipastikan lebih jauh dari HTML yang diunggah, jadi tidak dikoreksi diam-diam.

Explanation 0 juga merujuk pada sebuah gambar, tetapi berkas gambar tersebut tidak tersedia bersama HTML yang diunggah.
