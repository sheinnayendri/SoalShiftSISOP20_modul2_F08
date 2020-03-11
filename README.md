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
Dikarenakan tidak boleh memakai fungsi mkdir dari C, maka kami harus menggunakan fungsi ```fork``` dan ```exec``` agar dapat menjalankan beberapa perintah secara bersamaan, dan memanggil fungsi ```mkdir``` melalui exec. Di sini kami menggunakan fungsi ```sleep(5)``` agar dapat memberi delay 5 detik sebelum membuat folder **sedaap**, seperti berikut:
`c
pid_t cid4;
cid4 = fork();
if(cid4 < 0) exit(0);
if(cid4 == 0)
{
  char *argv[] = {"mkdir", "/home/sheinna/modul2/indomie", NULL};
  execv("/bin/mkdir", argv);
}
else
{
  sleep(5);
  char *argv[] = {"mkdir", "/home/sheinna/modul2/sedaap", NULL};
  execv("/bin/mkdir", argv);
}
`
#

### Jawab 3b
Untuk mengekstrak file zip, berarti merupakan suatu perintah baru, sehingga harus melakukan proses fork lagi dan menggunakan perintah ```unzip```, seperti berikut:
`c
while(wait(&status) > 0);
char *argv[] = {"unzip", "/home/sheinna/modul2/jpg.zip", NULL};
execv("/usr/bin/unzip", argv);
`
#

### Jawab 3c
Unutk memindahkan direktori dari direktori hasil ekstrak ```jpg.zip``` ke dalam direktori **indomie**, sedangkan file ke dalam direktori **sedaap**, digunakan perintah ```mv``` untuk memindahkan, dan *wildcard* untuk mengambil tipe folder dengan format ```/home/sheinna/modul2/jpg/*/``` yang berarti mengambil semua direktori yang ada dari direktori jpg. Kemudian memindahkannya ke direktori tujuan yaitu ```/home/sheinna/modul2/indomie```, seperti berikut:
`c
char *argv[] = {"mv", "/home/sheinna/modul2/jpg/*/", "/home/sheinna/modul2/indomie", NULL};
execv("/bin/mv", argv);
`

Kemudian, untuk file yang tersisa dalam direktori jpg, pastilah yang merupakan file, sehingga tinggal memindahkan seluruh file yang ada dalam direktori jpg ke tujuan yaitu ```/home/sheinna/modul2/sedaap```, seperti berikut:
`c
char *argv[] = {"mv", "/home/sheinna/modul2/jpg/", "/home/sheinna/modul2/sedaap", NULL};
execv("/bin/mv", argv);
`
#

### Jawab 3d
Untuk soal 3d, diminta untuk membuat file kosong dengan nama ```coba1.txt``` di dalam semua folder yang ada dalam direktori ```indomie```, dan kemudian membuat file kosong lagi dengan nama ```coba2.txt``` di dalam semua folder tadi (```/home/sheinna/modul2/jpg/```). Untuk memberikan 3 detik sebelum membuat file ```coba2.txt```, maka dapat menggunakan fungsi ```sleep(3)```. Jika menggunakan perintah exec, dapat menggunakan perintah sebagai berikut:
`c
pid_t cid6;
cid6 = fork();
if(cid6 < 0) exit(0);
if(cid6 == 0)
{
  chdir("/home/sheinna/modul2/indomie");
  char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba1.txt", "\\;", NULL};
  execv("/usr/bin/find", argv);
}
else
{
  sleep(3);
  chdir("/home/sheinna/modul2/indomie");
  char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba2.txt", "\\;", NULL};
  execv("/usr/bin/find", argv);
}
`
#
