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
Untuk membuat folder dengan timestamp ```[YYYY-mm-dd_HH:ii:ss]``` dapat menggunakan fungsi ```strftime``` dari C dan menggunakan ```fork``` serta ```exec``` untuk memanggil command ```mkdir```. Agar program berjalan setiap 30 detik, maka digunakan daemon dan diberi selang 30 detik dengan ```sleep(30)```. Berikut kodenya:
```c
pid_t cid, cid2, cid3, cid4;
time_t t1 = time(NULL);
struct tm* p1 = localtime(&t1);
strftime(curtime, 30, "%Y-%m-%d_%H:%M:%S", p1);

cid = fork();
if(cid < 0) exit(0);
if(cid == 0)
{
    char *ag[] = {"mkdir", curtime, NULL};
    execv("/bin/mkdir", ag);
}
sleep(30);
```
#

### Jawab 2b
Untuk mendownload gambar untuk tiap folder, digunakan fungsi ```fork``` dan ```exec``` untuk memanggil fungsi ```wget```, dengan format untuk mendapatkan timestamp sama seperti di soal 2a. Sebelum menjalankan perintah tersebut, akan memanggil fungsi ```chdir(curtime)``` terlebih dahulu, agar dapat masuk ke folder tersebut. Karena membutuhkan download 20 gambar, maka digunakan loop ```for``` dengan iterasi 20 kali. Berikut kodenya:
```c
chdir(curtime);
for(i = 0; i < 20; i++)
{
    time_t t2 = time(NULL);
    struct tm* p2 = localtime(&t2);
    strftime(curtime2, 30, "%Y-%m-%d_%H:%M:%S", p2);
    sprintf(link, "https://picsum.photos/%ld", (t2 % 1000) + 100);

    cid3 = fork();
    if(cid3 < 0) exit(0);
    if(cid3 == 0)
    {
        char *ag[] = {"wget", link, "-O", curtime2, "-o", "/dev/null", NULL};
        execv("/usr/bin/wget", ag);
    }
    sleep(5);
}
```
#

### Jawab 2c
Setelah keluar dari loop (sudah mendownload 20 gambar), maka perlu melakukan zip folder tadi dengan nama yang sama yaitu nama folder tadi (curtime). Untuk mendapatkan nama folder, digunakan fungsi ```strcpy(curtime3, curtime)``` yang berarti variable curtime3 akan berisi sama dengan curtime (nama folder), kemudian dilanjutkan dengan fungsi ```strcat(curtime3, ".zip")``` agar menambahkan ekstensi ```.zip```. Untuk memanggil fungsi ```zip```, harus menggunakan ```fork``` dan ```exec``` lagi. Sebelumnya, maka harus berpindah ke direktori parent (keluar), karena akan dilakukan zip, dengan command ```chdir("..")```. Dan kemudian command ```rm -r``` agar folder awalnya terhapus. Berikut kodenya:
```c
while(wait(&stat2) > 0);
chdir("..");
strcpy(curtime3, curtime);
strcat(curtime3, ".zip");

cid4 = fork();
if(cid4 < 0) exit(0);
if(cid4 == 0)
{
    char *ag[] = {"zip", "-r", curtime3, curtime, NULL};
    execv("/usr/bin/zip", ag);
}
while(wait(&stat3) > 0);

char *ag[] = {"rm", "-r", curtime, NULL};
execv("/bin/rm", ag);
```
#

### Jawab 2d
Program killer yang kami buat dalam bentuk bash, di mana dituliskan dari program C dengan command ```fopen``` terlebih dahulu untuk membuat file baru yang akan dituliskan, dengan command ```w```, dan command ```fprintf``` untuk menuliskan source code killer. Kemudian memanggil fungsi ```exec``` dan ```fork``` lagi untuk mengganti hak akses file tersebut menggunakan command ```chmod u+x kill.sh```, yang berarti user dapat mengeksekusi file kill.sh tersebut. Berikut kodenya:
```c
FILE* kill;
kill = fopen("kill.sh", "w");
fprintf(kill, "#!/bin/bash\nkill %d\necho \'Killed program.\'\nrm \"$0\"", getpid());
fclose(kill);
pid_t cid;
cid = fork();
if(cid < 0) exit(0);
if(cid = 0)
{
    char *ag[] = {"chmod", "u+x", "kill.sh", NULL};
    execv("/bin/chmod", ag);
}
while(wait(&stat) > 0);
```
#

### Jawab 2e
Untuk menerima argumen, digunakan parameter di fungsi main, dalam bentuk argc (untuk mengetahui berapa banyak argumen), dan array argv yang berisi argumen yang dipassing. Jika argumen yang diinginkan berupa ```-a``` dan ```-b```, artinya huruf a dan b berada pada array argv\[1]\[1] karena di argumen kedua dan karakter kedua (*zero indexing*). Kemudian untuk membedakan mode a, di mana program langsung berhenti tanpa menyelesaikan pekerjaannya dulu, maka diberi command ```if``` di dalam loop pembuatan folder dalam ```while(1)```, agar jika mode yang dipassing adalah a, dapat langsung memberikan sinyal hangup dengan ```SIGHUP``` dengan bantuan fungsi ```prctl```. Berikut kodenya:
```c
int main(int argc, char* argv[])
{
    if(argc != 2 || (argv[1][1] != 'a' && argv[1][1] != 'b')) 
    {
        printf("Mode hanya ada -a atau -b\n");
        exit(0);
    }
    ...
    while(1)
    {
        ...
        if(argv[1][1] == 'a') prctl(PR_SET_PDEATHSIG, SIGHUP);
        ...
    }
    ...
}
```
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
pid_t cid1, cid2, cid3, cid4, cid5, cid6, cid7, cid8, cid9;
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

while((wait(&status)) > 0);
cid9 = fork();
if(cid9 < 0) exit(0);
if(cid9 == 0)
{
    chdir("/home/sheinna/modul2/indomie/");
    char *argv[] = {"rm", "coba1.txt", "coba2.txt", NULL};
    execv("/bin/rm", argv);
}
```
#
