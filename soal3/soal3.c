#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<wait.h>
#include<time.h>
#include<stdbool.h>
#include<dirent.h>

int main() 
{
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

    while((wait(&status)) > 0);
    cid3 = fork();
    if(cid3 < 0) exit(0);
    if(cid3 == 0)
    {
        char *argv[] = {"unzip", "/home/sheinna/modul2/jpg.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }

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
}
