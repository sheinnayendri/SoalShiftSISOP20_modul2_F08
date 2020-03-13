#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int cekConvert(char s[])
{
  if(s[0] == '*') return -2;
	int angka = 0;
	for(int i = 0; i < strlen(s); i++)
	{
		if((s[i] < '0' || s[i] > '9') && s[i] != '*') return -1;
		angka += (s[i] - '0');
		angka *= 10;
	}
	angka /= 10;
	return angka;
}

int main(int arg, char *argv[]) {

  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }
  int detik = cekConvert(argv[1]);
  int menit = cekConvert(argv[2]);
  int jam = cekConvert(argv[3]);


  if(arg != 5){
    printf("argumen tidak sesuai\n");
    exit(EXIT_FAILURE);
  }
  if(argv[4][strlen(argv[4])-3] != '.' || argv[4][strlen(argv[4])-2] != 's' || argv[4][strlen(argv[4])-1] != 'h'){
      printf("eror bukan bash\n");
      exit(EXIT_FAILURE);
  }

  if(cekConvert(argv[1]) == -1 || cekConvert(argv[2]) == -1 || cekConvert(argv[3]) == -1) 
  {
      printf("eror bukan angka atau angka tidak sesuai\n");
      exit(0);
  }
  // if(detik > 59 || detik < 0 || menit > 59 || menit < 0 || jam < 0 || jam > 23){
  //   printf("eror waktu salah\n");
  //   exit(EXIT_FAILURE);    
  // }
  

	time_t now;
	time(&now);
  
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  

	struct tm *local;
  char *bash[] = {"bash", argv[4], NULL};

  while (1) {
    pid_t child_id;
    
    time(&now);
    local = localtime(&now); 
    if(strcmp(argv[1], "*") == 0){ 
        if(strcmp(argv[2], "*") == 0){ 
          if(strcmp(argv[3], "*") == 0){ //setiap detik setiap menit setiap jam
            while (1){
              child_id = fork();
              if(child_id == 0){
                execv("/bin/bash", bash);
              }
              sleep(1);
              time(&now);
              local = localtime(&now); 
            }
          }
          else{
            while (1){
              if(atoi(argv[3]) == local->tm_hour){//setiap detik setiap menit BEDA jam
                child_id = fork();
                if(child_id == 0){
                  execv("/bin/bash", bash);
                }
              }
              sleep(1);
              time(&now);
              local = localtime(&now); 
            }
          }
        }
        else{
          if(strcmp(argv[3], "*") == 0){ //setiap detik BEDA menit setiap jam
            while (1){
              if(atoi(argv[2]) == local->tm_min){
                child_id = fork();
                if(child_id == 0){
                  execv("/bin/bash", bash);
                }
              }
              
              sleep(1);
              time(&now);
              local = localtime(&now); 
            }
          }
          else{
            while (1){
              if(atoi(argv[2]) == local->tm_min && atoi(argv[3]) == local->tm_hour){ //setiap detik BEDA menit BEDA jam
                child_id = fork();
                if(child_id == 0){
                  execv("/bin/bash", bash);
                }
              }
              sleep(1);
              time(&now);
              local = localtime(&now); 
            }
          }
        }
        }
      
    else{
      if(strcmp(argv[2], "*") == 0){ 
          if(strcmp(argv[3], "*") == 0){ //BEDA detik setiap menit setiap jam
            while (1){
              if(atoi(argv[1]) == local->tm_sec){
                child_id = fork();
                if(child_id == 0){
                  execv("/bin/bash", bash);
                }
              sleep(1);
              time(&now);
              local = localtime(&now); 
              }
            }
          }
          else{
            while (1){
              if(atoi(argv[1]) == local->tm_sec && atoi(argv[3]) == local->tm_hour){//BEDA detik setiap menit BEDA jam
                child_id = fork();
                if(child_id == 0){
                  execv("/bin/bash", bash);
                }
              }
              sleep(1);
              time(&now);
              local = localtime(&now); 
            }
          }
        
      }
      else{
        if(strcmp(argv[3], "*") == 0){ //BEDA detik BEDA menit setiap jam
          while (1){
            if(atoi(argv[1]) == local->tm_sec && atoi(argv[2]) == local->tm_min){
              child_id = fork();
              if(child_id == 0){
                execv("/bin/bash", bash);
              }
            }
            
            sleep(1);
            time(&now);
            local = localtime(&now); 
          }
        }
        else{
          while (1){
            if(atoi(argv[1]) == local->tm_sec && atoi(argv[2]) == local->tm_min && atoi(argv[3]) == local->tm_hour){ //BEDA detik BEDA menit BEDA jam
              child_id = fork();
              if(child_id == 0){
                execv("/bin/bash", bash);
              }
            }
            sleep(1);
            time(&now);
            local = localtime(&now); 
          }
        }
      }
        
    
    
    }
  }
  }
