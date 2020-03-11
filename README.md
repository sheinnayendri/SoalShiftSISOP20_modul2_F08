# SoalShiftSISOP20_modul2_F08
Soal Shift Sistem Operasi 2020
#
1. Sheinna Yendri (05111840000038)
2. Muhammad Rafi Yudhistira (05111840000115)
#
1. [Soal1](#soal1)
2. [Soal2](#soal2)
3. [Soal3](#soal3)
#

## Soal1

#

### Jawab 1a

#

### Jawab 1b

#

### Jawab 1c

#

###  Jawab 1d

#

### Jawab 1e

#

## Soal2

#

### Jawab 2a

#

### Jawab 2b

#

### Jawab 2c

#

### Jawab 2d

#

### Jawab 2e

#

## Soal3
Soal ini meminta kami untuk membantu Jaya dalam membuat tugas yang berbeda tapi harus dikerjakan secara bersamaan (*multiprocessing*):
a. Membuat 2 direktori di **"/home/user/modul2/"**, yang bernama **"indomie"** dan **"sedaap"** (selang 5 detik).
b. Mengekstrak file **jpg.zip** di direktori **"/home/user/modul2/"**.
c. Memisahkan semua file hasil ekstrak ke dalam direktori **sedaap**, dan semua direktori ke dalam direktori **indomie**.
d. Membuat semua direktori kosong dalam direktori **indomie** menjadi memiliki 2 file kosong masing-masing bernama **coba1.txt** dan setelah 3 detik **coba2.txt**.
#

### Jawab 3a
Dikarenakan tidak boleh memakai fungsi mkdir dari C, maka kami harus menggunakan fungsi **fork** dan **exec** agar dapat menjalankan beberapa perintah secara bersamaan. Di sini kami menggunakan fungsi sleep(5) agar dapat memberi delay 5 detik sebelum membuat folder **sedaap**.
#

### Jawab 3b
Untuk mengekstrak file zip, berarti merupakan suatu perintah baru, sehingga harus melakukan proses fork lagi dan menggunakan perintah **unzip**.
#

### Jawab 3c

#

### Jawab 3d

#
