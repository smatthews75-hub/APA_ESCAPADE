# Lab08: Antrian Klinik Kesehatan

Klinik kesehatan Dr. Calvin pada hari ini menerima banyak pasien, salah satunya adalah Dr. Edwards. Sistem antrian di klinik Dr. Calvin diurutkan pertama-tama berdasarkan usia terlebih dahulu dan kedua berdasarkan waktu kedatangan. Pasien yang usianya lebih tua akan didahulukan untuk dilayani. Jika terdapat lebih dari satu pasien berusia sama, maka yang akan didahulukan adalah yang datang lebih awal.

Dr. Edwards sangat gelisah karena giliran antriannya tidak kunjung datang. Dengan diberikan logbook urutan kehadiran pasien dan dilayaninya pasien yang terdiri dari `[N]` baris, buatlah program untuk dapat memberi tahu Dr. Edwards berapa antrian pasien lagi yang perlu ia menunggu.

### Input Format

* Baris pertama berisi bilangan bulat `[N]`.
* `[N]` baris berikutnya secara terurut menunjukkan kejadian yang terjadi dalam klinik:
* kedatangan pasien, ditulis dalam format `hadir <nama> <umur>`, di mana `<nama>` berupa string alfabet dalam lowercase dan `<umur>` adalah bilangan bulat positif.
* pemanggilan pasien ke ruang dokter, ditulis dalam format `panggil`



### Constraints

* 1 <= K < 500000
* Umur pasien selalu bilangan bulat positif yang tidak lebih dari 100.
* Nama pasien berupa string 1 kata dengan seluruhnya dalam lowercase.
* Dari daftar nama pasien yang hadir, dijamin tidak ada string nama pasien yang terduplikasi dan juga dijamin pasti ada nama `edwards` dalam pasien-pasien yang hadir.
* Dijamin urutan kejadian dalam logbook klinik memenuhi unsur logis, yaitu tidak mungkin pemanggilan pasien dilakukan lebih banyak daripada jumlah pasien yang sudah hadir hingga saat itu.

### Output Format

Sebuah bilangan bulat `[X]`, yang menyatakan bahwa masih ada `[X]` pasien yang harus ditunggu oleh Dr. Edwards hingga kejadian terakhir terjadi dalam logbook.

Jika di akhir logbook ternyata Dr. Edwards sudah dilayani, maka outputkan `0`.

### Sample Input 0

```text
10
hadir bunyan 14
hadir luther 65
hadir owen 23
panggil
hadir knox 25
hadir edwards 23
panggil
hadir zwingli 71
panggil
hadir calvin 54
```

### Sample Output 0

```text
3
```