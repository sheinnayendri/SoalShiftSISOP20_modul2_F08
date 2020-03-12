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

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
	time_t now;
	time(&now);
	printf("%s", ctime(&now));

	struct tm *local;
  char *bash[] = {"bash", argv[4], NULL};

  while (1) {
    pid_t child_id;
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
              if(atoi(argv[3]) == local->tm_hour){ //setiap detik BEDA menit BEDA jam
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
