# Lab08: Calvin Ambassador

Dr. Calvin sedang mencari sepasang mahasiswa dan mahasiswi untuk dijadikan ambassador bagi universitas yang dikelolanya. Dia sedang mempertimbangkan $N$ mahasiswa dan $M$ mahasiswi untuk dipilih seorang mahasiswa dan seorang mahasiswi sehingga tinggi badan mereka semirip mungkin. Bantulah Dr. Calvin untuk menemukan pasangan yang terbaik untuk menjadi ambassador. Jika terdapat banyak pilihan pasangan, pilihlah pasangan yang mengutamakan urutan leksikografis nama mahasiswa, kemudian nama mahasiswi.

## Input Format

* Baris pertama berisi 2 buah bilangan bulat (mewakili $N$ dan $M$) yang dipisahkan spasi.


* Baris-baris berikutnya berisi string yang berisi nama mahasiswa dan bilangan real tinggi badannya; dipisahkan spasi.


* Baris-baris selanjutnya berisi string yang berisi nama mahasiswi dan bilangan real tinggi badannya; dipisahkan spasi.



## Constraints

* Nama mahasiswa/mahasiswi dijamin selalu berupa string 1 kata dengan panjang maksimal 10 karakter dan selalu dalam lowercase.


* Dijamin bahwa semua keseluruhan nama mahasiswa dan mahasiswi selalu unik.


* Tinggi badan mahasiswa/mahasiswi dijamin selalu berupa bilangan real dalam suatu rentang nilai dalam ketelitian 2 digit di belakang koma. *(Catatan: Nilai batasan matematis spesifik direpresentasikan sebagai SVG dalam sumber asli)*.



## Output Format

* 1 baris berisi nama mahasiswa dan mahasiswi yang terpilih sebagai Calvin Ambassador, dipisahkan oleh spasi.


* Jika terdapat banyak solusi, pilihlah pasangan dengan nama mahasiswa paling awal secara abjad.


* Jika masih terdapat banyak solusi, pilihlah kembali yang nama mahasiswinya paling awal secara abjad.



## Sample Input 0

```text
5 4
erdos 185.32
graham 153.91
szemeredy 171.03
tutte 164.28
seymour 182.01
noether 161.42
chudnovsky 175.82
fanchung 155.90
szekeres 161.51

```

(Sumber:)

## Sample Output 0

```text
graham fanchung

```