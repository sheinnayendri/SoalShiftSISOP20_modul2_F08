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
Soal ini meminta kami untuk membantu Kiwa membuat program sebagai berikut:
1. (a) Program yang berada di suatu folder khusus, dapat membuat direktori baru setiap 30 detik, dengan nama timestamp ```[YYYY-mm-dd_HH:ii:ss]```.
2. (b) Tiap-tiap folder yang dibuat tadi, diisi dengan 20 gambar yang didownload dari *https://picsum.photos/* setiap 5 detik. Tiap gambar yang berbentuk persegi dengan ukuran ```(t % 1000) + 100``` piksel, di mana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp juga ```[YYYY-mm-dd_HH:ii:ss]```.
3. (c) Kemudian tiap folder yang sudah berisi 20 gambar akan dizip dan folder akan didelete, yang tersisa hanya file zipnya.
4. (d) Program tersebut dapat men-generate sebuah program *killer* yang siap di-execute untuk menterminasi semua operasi program tersebut. Setelah dirun, program itu akan mendelete dirinya sendiri.
5. (e) Program utama dapat dijalankan dalam 2 mode, yaitu **MODE_A** dan **MODE_B**. Di mana di MODE_A, jika program killer dijalankan, semua kegiatan operasi akan langsung terhenti, sedangkan untuk MODE_B, apabila masih ada proses download di masing-masing folder sampai 20 gambar dan sudah ter-zip, maka akan tetap berjalan sampai selesai.
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
1. (a) Membuat 2 direktori di **"/home/user/modul2/"**, yang bernama **"indomie"** dan **"sedaap"** (selang 5 detik).
2. (b) Mengekstrak file **jpg.zip** di direktori **"/home/user/modul2/"**.
3. (c) Memisahkan semua file hasil ekstrak ke dalam direktori **sedaap**, dan semua direktori ke dalam direktori **indomie**.
4. (d) Membuat semua direktori kosong dalam direktori **indomie** menjadi memiliki 2 file kosong masing-masing bernama **coba1.txt** dan setelah 3 detik **coba2.txt**.
#

### Jawab 3a
Dikarenakan tidak boleh memakai fungsi mkdir dari C, maka kami harus menggunakan fungsi ```fork``` dan ```exec``` agar dapat menjalankan beberapa perintah secara bersamaan, dan memanggil fungsi ```mkdir``` melalui exec. Di sini kami menggunakan fungsi ```sleep(5)``` agar dapat memberi delay 5 detik sebelum membuat folder **sedaap**, seperti berikut:
```c
pid_t cid1, cid2, cid3, cid4, cid5, cid6, cid7, cid8;
int status;
cid1 = fork();
if(cid1 < 0) exit(0);
if(cid1 == 0) 
{
    char *argv[] = {"mkdir", "/home/sheinna/modul2/indomie", NULL};
    execv("/bin/mkdir", argv);
}

while((wait(&status)) > 0);
cid2 = fork();
if(cid2 < 0) exit(0);
if(cid2 == 0)
{
    sleep(5);
    char *argv[] = {"mkdir", "/home/sheinna/modul2/sedaap", NULL};
    execv("/bin/mkdir", argv);
}
```
#

### Jawab 3b
Untuk mengekstrak file zip, berarti merupakan suatu perintah baru, sehingga harus melakukan proses fork lagi dan menggunakan perintah ```unzip```, seperti berikut:
```c
while((wait(&status)) > 0);
cid3 = fork();
if(cid3 < 0) exit(0);
if(cid3 == 0)
{
    char *argv[] = {"unzip", "/home/sheinna/modul2/jpg.zip", NULL};
    execv("/usr/bin/unzip", argv);
}
```
#

### Jawab 3c
Untuk memindahkan direktori dari direktori hasil ekstrak ```jpg.zip``` ke dalam direktori **indomie**, sedangkan file ke dalam direktori **sedaap**. Untuk itu, kami menggunakan library ```#include<dirent.h>``` untuk melakukan looping terhadap semua file/folder yang ada di dalam direktori ```/home/sheinna/modul2/jpg```, kemudian dengan fungsi ```d_type``` kami dapat mengetahui tipe dari file/folder yang sedang diakses. ```DT_REG``` berarti tipe file reguler. Jika dikenali sebagai file biasa, maka akan dilakukan fork dan menggunakan exec dapat memindahkan file tersebut ke dalam direktori ```/home/sheinna/modul2/sedaap``` dengan command ```mv```.
```c
while((wait(&status)) > 0);
cid4 = fork();
if(cid4 < 0) exit(0);
if(cid4 == 0)
{
    DIR *dirp;
    struct dirent *entry;
    dirp = opendir("/home/sheinna/modul2/jpg");
    while((entry = readdir(dirp)) != NULL)
    {
        if(entry->d_type == DT_REG)
        {
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0)
            {
                char namafile[105];
                sprintf(namafile, "/home/sheinna/modul2/jpg/%s", entry->d_name);
                char *argv[] = {"mv", namafile, "/home/sheinna/modul2/sedaap", NULL};
                execv("/bin/mv", argv);
            }
        }
    }
}
```

Kemudian, untuk file yang tersisa dalam direktori ```/home/sheinna/modul2/jpg```, pastilah yang merupakan folder, sehingga tinggal memindahkan seluruh file yang ada dalam direktori ```/home/sheinna/modul2/jpg``` ke direktori tujuan yaitu ```/home/sheinna/modul2/indomie```, dengan cara men-copy seluruh isi direktori ```/home/sheinna/modul2/jpg``` ke direktori ```/home/sheinna/modul2/indomie``` dengan command ```rsync```, kemudian untuk menghapus isi dari direktori asalnya, maka digunakan command ```rm -r``` untuk menghapus folder tersebut dan digunakan command ```mkdir``` untuk membuat folder tersebut kembali. Berikut kodenya:
```c
while((wait(&status)) > 0);
cid5 = fork();
if(cid5 < 0) exit(0);
if(cid5 == 0)
{
    char *argv[] = {"rsync", "-r", "/home/sheinna/modul2/jpg/", "/home/sheinna/modul2/indomie", NULL};
    execv("/usr/bin/rsync", argv);
}

while((wait(&status)) > 0);
cid6 = fork();
if(cid6 < 0) exit(0);
if(cid6 == 0)
{
    char *argv[] = {"rm", "-r", "/home/sheinna/modul2/jpg", NULL};
    execv("/bin/rm", argv);
}

while((wait(&status)) > 0);
cid7 = fork();
if(cid7 < 0) exit(0);
if(cid7 == 0)
{
    char *argv[] = {"mkdir", "/home/sheinna/modul2/jpg", NULL};
    execv("/bin/mkdir", argv);
}
```
#

### Jawab 3d
Untuk soal 3d, diminta untuk membuat file kosong dengan nama ```coba1.txt``` di dalam semua folder yang ada dalam direktori ```indomie```, dan kemudian membuat file kosong lagi dengan nama ```coba2.txt``` di dalam semua folder tadi (```/home/sheinna/modul2/jpg/```), kami menggunakan bantuan command ```find . -type d -exec touch {}/coba1.txt\;``` yang berarti mencari tiap direktori dan membuat file baru bernama coba1.txt di dalamnya. Untuk memberikan 3 detik sebelum membuat file ```coba2.txt```, maka dapat menggunakan fungsi ```sleep(3)```. Akan tetapi, karena direktori asalnya sendiri (```/home/sheinna/modul2/indomie/```) juga merupakan sebuah direktori, maka akan di dalam file tersebut akan terbuat juga kedua file ```coba1.txt``` dan ```coba2.txt```. Sehingga perlu ditambahkan command ```rm coba1.txt coba2.txt``` setelah mengeksekusi ```chdir("/home/sheinna/modul2/indomie/")``` agar kedua file .txt dalam direktori tersebut terhapus. Berikut kodenya:
```c
while((wait(&status)) > 0);
cid8 = fork();
if(cid8 < 0) exit(0);
if(cid8 == 0)
{
    chdir("/home/sheinna/modul2/indomie/");
    char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba1.txt", "\;", NULL};
    execv("/usr/bin/find", argv);
}

sleep(3);
while((wait(&status)) > 0);
cid8 = fork();
if(cid8 < 0) exit(0);
if(cid8 == 0)
{
    chdir("/home/sheinna/modul2/indomie/");
    char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba2.txt", "\;", NULL};
    execv("/usr/bin/find", argv);
}

chdir("/home/sheinna/modul2/indomie/");
char *argv[] = {"rm", "coba1.txt", "coba2.txt", NULL};
execv("/bin/rm", argv);
```
#
